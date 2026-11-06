#include <stdio.h>
#include <stdlib.h>


int* BubbleSort(int* src, int size) {
    // Выделяем память под новый массив
    int* copy = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i += 1) {
        copy[i] = src[i];

    }
    for (int i = 0; i < size - 1; i += 1) {
        for (int j = 0; j < size - 1; j += 1) {

            // правила сортировки по возрастанию 
            if (copy[j] > copy[j + 1]) {
                int temp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = temp;

            }
        }
    }
    return copy;
} 

int main() {
    int size;

    // вопрос пользолователю скок чисел он хочет ввести 
    printf("Сколько чисел хотите ввести: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        printf("Ошибка, попробуйте еще раз \n");
        return 1;
    }

    // Выделяем память под исходный массив 
    int* orig = (int*)malloc(size * sizeof(int));
    if (orig == NULL) {
        printf("Errore ((");
        return 1;

    }

    // ввод числа с клавиатуры 
    printf("Введите %d чисел\n", size);
    for (int i = 0; i < size; i += 1) {
        printf("Число %d: ", i + 1);
        while (scanf("%d", &orig[i]) != 1) {

            // проверка на то что пользователь написал число, а не рандом символ
            printf(" Попробуйте еще раз:");
            while (getchar() != '\n');
        }
    }

    // Исходный массив 
    printf("Исходный массив: ");
    for (int i = 0; i < size; i += 1) {
        printf("%d", orig[i]);
    }
    printf("\n");

    // Сортировка
    int* sorted = BubbleSort(orig, size);
    if (sorted == 0) {
        free(orig);
        return 1;
    }

    // Выводим результат
    printf("Отсортированный: ");
    for (int i = 0; i < size; i += 1) {
        printf("%d", sorted[i]);
    }
    printf("\n");

    // Освобождаем память 
    free(orig);
    free(sorted);

    return 0;
}
