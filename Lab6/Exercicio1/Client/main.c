#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 4242

int main(int argc, char const *argv[])
{
    int sock = 0, valread, client_fd, len;
    struct sockaddr_in serv_addr;
    char msg[200];
    char buffer[1024] = { 0 };

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address.\n");
        return -1;
    }

    if((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))) {
        printf("\nInvalid address.\n");
        return -1;
    }

    while(1) {
        printf("Digite a mensagem que deseja enviar\n");
        scanf("%50[^\n]", msg);
        // len = strlen(msg);
        // msg[len] = '\0';
        // len++;

        if(strcmp(msg, "quit") == 0) {
            break;
        }

        send(sock, msg, len, 0);
        printf("Mensagem enviada\n");
        valread = read(sock, buffer, 1024);
        printf("%s\n", buffer);
    }
  
    // closing the connected socket
    close(client_fd);

    return 0;
}
