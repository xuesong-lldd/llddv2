#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *x = malloc(sizeof(int));
    int a = *x + 1;
    free(x);
    return a;
}
