#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char s[10] = "abc\n";
    char *p = s;
    memcpy(p, s, strlen(s));
    return EXIT_SUCCESS;
}
