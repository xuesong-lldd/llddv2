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
    int i;
    ssize_t sz;
    unsigned char *buf, *ptr;
    int status;
    pid_t pid;
    int target_addr;
    int read_sz;
    int repeat;
    long data;

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
    printf("read_sz: %x\n", read_sz);


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

    /* read loop */
    repeat = (read_sz + sizeof(long)-1) / sizeof(long);
    for (i = 0; i < repeat; i++) {
        unsigned long ofs = i*sizeof(long);
        *((long*)&buf[ofs]) = ptrace(PTRACE_PEEKDATA, pid, target_addr + ofs, NULL);
        if (errno != 0) {
            printf("Failed to read, errno: %d\n", errno);
            goto err_exit2;
        }
    }

    /* print read data */
    /*ptr = buf;
    for (i = 0; i < read_sz; i++, ptr++) {
        if (i%16 == 0)
            printf("\n");
        printf("%02x ", *ptr);
    }
    printf("\n");
    */

    /* clean up */
    ptrace(PTRACE_CONT, pid, NULL, NULL);
    ptrace(PTRACE_DETACH, pid, NULL, NULL);
    free(buf);
    return EXIT_SUCCESS;

err_exit2:
    ptrace(PTRACE_CONT, pid, NULL, NULL);
    ptrace(PTRACE_DETACH, pid, NULL, NULL);

err_exit1:
    free(buf);
    return EXIT_FAILURE;
}
