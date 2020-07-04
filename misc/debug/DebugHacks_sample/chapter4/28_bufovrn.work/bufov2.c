#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int my_data[2] = {1, 2};

int calc_index(void)
{
    /* この関数にバグがあり、あやまった値を返す */
    return  -7;
}


int main(void)
{
    int idx = calc_index();
    my_data[idx] = 0x0a;
    my_data[idx+1] = 0x08;
    printf("This is a message\n");
    return EXIT_SUCCESS;
}
