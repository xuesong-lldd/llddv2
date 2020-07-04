#include <stdio.h>
#include <stdlib.h>

int a_5(int a)
{
	int rv = 0;
	if (a > 5) {
		printf("invalid parameters...a = %d\n", a);
		return -1;
	}

	for (int i = 0; i < a; i++) {
		rv += i;
	}

	return rv;
}

int b_10(int b)
{
	int rv = 0;
	if (b > 10) {
		printf("invalid parameter...b = %d\n", b);
		return -1;
	}

	for (int i = 0; i < b; i++) {
		rv += i * b;
	}

	return rv;
}

int main(int argc, char *argv[])
{
	int i = 0, rv = 0;
	if (argc <= 1) {
		printf("usage:\n\tmain 10\n");
		return -1;
	}

	i = atoi(argv[1]);
	switch (i) {
		case 5:
			rv = a_5(5);
			printf("a_5: rv = %d\n", rv);
			break;
		case 10:
			rv = b_10(10);
			printf("b_10: rv = %d\n", rv);
			break;	       
	}

	return 0;
}
