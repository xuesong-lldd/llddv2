#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
	int ret;
	int fd;

	if (argc < 2) {
		printf("usage:\n\t load_kmod kmod_path\n");
		return 0;
	}

	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		printf("open file %s failed: %d\n", argv[1], fd);
		return fd;
	}

	ret = syscall(SYS_finit_module, fd, "", 0);
    	printf("ret = %d\n", ret);

	return 0;
}
