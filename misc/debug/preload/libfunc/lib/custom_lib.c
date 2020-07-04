#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct hook_sys {
	int a;
	int b;
	unsigned int c;
} hook_sys_t;

void *malloc(size_t size)
{
	static void *(*mallocp)(size_t size);
	char *error;
	hook_sys_t *p;

	fprintf(stderr, "In the wrapper of the libc malloc() funciton\n");
	/* get address of libc malloc */
	if (!mallocp) {
		mallocp = dlsym(RTLD_NEXT, "malloc");
		if ((error = dlerror()) != NULL) {
			fputs(error, stderr);
			exit(1);
		}
	}

	p = mallocp(sizeof(hook_sys_t));
	p->c = 0x5a5a5a5a;
	fprintf(stderr, "malloc(%ld) = %p\n", sizeof(hook_sys_t), p);

	return p;
}

void free(void *ptr)
{
	static void (*freep)(void *);
	char *error;

	fprintf(stderr, "In the wrapper of the libc free() funciton\n");
	/* get address of libc free */
	if (!freep) {
		freep = dlsym(RTLD_NEXT, "free");
		if ((error = dlerror()) != NULL) {
			fputs(error, stderr);
			exit(1);
		}
	}
	fprintf(stderr, "free(%p)\n", ptr);
	freep(ptr);
}

