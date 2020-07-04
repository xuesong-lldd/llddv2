#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

int main( int argc, char *argv[] )
{
    int i, fd;
    const int npath = 100;
    char path[npath];
    off_t ofs;
    ssize_t sz;
    unsigned char *buf, *ptr;
    int status;
    pid_t pid;
    int target_addr;
    int read_sz;

    /* get arguments */
    if (argc < 4) {
        printf("Usage:\n");
        printf("  # %s pid target_addr(hex) read_sz(hex)\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid = atoi(argv[1]);
    printf("PID: %d\n", pid);

    sscanf(argv[2], "%x", &target_addr);
    printf("target_addr: %x\n", target_addr);

    sscanf(argv[3], "%x", &read_sz);
    printf("read_sz: %d\n", read_sz);


    /* allocate memory for reading */
    buf = malloc(read_sz);
    if (buf == NULL) {
        printf("Failed to malloc (size: %d)\n", read_sz);
        return EXIT_FAILURE;
    }

    /* attach and open /proc/[PID]/mem */
    if ( ptrace(PTRACE_ATTACH, pid, NULL, NULL) != 0 ) {
        printf("Failed to attach (pid: %d)\n", pid);
        goto err_exit1;
    }
    waitpid(pid, &status, __WALL);

    snprintf(path, npath, "/proc/%d/mem", pid);
    fd = open(path, O_RDWR);
    if (fd < 0 ) {
        printf("Failed to open\n");
        goto err_exit2;
    }

    /* seek and read data */
    ofs = lseek(fd, target_addr, SEEK_SET);
    if (ofs == (off_t)-1) {
        printf("Failed to lseek, errno: %d\n", errno);
        goto err_exit3;
    }

    sz = read(fd, buf, read_sz);
    if (sz != read_sz) {
        printf("Failed to read, errno: %d\n", errno);
        goto err_exit3;
    }

    /* print read data */
    /*
    ptr = buf;
    for (i = 0; i < read_sz; i++, ptr++) {
        if (i%16 == 0)
            printf("\n");
        printf("%02x ", *ptr);
    }*/
    printf("\n");

    /* clean up */
    close(fd);
    ptrace(PTRACE_CONT, pid, NULL, NULL);
    ptrace(PTRACE_DETACH, pid, NULL, NULL);
    free(buf);
    return EXIT_SUCCESS;

err_exit3:
    close(fd);

err_exit2:
    ptrace(PTRACE_CONT, pid, NULL, NULL);
    ptrace(PTRACE_DETACH, pid, NULL, NULL);

err_exit1:
    free(buf);
    return EXIT_FAILURE;
}
