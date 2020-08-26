#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "../chrdev_ioctl_def.h"

#define DEVFILE	"/dev/fa_dev"

int
main(int argc, char *argv[])
{
	int ret;
	int dtb_fd, cdev_fd;

	if (argc < 2) {
		printf("usage:\n\t dtbp dtb_path\n");
		return 0;
	}
	printf("pid = %d\n", getpid());
	dtb_fd = open(argv[1], O_RDONLY);
	if (dtb_fd < 0) {
		printf("open file %s failed: %d\n", argv[1], dtb_fd);
		return dtb_fd;
	}
	printf("dtb_fd = %d\n", dtb_fd);

	cdev_fd = open(DEVFILE, O_RDWR);
	if (cdev_fd < 0) {
		printf("open file %s failed\n", DEVFILE);
		return cdev_fd;
	}

	ioctl(cdev_fd, IOCTL_GET_DTB_FD, &dtb_fd);

	close(dtb_fd);
	close(cdev_fd);
	return 0;
}
