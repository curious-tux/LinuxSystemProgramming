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
	
	/*Create server*/
	if( (server = mq_open(SERVER_NAME, O_CREAT|O_RDONLY,0660,&attr) == -1 ))
	{
		perror("mq_open");
		exit(EXIT_FAILURE);
	}
	char clientName[64];
	char serverMessage[] = "You have been served!!";
	while(1)
	{
		if( mq_receive(server, clientName, sizeof(clientName), NULL) == -1)
		{
			perror("mq_receive");
			exit(EXIT_FAILURE);
		}

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

