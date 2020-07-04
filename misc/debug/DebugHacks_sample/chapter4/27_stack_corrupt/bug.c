#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

#define LOGFILE		"error.log"

#define NR_DATA		64
#define NR_QUEUE	32

#define NR_REQ		64
#define NR_RES		16

#define SV_ST_REQ	1
#define SV_ST_RES_OK	2
#define SV_ST_RES_NG	3

struct service {
	int req[NR_DATA];
	int res[NR_DATA];
	int status;
};

struct service *queue[NR_QUEUE];
int rqueue, wqueue, nr_queue;

pthread_mutex_t mtx1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx3 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;

FILE *logfile;

void log_setup_strings(char *buf, const char *func)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	sprintf(buf, "[%ld.%06ld]:%s\n", now.tv_sec, now.tv_usec, func);
}

void log_error(const char *func)
{
	char *logbuf;

	logbuf = malloc(256);

	usleep(100000);
	log_setup_strings(logbuf, func);

	pthread_mutex_lock(&mtx3);
	fputs(logbuf, logfile);
	fflush(logfile);
	pthread_mutex_unlock(&mtx3);

	free(logbuf);
}

int queue_service_req(struct service *sv)
{
	int ret = -1;

	pthread_mutex_lock(&mtx1);

	if (nr_queue >= NR_QUEUE)
		goto out;

	queue[wqueue] = sv;
	nr_queue++;
	wqueue++;
	if (wqueue >= NR_QUEUE)
		wqueue = 0;

	pthread_cond_signal(&cond1);
	ret = 0;

out:
	pthread_mutex_unlock(&mtx1);
	return ret;
}

struct service *deq_service_req(void)
{
	struct service *sv;

	sv = NULL;
	pthread_mutex_lock(&mtx1);

	while (nr_queue <= 0)
		pthread_cond_wait(&cond1, &mtx1);

	sv = queue[rqueue];
	nr_queue--;
	rqueue++;
	if (rqueue >= NR_QUEUE)
		rqueue = 0;

	pthread_mutex_unlock(&mtx1);

	return sv;
}

int proc_req(void)
{
	struct service sv;
	struct timeval now;
	struct timespec timeout;
	int i, ret;

	sv.status = SV_ST_REQ;
	for (i = 0; i < NR_DATA; i++)
		sv.req[i] = 0;

	ret = queue_service_req(&sv);
	if (ret == -1)
		return -1;

	gettimeofday(&now, NULL);
	timeout.tv_sec = now.tv_sec + 1;
	timeout.tv_nsec = now.tv_usec * 1000;

	pthread_mutex_lock(&mtx2);
	ret = pthread_cond_timedwait(&cond2, &mtx2, &timeout);
	pthread_mutex_unlock(&mtx2);

	if (ret == ETIMEDOUT)
		return -1;

	if (sv.status == SV_ST_RES_OK)
		return 0;

	return -1;
}

int proc_res(void)
{
	struct timeval now;
	struct service *sv;
	int i;

	sv = deq_service_req();
	if (!sv)
		return -1;

	pthread_mutex_lock(&mtx2);

	usleep(900000);

	for (i = 0; i < NR_DATA; i++) {
		gettimeofday(&now, NULL);
		sv->res[i] = now.tv_usec;
	}
	sv->status = SV_ST_RES_OK;

	pthread_mutex_unlock(&mtx2);

	return 0;
}

void *th_req(void *p)
{
	for (;;) {
		if (proc_req() == -1)
			log_error("Request");
		usleep(100000);
	}

	return NULL;
}

void *th_res(void *p)
{
	for (;;) {
		if (proc_res() == -1)
			log_error("Response");
		usleep(100000);
	}

	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t reqs[NR_REQ], resp[NR_RES];
	int i;

	/* error log init */
	logfile = fopen(LOGFILE, "w");

	for (i = 0; i < NR_RES; i++)
		pthread_create(&resp[i], NULL, th_res, NULL);

	for (i = 0; i < NR_REQ; i++)
		pthread_create(&reqs[i], NULL, th_req, NULL);

	for (;;)
		sleep(1);

	fclose(logfile);

	return 0;
}
