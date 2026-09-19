#include <stdio.h>

int main() {
    int num1, num2, num3, num4, num5;
    int sum = 0;
    int vichet = 0;
    int umnojit = 1;
    int ostat1, ostat2, ostat3, ostat4, ostat5;

    // Ввод чисел чисел от 1 до5

    printf("Введите num1:\n "); 
    scanf("%d", &num1);
    sum = sum + num1;
    vichet = vichet - num1;
    umnojit = umnojit * num1;
    ostat1 = num1 % 10;


    printf("Введите num2:\n "); 
    scanf("%d", &num2);
    sum = sum + num2;
    vichet = vichet - num2;
    umnojit = umnojit * num2;
    ostat2 = num2 % 10;


    printf("Введите num3:\n "); 
    scanf("%d", &num3);
    sum = sum + num3;
    vichet = vichet - num3;
    umnojit = umnojit * num3;
    ostat3 = num3 % 10;

  
    printf("Введите num4:\n "); 
    scanf("%d", &num4);
    sum = sum + num4;
    vichet = vichet - num4;
    umnojit = umnojit * num4;
    ostat4 = num4 % 10;


    printf("Введите num5:\n "); 
    scanf("%d", &num5);
    sum = sum + num5;
    vichet = vichet - num5;
    umnojit = umnojit * num5;
    ostat5 = num5 % 10;


  
    // сумма всех пяти числе 
   printf("Сумма: %d\n", sum); 
   // разность всех пяти чисел
   printf("Разность: %d\n", vichet);
   // произведение всех пяти чисел
   printf("Произвдени: %d\n", umnojit);
   // Остаток от деления на 10 
   // 1 числа
   printf("Остаток деления на 10: %d\n", ostat1);
   // 2 числа
   printf("Остаток деления на 10: %d\n", ostat2);
   // 3 числа
   printf("Остаток деления на 10: %d\n", ostat3);
   // 4 числа
   printf("Остаток деления на 10: %d\n", ostat4);
   // 5 числа
   printf("Остаток деления на 10: %d\n", ostat5);


   printf("Число 1: %zu байт \n", sizeof(num1));
   printf("Число 2: %zu байт \n", sizeof(num2));
   printf("Число 3: %zu байт \n", sizeof(num3));
   printf("Число 4: %zu байт \n", sizeof(num4));
   printf("Число 5: %zu байт \n", sizeof(num5));


    return 0;
}
    