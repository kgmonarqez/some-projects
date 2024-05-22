#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define DEF_PORT 8888
#define DEF_IP "127.0.0.1"

int main(int argc, char** argv) {
    char* addr = (argc < 2) ? DEF_IP : argv[1];
    int port = (argc < 3) ? DEF_PORT : atoi(argv[2]);

    struct sockaddr_in serverAddr;
    socklen_t serverAddrLen = sizeof(serverAddr);

    char buffer[100];
    int clientSocket;

    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Can't create socket");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(addr);

    printf("Send a message (type empty string to quit)\n");

    while (1) {
        printf("> ");
        //fgets(buffer, sizeof(buffer), stdin);
        sprintf(buffer, "HI");
        //buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) == 0) {
            puts("Shutting down...");
            break;
        }

        ssize_t sendLen = sendto(clientSocket, buffer, strlen(buffer), 0, (struct sockaddr *)&serverAddr, serverAddrLen);
        if (sendLen < 0) {
            perror("Can't send message");
            exit(EXIT_FAILURE);
        }

        ssize_t recvLen = recvfrom(clientSocket, buffer, sizeof(buffer), 0, NULL, NULL);
        if (recvLen < 0) {
            perror("Can't get server feedback");
            exit(EXIT_FAILURE);
        }

        buffer[recvLen] = '\0';
        printf("Server feedback: %s\n", buffer);
        break;
    }

    close(clientSocket);
    return 0;
}

