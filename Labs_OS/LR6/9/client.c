#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define N 100

int openOutput(char* fifoName){
    int output = open(fifoName, O_WRONLY);
    if (output == -1) {
        printf("Can't open %s channel from client\n", fifoName);
        exit(0);
    }
    
    return output;
}

int openInput(char* fifoName){
    int input = open(fifoName, O_RDONLY);
    if (input == -1) {
        printf("Can't open %s channel from client\n", fifoName);
        exit(0);
    }

    return input;
}

int main() {
    // Открытие канала получения информации от сервера
    char* inputName = "serverOutput";
    int input = openInput(inputName);

    // Открытие канала отправки информации серверу
    char* outputName = "serverInput";
    int output = openOutput(outputName);

    // Получение имени файла
    char fileName[N+1];
    bzero(fileName, N);
    int res = read(input, fileName, N);
    if(res <= 0) {
        printf("Can't read fileName from server output\n");
        exit(0);
    }
    printf("File name: %s\n", fileName);

    // Чтение из файла и отправка данных на сервер
    FILE *f = fopen(fileName, "r");
    if(!f) {
        printf("Can't open file %s\n",fileName);
        exit(0);
    }

    char buf[N+1];
    while(!feof(f)) {
        res = fread(buf, sizeof(char), N, f);
        write(output, buf, res);
    }

    fclose(f);
    close(input);
    close(output);
    return 0;
}
