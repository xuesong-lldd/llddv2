#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DEVFILE	"/dev/fa_dev"

int main(void)
{
	int fd, retv;
	fd_set rfds;

	fd = open(DEVFILE, O_RDWR);
	if (fd < 0) {
		printf("open file %s failed\n", DEVFILE);
		return fd;
	}

	/* reset the rfds first */
	FD_ZERO(&rfds);
	/* add the interested fd into the fd set */
	FD_SET(fd, &rfds);

	printf("begin to invoke the select() @fd[%d]...\n", fd);

	/* comment out the ifdef block to see the FD_SETSIZE(1024) max limit */
#if 0
	for (int i = 0; i < FD_SETSIZE - fd + 1; i++) {
		FD_SET(fd + i, &rfds);
	}
#endif
	/* block is possible here for the data is ready for read */
	retv = select(fd + 1, &rfds, NULL, NULL, NULL);
	if (retv < 0) {
		perror("select error");
		return -1;
	}

	/* check if the fd is still in the rfds */
	if (FD_ISSET(fd, &rfds)) {
		printf("The data is available for read @fd[%d] now\n", fd);
	} else {
		printf("No data is available for read, possibly the exception is happened\n");
	}

	close(fd);

	return 0;
}

