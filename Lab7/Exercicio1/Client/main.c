#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define SA struct sockaddr

int main(int argc, char const *argv[])
{
    int valread, client_fd, len;
    struct sockaddr_in serv_addr;
    char msg[200];
    char buffer[1024] = { 0 };

    if((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Erro na criação do SOCKET...\n");
        return -1;
    } else {
        printf("SOCKET criado com sucesso...\n");
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
        printf("Endereço inválido...\n");
        return -1;
    }

    while(1) {
        memset(msg, 0, 200);
        memset(buffer, 0, 1024);

        printf("Digite a mensagem que deseja enviar: ");
        fgets(msg, 200, stdin);
        if(strcmp(msg, "quit") == 0) {
            break;
        }
        len = strlen(msg);
        msg[len-1] = '\0';

        sendto(client_fd, (char*)&msg, sizeof(msg), 0, (SA*)&serv_addr, sizeof(serv_addr));
        printf("Mensagem enviada com sucesso...\n");

        int n = recvfrom(client_fd, (char*)buffer, 1024, 0, (SA*) &serv_addr, sizeof(serv_addr));
        printf("Mensagem recebida: %s\n", buffer);

    }
  
    // closing the connected socket
    close(client_fd);

    return 0;
}
