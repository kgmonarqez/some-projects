#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define IP "127.0.0.1"
#define PORT 8888
#define BUF_SIZE 100

int readMessage(int sock, char* buf, int bufSize, int flags) { // Чтение из сокета
    unsigned n = 0;
    int res = recv(sock, &n, sizeof(unsigned), flags | MSG_WAITALL);

    if (res <= 0){
        return res;
    }

    if (res > bufSize) {
        puts("Data overflow\n");
        exit(1);
      }
    
    return recv(sock, buf, n, flags | MSG_WAITALL);
}

int sendMessage(int sock, char* buf, int flags) { // Запись в сокет
    unsigned n = strlen(buf);
    int res = send(sock, &n, sizeof(unsigned), flags);

    if (res <= 0)
        return res;

    send(sock, buf, n, flags);
}

int main(int argc, char** argv) {
    int port;
    char* ip;
    if(argc < 2){
        printf("Using default IP adress: %s\n", IP);
        ip = IP;
    }
    else{
        ip = argv[1];
    }

    if(argc < 3){
        printf("Using default port: %d\n", PORT);
        port = PORT;
    }
    else{
        port = atoi(argv[2]);
    }
    printf("\tIP: %s\n", ip);
    printf("\tPort: %d\n", port);

    int clientSocket;
    struct sockaddr_in server_addr;

    // Создание сокета
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Настройка сервера
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    // Подключение к серверу
    if (connect(clientSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");

    char buf[BUF_SIZE+1];
    // Отправка и прием сообщений
    while (1) {
        printf("Enter message: ");
        fgets(buf, BUF_SIZE, stdin);
        buf[strlen(buf) - 1] = '\0';
        /*if(strlen(buf) == 0){
            puts("Shutting down...");
            break;
        }*/

        if (sendMessage(clientSocket, buf, 0) == -1) {
            perror("Send failed");
            break;
        }

        ssize_t n = readMessage(clientSocket, buf, BUF_SIZE, 0);
        if (n <= 0) {
            perror("Receive failed");
            break;
        }
        buf[n] = '\0';
        printf("Received message: %s\n", buf);
    }

    // Закрытие сокета
    close(clientSocket);

    return 0;
}

