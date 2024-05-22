#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define DEF_FILENAME "info.txt"
#define N 100

void createOutput(char* fifoName){
    int res = mknod(fifoName, S_IFIFO | 0666, 0);
    if (res && errno!=EEXIST) {
        printf("Can't create %s channel\n", fifoName);
        exit(1);
    }
    puts("Server output channel created");
}

int openOutput(char* fifoName){     // Инициализация канала отправки информации
    int serverOutput = open(fifoName, O_WRONLY);
    if (serverOutput == -1) {
        printf("Can't open %s channel from server\n", fifoName);
        exit(0);
    }
    puts("Server output channel opened");
    
    return serverOutput;
}

void createInput(char* fifoName){
    int res = mknod(fifoName, S_IFIFO | 0666, 0);
    if (res && errno!=EEXIST) {
        printf("Can't create %s channel\n", fifoName);
        exit(1);
    }
    puts("Server input channel created");
}

int openInput(char* fifoName){      // Инициализация канала получения информации
    int serverInput = open(fifoName, O_RDONLY);
    if (serverInput == -1) {
        printf("Can't open %s channel from server\n", fifoName);
        exit(0);
    }
    puts("Server input channel opened");

    return serverInput;
}

int main(int argc, char **argv) {
    char fileName[30];
    if (argc < 2){
        strcpy(fileName, DEF_FILENAME);
    }
    else{
        strcpy(fileName, argv[1]);
    }
    
    char* outputName = "serverOutput";
    char* inputName = "serverInput";
    
    // Создание и открытие каналов получения и отправки информации
    createOutput(outputName);
    createInput(inputName);
    int output = openOutput(outputName);
    int input = openInput(inputName);

    write(output, fileName, strlen(fileName));
    char buf[N+1];
    puts("\n-----Client's info-----");
    while(1){
        bzero(buf, N);
        int res = read(input, buf, N);
        if (res <= 0){
            break;
        }
        buf[N] = '\0';
        printf("%s", buf);
    }
    puts("");
    close(output);
    close(input);
    unlink(outputName);
    unlink(inputName);
    return 0;
}
