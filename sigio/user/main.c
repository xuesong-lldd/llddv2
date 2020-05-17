#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
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
	int oflags, fd;

	/* set new SIGIO handler */
	signal(SIGIO, sig_handler);

	fd = open(DEVFILE, O_RDWR);
	if (fd < 0) {
		printf("open file %s failed\n", DEVFILE);
		return fd;
	}

	/* set fd's owner process */
	fcntl(fd, F_SETOWN, getpid());
	/* get old fd flags */
	oflags = fcntl(fd, F_GETFL);
	/* set new fd flags */
	fcntl(fd, F_SETFL, oflags | O_ASYNC);

	printf("Do everything you want until we get the SIGIO...\n");
	while(g_flag);
	close(fd);
	return 0;
}

