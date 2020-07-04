#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *p = malloc(10);
    p[10] = 1;
    free(p);
    return EXIT_SUCCESS;
}
