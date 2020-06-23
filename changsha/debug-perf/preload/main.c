#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
	int a;
	union {
		unsigned int pid;
		char path[256];
	};
}pre_load_t;

int main(int argc, char *argv[])
{
	char *c;
	pre_load_t *p = malloc(sizeof(pre_load_t));
	if (!p) {
		printf("malloc() failed\n");
		return -1;
	}
	printf("p = %p, sizeof(*p) = %lu\n", p, sizeof(*p));
	memset(p, 0, sizeof(*p));

	p->a = 1;
	p->pid = 10;
	strcpy(p->path, "hello");
	printf("p->a = %d, p->pid = %u, p->path = %s\n", p->a, p->pid, p->path);

	c = (char *)&p->pid;
	for (int i = 0; i < 5; i++) {
		printf("%c ", *(c + i));
	}
	printf("\n");

	srand(time(NULL));
	printf("rand = %d\n", rand());

	return 0;
}
