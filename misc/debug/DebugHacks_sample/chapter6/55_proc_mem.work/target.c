#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int cnt = 0;

int main(void)
{

    while(1) {
        printf("target: %d\n", cnt);
        cnt++;
        sleep(2);
    }
    return EXIT_SUCCESS;
}
