#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "shm.h"
#include <string.h>
int* buf;
int main(int argc, char** argv) {
    char keyFile[100];
    bzero(keyFile,100);
    if(argc < 2) {
        printf("Default file-key: %s\n",DEF_KEY_FILE);
        strcpy(keyFile,DEF_KEY_FILE);
    } else
        strcpy(keyFile,argv[1]);
    key_t key;
    int shmemory;
    int semaphore;
    // Будем использовать один и тот же ключ для семафора и разделяемой памяти
    if((key = ftok(keyFile, 'Q')) < 0) {
        printf("Can't ged key %s and id 'Q'\n",keyFile);
        exit(1);
    }
    // Создание разделяемой памяти
    if((shmemory = shmget(key, (BUF_SIZE+1)*sizeof(int), 0666)) < 0) {
        printf("Can't create separated memory\n");
        exit(1);
    }
    // Присоединение разделяемой памяти к адресному пространству процесса
    if((buf = (int*)shmat(shmemory, 0, 0)) < 0) {
        printf("Can't connect separated memory\n");
        exit(1);
    }
    // Создание семафора
    if((semaphore = semget(key, 2, 0666)) < 0) {
        printf("Error while creating semaphore\n");
        exit(1);
    }

    int send = 0;
    char tb[10];
    int i = 0;
    for(i = 0; i < 10;++i) {
        // Ждем, пока будет хоть одна свободная ячейка
        if(semop(semaphore, waitNotFull, 1) < 0) {
            printf("Operation error\n");
            exit(1);
        }
        // Ждем доступа к разделяемой памяти
        if(semop(semaphore, mem_lock, 1) < 0) {
            printf("Operation error\n");
            exit(1);
        }
        printf("Adding %d to cell %d\n",send,buf[BUF_SIZE]+1);
        ++buf[BUF_SIZE];
        buf[buf[BUF_SIZE]] = send++;
        // Освобождаем доступ к памяти
        if(semop(semaphore, mem_unlock, 1) < 0) {
            printf("Operation error\n");
            exit(1);
        }
        // Увеличиваем число занятых ячеек
        if(semop(semaphore, releaseFull, 1) < 0) {
            printf("Operation error\n");
            exit(1);
        }
    }
    // Отключение от области разделяемой памяти
    shmdt(buf);
    return 0;
}
