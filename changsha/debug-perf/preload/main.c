#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
	int a;
	union {
		unsigned int pid;
		char path[256];
	};
}pre_load_t;

int injection_demo()
{
	char buffer[1000];
	int amount_read;
	int fd;

	fd = fileno(stdin);
	if ((amount_read = read(fd, buffer, sizeof buffer)) == -1) {
		perror("error reading");
		return -1;
	}

	if (fwrite(buffer, sizeof(char), amount_read, stdout) == -1) {
		perror("error writing");
		return -1;
	}

	return 0;
}


int main(int argc, char *argv[])
{
	/* The first part is for the union memory layout tap */
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

	/* The second part is for the injection demo for the dynamic lib */
	injection_demo();

	return 0;
}
