#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/signal.h>
#include <semaphore.h>

unsigned count;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


void thread_timer(union sigval val)
{
	if(count < 10)
		printf("Passing time ...%d\n",count++);
	else 
	{
		if( pthread_mutex_lock(&mutex) == -1 )
		{
			printf("Error while acquiring lock!! at %s\n",__func__);
			perror("mutex_lock");
			exit(EXIT_FAILURE);
		}
		if( pthread_cond_signal(&cond) == -1 )
		{
			printf("Error while Signaling %s\n",__func__);
			perror("cond_signal");
			exit(EXIT_FAILURE);
		}
		if( pthread_mutex_unlock(&mutex) == -1 )
		{
			printf("Error while unlocking mutex %s\n",__func__);
			perror("mutex_unlock");
			exit(EXIT_FAILURE);
		}	
	}
}

int main(void)
{
	timer_t timer_id;
	struct sigevent sevent;
	struct itimerspec tspec 

			= 
	{
		.it_value.tv_sec = 1, /*Timer expiers after 1 sec*/
		.it_value.tv_nsec = 0,
		.it_interval.tv_sec = 1, /*Timer reload (to be expiered after a sec)*/
		.it_interval.tv_nsec = 0
	};
	sevent.sigev_notify = SIGEV_THREAD; /*A new thread will be created once the timer expiers*/
	sevent.sigev_value.sival_ptr = &timer_id;
	sevent._sigev_un._sigev_thread._function = thread_timer;
	sevent._sigev_un._sigev_thread._attribute = NULL;

	if( timer_create(CLOCK_REALTIME, &sevent, &timer_id) == -1 )
	{
		printf("Error while Creating timer!! at %s\n",__func__);
		perror("timer_create");
		exit(EXIT_FAILURE);
	}
	if( timer_settime(timer_id, 0/*No flags*/, &tspec, NULL) == -1 )
	{
		printf("Error while Setting time!! at %s\n",__func__);
		perror("timer_settime");
		exit(EXIT_FAILURE);
	}
	if( pthread_mutex_lock(&mutex) == -1 )
	{
		printf("Error while acquiring mutex!! at %s\n",__func__);
		perror("mutex_lock");
		exit(EXIT_FAILURE);
	}
	if(pthread_cond_wait(&cond, &mutex) == -1)
	{
		printf("Error while waiting for signal !! at %s\n",__func__);
		perror("cond_wait");
		exit(EXIT_FAILURE);
	}
	if( pthread_mutex_unlock(&mutex) == -1 )
	{
		printf("Error while unlocking mutex!! at %s\n",__func__);
		perror("mutex_unlock");
		exit(EXIT_FAILURE);
	}
	
	//while(1); /*Holt program to see timer in action {temoerary}*/
	return 0;
}

