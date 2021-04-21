#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>

#define DEVFILE	"/dev/fa_dev"
static volatile unsigned long g_flag = 1;

static void sig_handler(int signum)
{
	printf("Get the SIGIO signal (%d), the application will exit\n", signum);
	g_flag = 0;	
}

int main(void)
{
	int oflags, fd, pgsz;
	unsigned long *p_mapped;

	pgsz = sysconf(_SC_PAGE_SIZE);

	/* set new SIGIO handler */
	signal(SIGIO, sig_handler);

	fd = open(DEVFILE, O_RDWR);
	if (fd < 0) {
		printf("open file %s failed\n", DEVFILE);
		return fd;
	}

	/* set fd's owner process to receive the SIGIO signal */
	fcntl(fd, F_SETOWN, getpid());
	/* get old fd flags */
	oflags = fcntl(fd, F_GETFL);
	/* set new fd flags */
	fcntl(fd, F_SETFL, oflags | O_ASYNC);
	/* file mmap */
	p_mapped = mmap(NULL, pgsz, PROT_READ, MAP_PRIVATE, fd, 0);
	if (p_mapped == MAP_FAILED) {
		printf("mmap failed\n");
		close(fd);
		return -1;
	}
	printf("Do everything you want until we get the SIGIO...\n");
	printf("before signaled: *p_mapped = 0x%lx\n", *p_mapped);
	while(g_flag);
	printf("after signaled: *p_mapped = 0x%lx\n", *p_mapped);
	munmap(p_mapped, pgsz);
	close(fd);

	return 0;
}

