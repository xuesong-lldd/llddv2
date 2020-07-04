#include <stdio.h>
#include <stdlib.h>

int func(int x)
{
    int a, a0, a1, a2;
    a0 = x * x * 2 + 1;
    a1 = x + 2 - a0;
    a2 = x / 2 + a1;
    a = a0 + a1 + a2;
    printf("a: %d\n", a);
    return a;
}

int main(void)
{
    int i = 1;
    while(1) {
        i = func(i);
        sleep(3);
    }
    return EXIT_SUCCESS;
}
