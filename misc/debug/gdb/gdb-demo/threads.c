#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

unsigned long a = 0;
unsigned long b = 0;

static void * pthread_run1(void *arg)
{
        int runflag = 1;

        while(runflag)
        {
                a++;
                sleep(1);
        }

        pthread_exit((void *)a);

        return NULL;
} 

static void * pthread_run2(void *arg)
{
        int runflag = 1;

        while(runflag)
        {
                b++;
                sleep(1);
        }

        pthread_exit((void *)b);

        return NULL;
}

int main(int argc,char *argv[])
{
        pthread_t tid1, tid2;
        int retval_1, retval_2;

        pthread_create(&tid1, NULL, pthread_run1, NULL);
        pthread_create(&tid2, NULL, pthread_run2, NULL);

        pthread_join(tid1,(void *)&retval_1);
        pthread_join(tid2,(void *)&retval_2);

        printf("retval_1: %d\n", retval_1);
        printf("retval_2: %d\n", retval_2);

        return 0x0;
}
