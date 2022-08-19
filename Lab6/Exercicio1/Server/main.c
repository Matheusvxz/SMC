// #include <netinet/in.h>
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <unistd.h>

// #define PORT            8080
// #define BUFFER_SIZE     1024

// int main(int argc, char const *argv[])
// {
//     printf("\nStarting server\n");
//     int sock = 0, num;
//     char buffer[BUFFER_SIZE];
//     struct sockaddr_in serv_addr, client_addr;
//     char message[100] = "Send response";
//     if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
//         printf("\n Socket creation error \n");
//         return -1;
//     }
//     serv_addr.sin_family = AF_INET;
//     serv_addr.sin_addr.s_addr = INADDR_ANY;
//     serv_addr.sin_port = htons(PORT);

//     bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

//     while (1)
//     {
//         printf("\nFirst loop\n");
//         num = recvfrom(sock, buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)&client_addr, sizeof(client_addr));
//         printf("\npassou aqui\n");
//         if(buffer[0] == 'x') break;
//         buffer[num] = '\0';
//         sprintf("%s\n", buffer);
//         sendto(sock, &message, strlen(message), MSG_CONFIRM, (struct sockaddr*)&client_addr, sizeof(client_addr));
//     }
//     close(sock);

//     return 0;
// }


// int main(int argc, char const *argv[])
// {
//     int sock, len, num, count = 1;
//     char buffer[1024];
//     struct sockaddr_in serveraddr, clientaddr;
//     char msg[26] = "Hello from Raspberry Pi";

//     sock = socket(AF_INET, SOCK_DGRAM, 0);
//     len = sizeof(clientaddr);

//     serveraddr.sin_family = AF_INET;
//     serveraddr.sin_addr.s_addr = INADDR_ANY;
//     serveraddr.sin_port = htons(5000);
//     bind(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

//     while(1) {
//         num = recvfrom(sock, buffer, 1024, MSG_WAITALL, (struct sockaddr*)&clientaddr, &len);
//         if(buffer[0] == 'x') break;
//         buffer[num] = '\0';
//         printf("%s\n", buffer);
//         sprintf(&msg[24], "%d", count);
//         count++;
//         sendto(sock, &msg, strlen(msg), MSG_CONFIRM, (struct sockaddr*)&clientaddr, len);

//     }
//     close(sock);
//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


/* Server port  */
#define PORT 4242


/* Buffer length */
#define BUFFER_LENGTH 4096



/*
 * Main execution of the server program of the simple protocol
 */
int
main(void) {

    /* Client and Server socket structures */
    struct sockaddr_in client, server;

    /* File descriptors of client and server */
    int serverfd, clientfd;

    char buffer[BUFFER_LENGTH];

    fprintf(stdout, "Starting server\n");

    /* Creates a IPv4 socket */
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverfd == -1) {
        perror("Can't create the server socket:");
        return EXIT_FAILURE;
    }
    fprintf(stdout, "Server socket created with fd: %d\n", serverfd);


    /* Defines the server socket properties */
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    memset(server.sin_zero, 0x0, 8);


    /* Handle the error of the port already in use */
    int yes = 1;
    if(setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR,
                  &yes, sizeof(int)) == -1) {
        perror("Socket options error:");
        return EXIT_FAILURE;
    }


    /* bind the socket to a port */
    if(bind(serverfd, (struct sockaddr*)&server, sizeof(server)) == -1 ) {
        perror("Socket bind error:");
        return EXIT_FAILURE;
    }


    /* Starts to wait connections from clients */
    if(listen(serverfd, 1) == -1) {
        perror("Listen error:");
        return EXIT_FAILURE;
    }
    fprintf(stdout, "Listening on port %d\n", PORT);

    socklen_t client_len = sizeof(client);
    if ((clientfd=accept(serverfd,
        (struct sockaddr *) &client, &client_len )) == -1) {
        perror("Accept error:");
        return EXIT_FAILURE;
    }
    
    while(1) {

      /* Copies into buffer our welcome messaage */
        strcpy(buffer, "Hello, client!\n\0");

        /* Sends the message to the client */
        if (send(clientfd, buffer, strlen(buffer), 0)) {
            fprintf(stdout, "Client connected.\nWaiting for client message ...\n");

            /* Communicates with the client until bye message come */
            do {

                /* Zeroing buffers */
                memset(buffer, 0x0, BUFFER_LENGTH);

                /* Receives client message */
                int message_len;
                if((message_len = recv(clientfd, buffer, BUFFER_LENGTH, 0)) > 0) {
                    buffer[message_len - 1] = '\0';
                    printf("Client says: %s\n", buffer);
                }


                /* 'bye' message finishes the connection */
                if(strcmp(buffer, "bye") == 0) {
                    send(clientfd, "bye", 3, 0);
                } else {
                    send(clientfd, "yep\n", 4, 0);
                }

            } while(strcmp(buffer, "bye"));
        }
        
    }

    /* Client connection Close */
    close(clientfd);


    /* Close the local socket */
    close(serverfd);

    printf("Connection closed\n\n");

    return EXIT_SUCCESS;
}
