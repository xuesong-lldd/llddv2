/* gcc -E main.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FUNC_NAME(name)  #name
#define FUNC_NAME_STR FUNC_NAME(my_defined_func)
int main(void)
{

	char buf[64];
	strcpy(buf, FUNC_NAME_STR);
	printf("Hello world: %s\n", buf);

	return 0;
}
