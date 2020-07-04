#include <stdio.h>
#include <stdlib.h>

#define data_size 128*1024*1024
unsigned char data[data_size];

int main (void)
{
    int i;
    for (i = 0; i < data_size; i++)
        data[i] = 0xff & random();
    printf("initialized.\n");
    while(1)
        sleep(1000);
    return EXIT_SUCCESS;
}
