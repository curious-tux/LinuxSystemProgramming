#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main(void)
{
	int nwk_socket;

	if( (nwk_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in addr = {
		.sin_addr.s_addr = INADDR_ANY,
		.sin_family = AF_INET,
		.sin_port = htons(12340),
	};
	
	if(connect(nwk_socket, (struct sockaddr *)&addr, sizeof(addr))==-1)
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}

	char serverResponse[256];
	ssize_t len;
	len = recv(nwk_socket, serverResponse, sizeof(serverResponse), 0);
	printf("Server Respone:%s",serverResponse);

	close(nwk_socket);
	return 0;
}


