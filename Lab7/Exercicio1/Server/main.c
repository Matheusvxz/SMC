#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAX 80
#define SA struct sockaddr

int main(int argc, char const *argv[])
{
	int sockfd, len;
	struct sockaddr_in servaddr, cliaddr;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1) {
		printf("Criação do SOCKET falhou...\n");
		return -1;
	} else {
		printf("Criação do SOCKET com sucesso...\n");
	}

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("Falha para criar o BIND do SOCKET...\n");
		close(sockfd);
		return -1;
	} else {
		printf("BIND realizado na porta %d com sucesso...\n", atoi(argv[1]));
	}

	char buff[MAX];

	for (;;) {
		memset(buff, 0, MAX);
		memset(&cliaddr, 0, sizeof(cliaddr));

		len = sizeof(cliaddr);

		recvfrom(sockfd, (char*)buff, MAX, 0, (SA*) &cliaddr, &len);
		printf("Mensagem recebida: %s\n", buff);
		sendto(sockfd, (char*) buff, sizeof(buff), 0, (SA*) &cliaddr, len);
		printf("Mensagem enviada.\n");

		if (strncmp("exit", buff, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
	}

	close(sockfd);
}
