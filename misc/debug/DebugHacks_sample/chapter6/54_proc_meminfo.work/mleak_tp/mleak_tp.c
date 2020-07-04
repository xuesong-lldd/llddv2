#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <string.h>

//const float Pleak = 0.1;
const float Pleak = 0.0;
const float Paccess = 0.5;
const float MinAlloc = 1;
const float MaxAlloc = 4*1024*1024;

double frand(void)
{
    return ((double)rand())/RAND_MAX;
}

size_t calc_size(void)
{
    double r = frand();
    double a = pow(MaxAlloc/MinAlloc, r) * MinAlloc;
    return (size_t)a;
}

int leak(void)
{
    if (frand() < Pleak)
        return 1;
    return 0;
}

int is_access(void)
{
    if (frand() < Paccess)
        return 1;
    return 0;
}

void *thr_func(void *arg)
{
    while (1) {
        size_t s = calc_size();
        void *p = malloc(s);
        if (p == NULL) {
            printf("Failed to malloc: %d\n", s);
            return NULL;
        }

        if (!is_access())
            memset(p, 0xaa, s);

        if (!leak())
            free(p);

        /* sleep */
        const static useconds_t slp_min = 10*1000;
        const static useconds_t slp_max = 100*1000;
        useconds_t slp = (slp_max - slp_min) * frand() + slp_min;
        usleep(slp);
    }
}

int main(void)
{
    pthread_t t1, t2, t3, t4;
    pthread_create(&t1, NULL, thr_func, NULL);
    pthread_create(&t2, NULL, thr_func, NULL);
    pthread_create(&t3, NULL, thr_func, NULL);
    pthread_create(&t4, NULL, thr_func, NULL);
    thr_func(NULL);

    return EXIT_SUCCESS;
}
