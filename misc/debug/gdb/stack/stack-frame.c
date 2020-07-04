#include <stdio.h>

int b(int arg0, int *p)
{
	return arg0 + *p;
}
int c()
{
	return 0;
}
int a()
{
	int local = 100, sum;
	sum = b(10, &local);
	c();
	return sum;
}

int main(void)
{
	int sum = 0;
	sum = a();
	printf("sum = %d\n", sum);

	return 0;
}
