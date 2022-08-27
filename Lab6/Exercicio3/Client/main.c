#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    int sock = 0, valread, client_fd;
    struct sockaddr_in serv_addr;
    char msg[200];
    char buffer[1024] = { 0 };

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(28390);

    if((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))) {
        printf("\nInvalid address.\n");
        return -1;
    }
 
    int n;
    FILE *log = fopen("log.txt", "w");

    if(log == NULL) {
        printf("Error! Could not open file\n");
        return -1;
    }

    sprintf(msg,"packet");
    clock_t t;

    for(n = 0; n < 20; n++) {
        t = clock();
        send(sock, msg, sizeof(msg), 0);
        valread = read(sock, buffer, 1024);
        t = clock() - t;
        double timeTaken = ((double)t)/(CLOCKS_PER_SEC / 1000);
        fprintf(log, "Resposta de %s: tempo=%.2fms\n", argv[1], timeTaken);
        printf("Resposta de %s: tempo=%.2fms\n", argv[1], timeTaken);

        usleep(500000);
    }

    fclose(log);
  
    // closing the connected socket
    close(client_fd);

    return 0;
}
