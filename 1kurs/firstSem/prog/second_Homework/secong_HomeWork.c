#include <stdio.h>
// тут все просто std - стандратная; lib - библиотека
#include <stdlib.h>
// библиотека для типов данных 
#include <time.h>

int main() {
    int igrok, comp;
    int igrok_schet = 0;
    int comp_schet = 0;

    srand(time(NULL));

    printf("Камень-ножницы-бумага до 3 побед\n");
    printf("Введите 1 - Камень, 2 - Ножницы, 3 - Бумага\n\n");

    for (int i = 0; i < 3; i++) {
        while (1) {
            if (scanf("%d", &igrok) != 1) {
                // соблюдение правил(провекрка на символы(google))
                while (getchar() != '\n') {}
                printf("Errore! Попробуйте еще раз:");

            // соблюдение правил(что число должно находиться в диапозоне от 1 до 3) 
            } else if (igrok < 1 || igrok > 3) {
                printf("Errore! Попробуйте еще раз:");
            } else {
                break;
            }
        }
        
        // выбор компьютером рандомного числа
        comp = rand() % 3 + 1;
        int result = (igrok - comp + 3) % 3;

        // условие игры
        if (result == 0) {
            printf("dead heat...\n");
        } else if (result == 1) {
            printf("Win!\n");
            igrok_schet++;
        } else {
            printf("Defeat(\n");
            comp_schet++;
        }
    }
    
    printf("Igrok %d:%d Comp", igrok_schet, comp_schet);
    return 0;
}