#include <stdio.h>

int func_debug(int x)
{
    int a, a0, a1, a2;
    a0 = x * x * 2 + 1;
    a1 = x + 2 - a0;
    a2 = x / 2 + a1;
    a = a0 + a1 + a2;
    printf("[Debug]a0: %d, a1: %d, a2: %d\n", a0, a1, a2);
    printf("a: %d\n", a);
    return a;
}
