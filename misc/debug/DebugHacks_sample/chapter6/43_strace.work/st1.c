#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp;
    fp = fopen("/etc/shadow", "r");
    if (fp == NULL) {
        printf("Error!\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
