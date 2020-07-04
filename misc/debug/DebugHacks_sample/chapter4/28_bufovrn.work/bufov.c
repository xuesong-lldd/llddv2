#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char my_name[] = "book cat dog building automoble curry";

void func(void)
{
    char name[5];
    strcpy(name, my_name);
}

int main(void)
{
    func();
    return EXIT_SUCCESS;
}
