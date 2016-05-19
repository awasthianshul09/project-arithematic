#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>

#define DATA "heelo "

int main(int argc, char const *argv[])
{
	int sock;
	struct sockaddr_in server;
	struct hostent *hp;
	char buff[1024];

	sock = socket(AF_INET , SOCK_STREAM,0);
	if (sock<0)
	{
		perror("failed to create socket");
		exit(EXIT_FAILURE);
	}

	server.sin_family = AF_INET;

	hp = gethostbyname(argv[1]);
	if (hp ==0)
	{
		perror("gethostbyname failed");
		close(sock);
		exit(EXIT_FAILURE);
	}

	memcpy(&server.sin_addr,hp->h_addr,hp->h_length);
	server.sin_port = htons(6000);

	if(connect(sock,(struct sockaddr *)&server,sizeof(server))<0){

		perror("connect failed");
		close(sock);
		exit(EXIT_FAILURE);
	}

	if (send(sock,DATA,sizeof(DATA),0)<0)
	{
		perror("send failed");
		close(sock);
		exit(EXIT_FAILURE);
	}

	printf("sent data is %s",DATA);

	close(sock);

	return 0;

}