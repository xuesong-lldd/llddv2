#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int cnt = 0;

void cnt_reset(void)
{
	pthread_mutex_lock(&mutex);
	cnt = 0;
	pthread_mutex_unlock(&mutex);
}

void* thr(void *arg)
{
	while(1) {
		pthread_mutex_lock(&mutex);
		if (cnt > 1)
			cnt_reset();
		else
			cnt++;
		pthread_mutex_unlock(&mutex);

		printf("%d\n",cnt);
		sleep(1);
	}
}

int main(void)
{
	pthread_t tid;

	pthread_create(&tid, NULL, thr, NULL);
	pthread_join(tid, NULL);

	return EXIT_SUCCESS;
}
