#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/epoll.h>

#define DEVFILE	"/dev/fa_dev"

int main(void)
{
	int oflags, fd;
	int epfd, nfds;
	struct epoll_event in_ev, out_ev;
	int read_val;
	ssize_t sz;

	fd = open(DEVFILE, O_RDWR);
	if (fd < 0) {
		printf("open file %s failed\n", DEVFILE);
		return fd;
	}

	sz = read(fd, &read_val, sizeof(int));
	printf("sz = %ld\n", sz);
	close(fd);
	return 0;
}

