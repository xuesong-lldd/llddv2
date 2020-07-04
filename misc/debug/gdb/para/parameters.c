#include <stdio.h>
#include <stdlib.h>

/* 8 parameters */
void sub_func(int a,  int b, int c, int d, int e, int f, int *g, int h)
{
	printf("a = %d, b = %d, c = %d, d = %d, e = %d, f = %d, g = %d, h = %d\n", a, b, c, d, e, f, *g, h);

	return;
}

int main(void)
{
	int v = 7;
	sub_func(1, 2, 3, 4, 5, 6, &v, 8);
	return 0;
}

