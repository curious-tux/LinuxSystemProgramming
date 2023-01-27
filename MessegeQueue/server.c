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

	char clientName[256];
	char serverMessage[] = "You have been served!!";
	struct mq_attr attr;
	
	attr.mq_curmsgs = 0;
	attr.mq_flags = 0;
	attr.mq_msgsize = 256;
	attr.mq_maxmsg = 10;
	
	printf("Starting server!!\n");
	/*Create server*/
	if( (server = mq_open(SERVER_NAME, O_RDONLY|O_CREAT,0660,&attr)) == -1)
	{
		perror("mq_open");
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		if( mq_receive(server, clientName, 256, NULL) == -1)
		{
			perror("mq_receive");
			exit(EXIT_FAILURE);
		}
		printf("Hello to you %s\n",clientName);
		if( (client = mq_open(clientName, O_WRONLY)) == -1 )
		{
			perror("mq_open");
			exit(EXIT_FAILURE);
		}
		
		if( mq_send(client, serverMessage, strlen(serverMessage), 0) == -1)
		{
			perror("mq_send");
			exit(EXIT_FAILURE);
		}
		mq_close(client);
	}
	mq_close(server);
	return 0;
}

