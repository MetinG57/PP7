// main.c
#include <stdio.h>
extern int add(int, int);

int main(void) {
    int sum = add(5, 7);
    printf("5 + 7 = %d\n", sum);
    return 0;
}
