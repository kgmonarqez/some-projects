#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define DEF_PORT 8888

int main(int argc, char** argv) {
    int port = (argc < 2) ? DEF_PORT : atoi(argv[1]);
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    char buffer[100];
    int serverSocket;
    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Can't create socket");
        exit(EXIT_FAILURE);
    }
    
    memset(&serverAddr, 0, sizeof(serverAddr));
    memset(&clientAddr, 0, sizeof(clientAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Can't bind socket to port");
        exit(EXIT_FAILURE);
    }
    
    puts("Waiting for new messages...");
    while (1) {
        ssize_t recvLen = recvfrom(serverSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (recvLen < 0) {
            perror("Can't read message");
            exit(EXIT_FAILURE);
        }
        buffer[recvLen] = '\0'; 
        printf("Some client sent: %s\n", buffer);
        
        if (sendto(serverSocket, buffer, recvLen, 0, (struct sockaddr *)&clientAddr, clientAddrLen) < 0) {
            perror("Can't send message");
            exit(EXIT_FAILURE);
        }
    }
    close(serverSocket);
    return 0;
}
