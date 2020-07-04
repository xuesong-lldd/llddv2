#include <stdlib.h>
#include <stdio.h>

/*
 * %gcc -pg -o main main.c
 * %./main 40
 * %gprof -b ./main
 */
static unsigned long sum(int num)
{
	int ret = 0;
	for(int i = 0; i < num; i++)
		ret += i;
	return ret;
}

static unsigned long fb(int num)
{
	if(num < 2)
		return 1;
	else
		return fb(num -1) + fb(num-2);
}

int main(int argc, char** argv)
{
	int i = 0;
	unsigned long r1 = 0, r2 = 0;

	if(argc < 2)
	{
		printf("usage num\n");
		return 1;
	}
	int num = atoi(argv[1]);
	for (i = 0; i < 15; i++) {
		r1 += i * sum(num);
	}

	for (i = 0; i < 5; i++) {
		r2 += 2 * i * fb(num);
	}
	printf("r1=%ld, r2=%ld\n", r1, r2);
	return 0;
}
