#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/signal.h>
#include <semaphore.h>

#define SIG SIGRTMIN
void sigactionHandler( int sig,siginfo_t *si,void *p )
{
   printf("Caught signal %d\n", sig);
   signal(sig, SIG_IGN);
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

	struct sigaction saction;
	sigset_t mask;
	
	sevent.sigev_notify = SIGEV_SIGNAL;
	sevent.sigev_value.sival_ptr = &timer_id;
	sevent.sigev_signo = SIG;
	
	saction.sa_flags = SA_SIGINFO;
	saction.sa_sigaction = sigactionHandler;
	sigemptyset(&saction.sa_mask);
	if( sigaction(SIG, &saction, NULL) == -1)
	{
		printf("Error while setting up sigaction !!at %s\n",__func__);
		perror("sigaction");
		exit(-1);
	}

	/*Temporarily disabling signaling*/
	/* sigemptyset(&mask); */
	/* sigaddset(&mask, SIG); */
	/* if( sigprocmask(SIG_SETMASK, &mask, NULL) == -1 ) */
	/* { */
	/* 	printf("Error while diabling signal !!%s\n",__func__); */
	/* 	perror("sigprocmask"); */
	/* 	exit(-1); */
	/* } */
//	sevent._sigev_un._sigev_thread._function = thread_timer;
//	sevent._sigev_un._sigev_thread._attribute = NULL;

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
	sleep(5);
	/* if (sigprocmask(SIG_UNBLOCK, &mask, NULL) == -1) */
	/* { */
	/* 	printf("Error while unblocking!! at %s\n",__func__); */
	/* 	perror("sigprocmask"); */
	/* 	exit(EXIT_FAILURE); */

	/* } */

	return 0;
}
