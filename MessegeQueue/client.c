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
	
	char clientName[64];
	sprintf(clientName, "/client-%d",getpid());

	if( (client = mq_open(clientName, O_CREAT|O_RDONLY,0660,&attr) )==-1)
	{
		perror("mq_open");
		exit(EXIT_FAILURE);
	}
		if((server = mq_open(SERVER_NAME, O_WRONLY)) == -1)
	{
		perror("mq_open_server");
		exit(EXIT_FAILURE);
	}
	char serverMessage[64];
	char temp[10];
	//while(fgets(temp, 2, stdin)){

		if(mq_send(server, clientName, strlen(clientName)+1, 0) == -1)
		{
			perror("mq_send");
			exit(1);
		}
		if(mq_receive(client, serverMessage, 256, NULL) == -1)
		{
			perror("mq_receive");
			exit(1);
		}
		printf("%s\n",serverMessage);
	//}
	mq_unlink(clientName);
	mq_unlink(SERVER_NAME);
	return 0;
}

