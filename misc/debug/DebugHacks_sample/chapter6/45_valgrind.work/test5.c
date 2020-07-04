#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *x = malloc(sizeof(int));
    free(x);
    free(x);
    return EXIT_SUCCESS;
}
