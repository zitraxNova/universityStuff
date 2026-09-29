#include <stdio.h>

int main() {
    int n;
    int arr[10]; 
    int i; 

    printf("Введите число не больше 10: ");
    scanf("%d", &n);

    if (n > 10 || n <= 0) {
        printf("Ошибка!\n");
        return 1; 
    }
    // Заполнение массива
    printf("Введите %d чисел:\n", n);
    for (i = 0; i < n; i++) { 
        printf("Число %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    
    // Сортировка вставками (Insertion Sort)
    for (i = 1; i < n; i++) { 
        int k = arr[i]; 
        int j = i - 1;

        while (j >= 0 && arr[j] > k) {
            arr[j + 1] = arr[j];
            j-=1;
        }
        arr[j + 1] = k;
    }
    
    printf("Отсортированный массив:\n");
    for (i = 0; i < n; i++) { 
        printf("%d ", arr[i]);
    }

    printf("\nMin число: %d\n", arr[0]);
    printf("Max число: %d\n", arr[n - 1]);

    return 0;
}