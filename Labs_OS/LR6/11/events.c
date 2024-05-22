#include <stdio.h>
#include <unistd.h>
#include <sys/eventfd.h>
#include <poll.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define W 1
#define A 2
#define S 3
#define D 4
#define QUIT 5
#define UNKNOWN 6

void sendMessage(int efd, uint64_t eventType){
    write(efd, &eventType, sizeof(uint64_t));
}

uint64_t readMessage(int efd){
    uint64_t eventType;
    read(efd, &eventType, sizeof(uint64_t));
    switch(eventType){
        case W:
            puts("User moved UP");
            break;
        case A:
            puts("User moved LEFT");
            break;    
        case S:
            puts("User moved DOWN");
            break;
        case D:
            puts("User moved RIGHT");
            break;
        case QUIT:
            puts("User quit simulator");
            break;
        case UNKNOWN:
            puts("Unknown action from user");
            break;
    }
    return eventType;
}

int getMove(char* move){
    if(!strcmp(move, "W")){
        return W;
    }
    else if(!strcmp(move, "A")){
        return A;
    }
    else if(!strcmp(move, "S")){
        return S;
    }
    else if(!strcmp(move, "D")){
        return D;
    }
    else if(!strcmp(move, "QUIT")){
        return QUIT;
    }
    return UNKNOWN;
}

int main(){
    int efd = eventfd(0, 0);
    if (efd == -1){
        perror("eventfd");
        exit(EXIT_FAILURE);
    }

    if(fork() == 0){
        struct pollfd pfd[1];
        pfd[0].fd = efd;
        pfd[0].events = POLLIN;
        while(1){
            int ret = poll(pfd, 1, -1);
            if (ret == -1) {
                perror("poll");
                exit(EXIT_FAILURE);
            }

            if(readMessage(efd) == QUIT){
                exit(EXIT_SUCCESS);
            }
        }
    }

    char buf[100];
    while(1){
        bzero(buf, 100);
        fgets(buf, 100, stdin);
        buf[strlen(buf) - 1] = '\0';
        int move = getMove(buf);
        sendMessage(efd, move);
        if(move == QUIT){
            break;
        }
    }

    close(efd);
}