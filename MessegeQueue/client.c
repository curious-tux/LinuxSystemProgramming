#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define SERVER_NAME "/server"
int main(void)
{
	mqd_t client,server;

	struct mq_attr attr = 
	{
		.mq_curmsgs = 0,
		.mq_flags = 0,
		.mq_msgsize = 256,
		.mq_maxmsg = 10
	};
	

	

	return 0;
}

