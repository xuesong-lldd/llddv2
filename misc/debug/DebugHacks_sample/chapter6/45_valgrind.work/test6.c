#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a;
    int* p = &a;
    p -= 0x20;
    *p = 1;
    return EXIT_SUCCESS;
}
