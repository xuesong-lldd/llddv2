#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>

#define DEVFILE	"/dev/fa_dev"

int main(void)
{
	int oflags, fd, err = 0;
	int epfd, nfds, pgsz;
	struct epoll_event in_ev, out_ev;
	int read_val;
	ssize_t sz;
	unsigned long *p_mapped;

	pgsz = sysconf(_SC_PAGE_SIZE);
	fd = open(DEVFILE, O_RDWR);
	if (fd < 0) {
		printf("open file %s failed\n", DEVFILE);
		return fd;
	}

	sz = read(fd, &read_val, sizeof(int));
	printf("sz = %ld\n", sz);

	/* ioctl begins */
	err = ioctl(fd, 0xdead, 0xbeef);
	if (err) {
		printf("ioctl failed\n");
		close(fd);
		return -1;
	}

	/* mmap begins */
	p_mapped = mmap(NULL, pgsz, PROT_READ, MAP_PRIVATE, fd, 0);
	if (p_mapped == MAP_FAILED) {
		printf("mmap failed\n");
		close(fd);
		return -1;
	}

	printf("*p_mapped = 0x%lx\n", *p_mapped);
	munmap(p_mapped, pgsz);

	close(fd);
	return 0;
}

