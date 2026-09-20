#include <stdio.h>

int main() {
    int a1, a2, a3, a4, a5;
	printf("Введите 5 чисел: ");
	scanf("%d %d %d %d %d", &a1, &a2, &a3, &a4, &a5);
	printf("Вы ввели:  %d, %d, %d, %d, %d\n", a1, a2, a3, a4, a5);
	
	int c;
	c = a1 + a2 + a3 + a4 + a5;
	printf("Сумма 5 чисел: %d\n", c);
	
	int c1;
	c1 = a1 - a2 - a3 - a4 - a5;
	printf("Разность 5 чисел: %d\n", c1);
	
	int x;
	x = a1 * a2 * a3 * a4 * a5;
	printf("Произведение 5 чисел: %d\n", x);
	
	int del;
	del = a1 % 10;
	int del2;
	del2 = a2 % 10;
	int del3;
	del3 = a3 % 10;
	int del4;
	del4 = a4 % 10;
	int del5;
	del5 = a5 % 10;
	printf("Остаток от деления на 10, этих 5 чисел: %d, %d, %d, %d, %d\n", del, del2, del3, del4, del5);
	
	printf("Размер 1 числа: %zu байт\n", sizeof(a1) );
	printf("Размер 2 числа: %zu байт\n", sizeof(a2) );
	printf("Размер 3 числа: %zu байт\n", sizeof(a3) );
	printf("Размер 4 числа: %zu байт\n", sizeof(a4) );
	printf("Размер 5 числа: %zu байт\n", sizeof(a5) );
	
	return 0;
	
}