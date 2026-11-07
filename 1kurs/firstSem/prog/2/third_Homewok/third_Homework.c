#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <termios.h>
#include <sys/stat.h>

const char *USERS_DIR = "users";
const char *SECRET_KEY_FILE = "secret.key";

// Использование enum для целых чисел — правильный способ в C для размеров массивов
enum {
    LINE  = 256,
    LOGIN = 64,
    PASS  = 128
};

// ввод пароля без echo
void read_password(const char *prompt, char *buf, int size)
{
    struct termios oldt, newt;

    printf("%s", prompt);
    fflush(stdout);

    tcgetattr(0, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &newt);

    fgets(buf, size, stdin);
    buf[strcspn(buf, "\r\n")] = 0;

    tcsetattr(0, TCSANOW, &oldt);
    printf("\n");
}

// хэш пароля
void hash_password(const char *password, char out[33])
{
    unsigned long h = 5381;
    int i;
    for (i = 0; password[i]; i++)
        h = h * 33 + (unsigned char)password[i];
    sprintf(out, "%016lx", h);
}

// check login
int valid_login(const char *login)
{
    int i;
    if (!login[0]) return 0;
    if (!isalpha((unsigned char)login[0]) && login[0] != '_') return 0;
    for (i = 0; login[i]; i++)
        if (!isalnum((unsigned char)login[i]) && login[i] != '_') return 0;
    return 1;
}

// путь к файл login
void user_path(const char *login, char *out, int size)
{
    snprintf(out, size, "%s/%s.txt", USERS_DIR, login);
}

int user_exists(const char *login)
{
    char path[512];
    struct stat st;
    user_path(login, path, sizeof(path));
    return stat(path, &st) == 0;
}

// create new login
int create_user(const char *login, const char *password)
{
    char path[512], hash[33];

    if (!valid_login(login)) {
        printf("    Логин: только буквы/цифры/_, начинается с буквы или _.\n");
        return 0;
    }
    if (user_exists(login)) {
        printf("Пользователь '%s' уже есть.\n", login);
        return 0;
    }

    hash_password(password, hash);
    user_path(login, path, sizeof(path));

    FILE *f = fopen(path, "w");
    if (!f) { printf("Не могу создать файл(.\n"); return 0; }
    fprintf(f, "%s:%s\n", login, hash);
    fclose(f);

    printf("Пользователь '%s' создан.\n", login);
    return 1;
}

// delete login
int delete_user(const char *login)
{
    char path[512];
    if (!user_exists(login)) {
        printf("Нет такого пользователя!\n");
        return 0;
    }
    user_path(login, path, sizeof(path));
    remove(path);
    printf("[-] Пользователь '%s' удалён.\n", login);
    return 1;
}

// change password
int change_password(const char *login)
{
    char path[512], pwd[PASS], pwd2[PASS], hash[33];
    FILE *f;

    if (!user_exists(login)) {
        printf("[!] Нет такого пользователя.\n");
        return 0;
    }

    read_password("Новый пароль: ", pwd, sizeof(pwd));
    read_password("Повтор: ", pwd2, sizeof(pwd2));

    if (strcmp(pwd, pwd2) != 0) {
        printf("[!] Пароли не совпадают.\n");
        return 0;
    }

    hash_password(pwd, hash);
    user_path(login, path, sizeof(path));

    f = fopen(path, "w");
    if (!f) { printf("[!] Ошибка записи.\n"); return 0; }
    fprintf(f, "%s:%s\n", login, hash);
    fclose(f);

    printf("[+] Пароль обновлён.\n");
    return 1;
}

// list login
void list_users(void)
{
    char cmd[512];
    printf("Пользователи:\n");
    fflush(stdout);
    // Формируем безопасную команду с подстановкой переменной USERS_DIR
    snprintf(cmd, sizeof(cmd), "ls \"%s\" 2>/dev/null | sed 's/\\.txt$//' | sed 's/^/  - /'", USERS_DIR);
    system(cmd);
}

// check password
int check_password(const char *login, const char *password)
{
    char path[512], line[LINE], stored_login[LOGIN], stored_hash[33];
    char hash[33];

    user_path(login, path, sizeof(path));

    FILE *f = fopen(path, "r");
    if (!f) return 0;
    if (!fgets(line, sizeof(line), f)) { fclose(f); return 0; }
    fclose(f);

    line[strcspn(line, "\r\n")] = 0;
    char *colon = strchr(line, ':');
    if (!colon) return 0;
    *colon = 0;
    strcpy(stored_login, line);
    strcpy(stored_hash, colon + 1);

    hash_password(password, hash);

    return strcmp(stored_login, login) == 0 && strcmp(stored_hash, hash) == 0;
}

// admin-console
void admin_shell(void)
{
    char line[LINE], pwd[PASS], pwd2[PASS];

    printf("\n ___СЕКРЕТНАЯ КОНСОЛЬ___\n");
    printf("Команды: add <login>, del <login>, list, passwd <login>, exit\n\n");

    while (1) {
        printf("admin> ");
        fflush(stdout);
        if (!fgets(line, sizeof(line), stdin)) break;
        line[strcspn(line, "\r\n")] = 0;

        char *cmd = strtok(line, " ");
        char *arg = strtok(NULL, " ");
        if (!cmd) continue;

        if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "quit") == 0) {
            break;
        }
        else if (strcmp(cmd, "help") == 0) {
            printf("add <login> | del <login> | list | passwd <login> | exit\n");
        }
        else if (strcmp(cmd, "list") == 0) {
            list_users();
        }
        else if (strcmp(cmd, "add") == 0) {
            if (!arg) { printf("[!] Укажите логин.\n"); continue; }
            read_password("Пароль: ", pwd, sizeof(pwd));
            read_password("Повтор: ", pwd2, sizeof(pwd2));
            if (strcmp(pwd, pwd2) != 0) { printf("Не совпадают!\n"); continue; }
            if (strlen(pwd) < 3)       { printf("Короткий пароль!\n"); continue; }
            create_user(arg, pwd);
        }
        else if (strcmp(cmd, "del") == 0) {
            if (!arg) { printf("Укажите логин!\n"); continue; }
            delete_user(arg);
        }
        else if (strcmp(cmd, "passwd") == 0) {
            if (!arg) { printf("Укажите логин!\n"); continue; }
            change_password(arg);
        }
        else {
            printf("Неизвестная команда?!: %s\n", cmd);
        }
    }
    printf("ВЫХОД\n\n");
}

// settigns (ключ и папка)
void setup(void)
{
    struct stat st;

    if (stat(USERS_DIR, &st) != 0)
        mkdir(USERS_DIR, 0755);

    if (stat(SECRET_KEY_FILE, &st) != 0) {
        FILE *f = fopen(SECRET_KEY_FILE, "w");
        if (f) {
            fprintf(f, "secret-key-root"); // Новый ключ
            fclose(f);
            chmod(SECRET_KEY_FILE, 0600);
        }
    }
}

// чтение secret-key
void get_secret_key(char *buf, int size)
{
    FILE *f = fopen(SECRET_KEY_FILE, "r");
    buf[0] = 0;
    if (!f) return;
    if (fgets(buf, size, f))
        buf[strcspn(buf, "\r\n")] = 0;
    fclose(f);
}

// авторизация
int login_flow(char *out_login, int size)
{
    char login[LOGIN], password[PASS], secret[128];

    get_secret_key(secret, sizeof(secret));

    printf("Логин: ");
    fflush(stdout);
    if (!fgets(login, sizeof(login), stdin)) return 0;
    login[strcspn(login, "\r\n")] = 0;

    if (secret[0] && strcmp(login, secret) == 0) {
        admin_shell();
        return 0;
    }

    if (!user_exists(login)) {
        printf("[!] Неверный пользователь.\n");
        return 0;
    }

    read_password("Пароль: ", password, sizeof(password));

    if (!check_password(login, password)) {
        printf("[!] Неверный пароль.\n");
        return 0;
    }

    printf("[+] Добро пожаловать, %s!\n", login);
    snprintf(out_login, size, "%s", login);
    return 1;
}

// console defolt user
void user_session(const char *login)
{
    char line[LINE];

    printf("\nКонсоль %s. Введите 'exit' для выхода.\n\n", login);

    while (1) {
        printf("%s> ", login);
        fflush(stdout);
        if (!fgets(line, sizeof(line), stdin)) break;
        line[strcspn(line, "\r\n")] = 0;

        if (strcmp(line, "exit") == 0 || strcmp(line, "quit") == 0) break;
        else if (strcmp(line, "help") == 0) printf("Доступна только exit.\n");
        else if (line[0]) printf("(эхо) %s\n", line);
    }
}

// main
int main(void)
{
    char login[LOGIN];

    setup();
    printf("Система авторизации\n");

    if (login_flow(login, sizeof(login)))
        user_session(login);

    return 0;
}