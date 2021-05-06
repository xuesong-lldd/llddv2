#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/poll.h>
#include <fcntl.h>

#define DEVFILE	"/dev/fa_dev"

int main(void)
{
	int fd, retv;
	struct pollfd fds;

	fd = open(DEVFILE, O_RDWR);
	if (fd < 0) {
		printf("open file %s failed\n", DEVFILE);
		return fd;
	}

	fds.fd = fd;
	fds.events = POLLIN;

	retv = poll(&fds, 1, -1);
	if (retv == -1) {
		perror("poll failed");
		close(fd);
		return -1;
	}

	if (fds.revents & POLLIN) {
		printf("data is ready for read\n");
	} else {
		printf("other events happened\n");
	}

	close(fd);

	return 0;
}

