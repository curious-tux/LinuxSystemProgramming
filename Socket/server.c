#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define serverResponse "You have been served"

int main(void)
{
	int server_socket,client_socket;

	if( (server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in 
		addr = 
	{
		.sin_addr.s_addr = INADDR_ANY,
		.sin_family = AF_INET,
		.sin_port = htons(12340),
	};
	
	if(bind(server_socket, (const struct sockaddr *) &addr, sizeof(addr)) == -1)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
		
	if(listen(server_socket, 5))
	{
		perror("listen");
		exit(EXIT_FAILURE);	
	}
	client_socket = accept(server_socket, NULL, NULL);

	if(client_socket < 0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}	
	if(send(client_socket, serverResponse, strlen(serverResponse)+1, 0) < 0)
	{
		
		perror("send");
		exit(EXIT_FAILURE);
		
	}
	close(client_socket);
}
