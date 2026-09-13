#include <stdio.h>

int main() {
    int num1, num2, num3, num4, num5;
    int sum = 0;
    int vichet = 0;
    int umnojit = 1;
    int ostat_10 ;


    // Ввод чисел чисел от 1 до 5

    printf("Введите num1:\n "); 
    scanf("%d", &num1);
    sum = sum + num1;
    vichet = vichet - num1;
    umnojit = umnojit * num1;


    printf("Введите num2:\n "); 
    scanf("%d", &num2);
    sum = sum + num2;
    vichet = vichet - num2;
    umnojit = umnojit * num2;


    printf("Введите num3:\n "); 
    scanf("%d", &num3);
    sum = sum + num3;
    vichet = vichet - num3;
    umnojit = umnojit * num3;

  
    printf("Введите num4:\n "); 
    scanf("%d", &num4);
    sum = sum + num4;
    vichet = vichet - num4;
    umnojit = umnojit * num4;


    printf("Введите num5:\n "); 
    scanf("%d", &num5);
    sum = sum + num5;
    vichet = vichet - num5;
    umnojit = umnojit * num5;

    if (sum != 0) {
        ostat_10 =  ostat_10 % 10;
    }  else {
        ostat_10 = 0;
    }

  

    // сумма всех пяти числе 
   printf("Сумма: %d\n", sum); 
   // разность всех пяти чисел
   printf("Разность: %d\n", vichet);
   // произведение всех пяти чисел
   printf("Произвдени: %d\n", umnojit);
   // Остаток от деления на 10 
   printf("Остаток деления на 10: %d\n", ostat_10);


   printf("Число 1: %d\n", num1);
   printf("Число 2: %d\n", num2);
   printf("Число 3: %d\n", num3);
   printf("Число 4: %d\n", num4);
   printf("Число 5: %d\n", num5);


    return 0;
}
    