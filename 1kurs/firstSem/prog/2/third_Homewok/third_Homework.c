#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 128

/* Проверка допустимости логина: только буквы/цифры/_ , длина 1..MAX_LEN-6.
   Защита от выхода из папки вида "../etc/passwd". */
static int valid_login(const char *s) {
    size_t len = strlen(s);
    if (len == 0 || len > MAX_LEN - 6) return 0;
    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)s[i];
        if (!(isalnum(c) || c == '_')) return 0;
    }
    return 1;
}

/* Обрезаем перевод строки \r\n с конца */
static void chomp(char *s) {
    size_t len = strlen(s);
    while (len > 0 && (s[len-1] == '\n' || s[len-1] == '\r')) {
        s[--len] = '\0';
    }
}

/* Проверяем, есть ли учётная запись с данным логином и совпадает ли пароль.
   Возвращает: 1 — успех, 0 — пользователя нет, -1 — пароль неверный,
   -2 — файл битый (не удалось прочитать пароль). */
static int check_account(const char *login, const char *password) {
    char fname[MAX_LEN];
    snprintf(fname, sizeof(fname), "%s.txt", login);

    FILE *f = fopen(fname, "r");
    if (!f) return 0;           // файла нет → пользователя нет

    char file_login[MAX_LEN] = {0};
    char file_pass[MAX_LEN]  = {0};

    /* если первая строка = логин, вторая = пароль */
    if (!fgets(file_login, sizeof(file_login), f)) { fclose(f); return -2; }
    if (!fgets(file_pass,  sizeof(file_pass),  f)) { fclose(f); return -2; }
    fclose(f);

    chomp(file_login);
    chomp(file_pass);

    /* сверяем логин из файла с введённым */
    if (strcmp(file_login, login) != 0) return -2;

    return strcmp(file_pass, password) == 0 ? 1 : -1;
}

int main(void) {
    char login[MAX_LEN];
    char password[MAX_LEN];

    printf("Логин: ");
    if (!fgets(login, sizeof(login), stdin)) return 0;
    chomp(login);

    if (!valid_login(login)) {
        printf("Недопустимый логин\n");
        return 0;
    }

    /* сначала проверяем, существует ли логин — но чтобы не читать
       пароль вслепую, просто смотрим, открывается ли файл */
    char fname[MAX_LEN];
    snprintf(fname, sizeof(fname), "%s.txt", login);
    FILE *probe = fopen(fname, "r");
    if (!probe) {
        printf("Пользователь '%s' не найден\n", login);
        return 0;
    }
    fclose(probe);

    printf("Пароль: ");
    if (!fgets(password, sizeof(password), stdin)) return 0;
    chomp(password);

    int res = check_account(login, password);
    switch (res) {
        case  1: printf("Авторизация успешна. Добро пожаловать, %s!\n", login); break;
        case -1: printf("Неверный пароль\n"); break;
        case -2: printf("Файл учётной записи повреждён\n"); break;
        default: printf("Пользователь не найден\n"); break;
    }
    return 0;
}