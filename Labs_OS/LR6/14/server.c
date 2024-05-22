#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 8888
#define BUF_SIZE 100
#define IP "127.0.0.1"

struct clientInfo{
    int client;
    int clientNum;
};

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


void* clientHandler(void* arg) {//
    struct clientInfo* newClientInfo = (struct clientInfo*)arg;
    int client = newClientInfo->client;
    int clientNum = newClientInfo->clientNum;
    char buf[BUF_SIZE+1];

    while(1) {  // Режим ожидания взаимодействия с клиентом
        bzero(buf, BUF_SIZE);
        ssize_t n = readMessage(client, buf, BUF_SIZE, 0);
        buf[n] = '\0';

        if (n <= 0) {
            perror("Some client terminated connection");
            pthread_exit(NULL);
        }
        printf("Client %d sent: %s\n", clientNum, buf);

        n = sendMessage(client, "OK", 0);
        if (n <= 0) {
            perror("send call failed");
            pthread_exit(NULL);
        }
    }
}

int main(int argc, char** argv) {
    int port;

    if(argc < 2){
        printf("Using default port: %d\n", PORT);
        port = PORT;
    }
    else{
        port = atoi(argv[1]);
    }
    puts("Creating a new server");
    printf("\tPort: %d\n", port);

    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_len = sizeof(clientAddr);

    // Создание сокета
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Настройка сервера
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    // Привязка сокета к адресу и порту
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Прослушивание подключений
    if (listen(serverSocket, 5) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server started. Waiting for connections...\n");

    // Прием и отправка сообщений
    int n = 1;
    while (1) {
        struct clientInfo newClient = {accept(serverSocket, NULL, NULL), n};
        pthread_t t;
        if(pthread_create(&t, NULL, clientHandler, (void *)(&newClient))){
            puts("Error while accepting new client");
        }
        printf("Client №%d connected\n", n);
        n++;
    }

    // Закрытие сокетов
    close(clientSocket);
    close(serverSocket);

    return 0;
}

