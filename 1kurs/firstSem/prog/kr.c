#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand(time(0));        
    int num = rand() % 10 + 1; 
    printf("Случайное число: %d\n", num);
    return 0;
}
