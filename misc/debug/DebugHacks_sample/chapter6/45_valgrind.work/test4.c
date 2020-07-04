#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *x = malloc(sizeof(int));
    free(x);
    int a = *x + 1;
    return a;
}
