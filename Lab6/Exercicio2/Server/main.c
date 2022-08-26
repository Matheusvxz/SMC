#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
// #define PORT 4242
#define SA struct sockaddr

int main(int argc, char const *argv[])
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("Falha bind o Socket...\n");
		exit(0);
	}
	else
		printf("Socket bind com sucesso...\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening on port %d...\n", atoi(argv[1]));
	len = sizeof(cli);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("Falha ao aceitar o cliente...\n");
		exit(0);
	}
	else {
		printf("Cliente aceito...\n");
    }

	char buff[MAX];
	int n;

	for (;;) {
		bzero(buff, MAX);

		read(connfd, buff, sizeof(buff));
		write(connfd, buff, sizeof(buff));

		if (strncmp("exit", buff, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
	}

	close(sockfd);
}
