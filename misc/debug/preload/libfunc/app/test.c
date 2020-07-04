#include <stdio.h>
#include <stdlib.h>

typedef struct hook_sys {
	int a;
	int b;
} hook_sys_t;

int main (void)
{
	unsigned int *magic;
	hook_sys_t *p = malloc(sizeof(hook_sys_t));
	fprintf(stderr, "In main, malloc(%ld) = %p\n", sizeof(*p), p);
	//printf("In main, malloc(%ld) = %p\n", sizeof(*p), p); /* trigger the malloc() again */
	p->a = 1;
	p->b = 2;
	fprintf(stderr, "magc num = 0x%x\n", *(unsigned int *)(p + 1));

	free(p);

	return 0;
}
