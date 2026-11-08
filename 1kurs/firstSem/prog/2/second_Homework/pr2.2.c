#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void prosm(int size, double **matrix) {
        for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) printf("%g ", matrix[i][j]);
        printf("\n");
    }
}
int main() {
    int size;
    printf("Введите размер матрицы. (Только квадратные матрицы имеют определитель)\n");
    scanf("%d", &size);
    printf("Вводите числа в матрицу: \n");
    double **matrix = (double**)malloc(size * sizeof(double*)), opred = 1;
    if (matrix == NULL) {
        printf("Ошибка, память не выделилась!");
        return 1;
    }
    for (int i = 0; i < size; i++) {
        matrix[i] = (double*)malloc(size * sizeof(double));
        if (matrix[i] == NULL) {
            printf("Ошибка, память не выделилась!");
            return 1;
        }
    }
    for (int i = 0; i < size; i++) for (int j = 0; j < size; j++) scanf("%lf", &matrix[i][j]);

    for (int i = 0; i < size; i++) for (int j = 0; j < size - 1 - i; j++) {
        if (matrix[i][i] == 0) {
            int flag = 0;
            for (int kef = i + 1; kef < size; kef++) {
                if (matrix[kef][i] == 0) continue;
                for (int i2 = 0; i2 < size; i2++) {
                    printf("%g ", matrix[kef][i]);
                    int peremen = matrix[kef][i2];
                    matrix[kef][i2] = matrix[i][i2];
                    matrix[i][i2] = peremen;
                    printf("rfr");
                }
                printf("%d", flag);
                flag = 1;
            }
            if (flag == 0) {
                printf("Определитель: 0\n");
                return 0;
            }
        }
        double koef = matrix[j + i + 1][i] / matrix[i][i];
        for (int t = 0; t < size; t++) matrix[j + i + 1][t] -= koef * matrix[i][t];
    }
    printf("\n\n");
    prosm(size, matrix);
    for (int i = 0; i < size; i++) opred *= matrix[i][i];
    printf("Определитель: %g\n", opred);
    for (int i = 0; i < size; i++) free(matrix[i]);
    free(matrix);
    return 0;
}