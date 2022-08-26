#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAX 80
#define PORT 4242
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
	servaddr.sin_port = htons(PORT);

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
		printf("Server listening on port %d...\n", PORT);
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
	char command[30];
	char value[20];
	int n;
	int i = 0;
	int s = 0;
	// infinite loop for chat
	for (;;) {
		bzero(buff, MAX);
		bzero(command, 30);
		bzero(value, 20);
		s = 0;
		i = 0;
		// read the message from client and copy it in buffer
		read(connfd, buff, sizeof(buff));

		if (strncmp("exit", buff, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}

		for(n = 0; n < MAX; n++) {
			char c = buff[n];

			if(c == ' ') {
				s = 1;
				continue;
			}
			if(c == '\0') {
				break;
			}
			if(s == 0) {
				command[n] = c;
			} else {
				value[i] = c;
				i++;
			}
		}

		int led = atoi(value);

		printf("Comando: %s Valor: %s\n", command, value);

		if(strcmp(command, "off") == 0) {
			printf("Desligar o LED KRL\n");
			
			switch (led) {
				case 1:
					printf("DESLIGANDO LED 1\n");
					break;
				case 2:
					printf("DESLIGANDO LED 2\n");
					break;
				case 3:
					printf("DESLIGANDO LED 3\n");
					break;
				case 4:
					printf("DESLIGANDO LED 4\n");
					break;
				default:
					break;
			}
			
		} else if(strcmp(command, "on") == 0) {
			printf("Liga essa PORRRAAA\n");

			switch (led) {
				case 1:
					printf("LIGANDO LED 1\n");
					break;
				case 2:
					printf("LIGANDO LED 2\n");
					break;
				case 3:
					printf("LIGANDO LED 3\n");
					break;
				case 4:
					printf("LIGANDO LED 4\n");
					break;
				default:
					break;
			}
		}

		// and send that buffer to client
		write(connfd, "Comando executado!", 19);

	}

	// After chatting close the socket
	close(sockfd);
}
