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

	fd = open(DEVFILE, O_RDWR);
	if (fd < 0) {
		printf("open file %s failed\n", DEVFILE);
		return fd;
	}

	epfd = epoll_create(1);
	if (epfd < 0) {
		printf("epoll_create() failed\n");
		close(fd);
		return epfd;
	}

	in_ev.data.fd = fd;
	in_ev.events = EPOLLIN;
	epoll_ctl(epfd, EPOLL_CTL_ADD, in_ev.data.fd, &in_ev);

	printf("begin to epoll_wait() @fd[%d]...\n", fd);
	nfds = epoll_wait(epfd, &out_ev, 1, -1);
	printf("nfds = %d, ready fd = %d, event type = %s\n", nfds, out_ev.data.fd, (out_ev.events & EPOLLIN) ? "READ" : "N/A"); 

	close(epfd);
	close(fd);
	return 0;
}

