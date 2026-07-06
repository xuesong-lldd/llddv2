#define _GNU_SOURCE
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sched.h>
#include <pthread.h>
#include <sys/types.h>

/* the rt test thread with the SCHED_RR schedling policy */
static void *rt_test_thread(void *param)
{
	pthread_t thread;
	cpu_set_t mask;
	struct sched_param schedp;
	int i, max_prio, cpu;

	if (!param) {
		printf("parameter pointer passed to the thread is invalid\n");
		return NULL;
	}

	cpu = *(int *)param;

	thread = pthread_self();

	/* set the cpu affinity to cpu for current thread */
	CPU_ZERO(&mask);
	CPU_SET(cpu, &mask);
	if (pthread_setaffinity_np(thread, sizeof(cpu_set_t), &mask)) {
		perror("pthread_setaffinity_np failed");
		return NULL;
	}

	/* set the scheduling policy and priority */
	memset(&schedp, 0, sizeof(schedp));
	max_prio = sched_get_priority_max(SCHED_FIFO);
	schedp.sched_priority = max_prio;
	if (sched_setscheduler(0, SCHED_FIFO, &schedp)) {
		perror("setscheduler failed");
		return NULL;
	}

	/* get the cpu affinity info */
	CPU_ZERO(&mask);
	if (pthread_getaffinity_np(thread, sizeof(cpu_set_t), &mask)) {
		perror("pthread_getaffinity_np failed");
		return NULL;
	}

	for (i = 0; i < CPU_SETSIZE; i++) {
		if (CPU_ISSET(i, &mask))
			break;
	}

	printf("thread[%d]@cpu#%d: policy = SCHED_FIFO max_prio = %d\n", gettid(), i, max_prio);

	return NULL;
}

int main(int argc, char *argv[])
{
	int status;
	pthread_t thread;
	pthread_attr_t attr;
	int cpu, *thread_par;

	if (argc != 2) {
		printf("Usage:\n\trt-main cpu[the cpu number that the rt thread will be bound to]\n");
		return -1;
	}

	cpu = atoi(argv[1]);
	thread_par = malloc(sizeof(int));
	if (!thread_par) {
		perror("malloc failed");
		return -1;
	}
	*thread_par = cpu;

	status = pthread_attr_init(&attr);
	if (status != 0) {
		perror("pthread_attr_init failed");
		free(thread_par);
		return -1;
	}
	status = pthread_create(&thread, &attr, rt_test_thread, thread_par);
	pthread_join(thread, NULL);
	printf("main thread exits...\n");
	free(thread_par);

	return 0;
}
