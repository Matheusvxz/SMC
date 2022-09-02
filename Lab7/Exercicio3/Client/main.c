#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define SA struct sockaddr

int main(int argc, char const *argv[])
{
    int client_fd;
    struct sockaddr_in serv_addr;
    char msg[200];
    char buffer[1024] = { 0 };
    FILE *log = fopen("log.txt", "w");
    struct timeval st, et;

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

    strcpy(msg, "SMC");
    int i;
    for(i = 0; i < 20;i++) {
        memset(buffer, 0, 1024);
        gettimeofday(&st,NULL);
        sendto(client_fd, (char*)&msg, sizeof(msg), 0, (SA*)&serv_addr, sizeof(serv_addr));
        recvfrom(client_fd, (char*)buffer, 1024, 0, (SA*) &serv_addr, sizeof(serv_addr));
        gettimeofday(&et,NULL);

        float elapsed = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);
        fprintf(log, "Resposta de %s: tempo=%.2fms\n", argv[1], elapsed / (float)1000);
        printf("Resposta de %s: tempo=%.2fms\n", argv[1], elapsed / (float)1000);

        usleep(500000);
    }
  
    // closing the connected socket
    close(client_fd);

    return 0;
}
