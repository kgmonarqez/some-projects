#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[]){ 
    if(argc < 2){           // Проверка на наличие аргумента при вызове программы
        puts("failed");     // Выход из программы в случае недостаточного кол-ва аргументов
        return -1;
    }

    pid_t pid1, pid2; // PID процессов-сыновей
    int status;             
    char command[128];      // Команда для исполнения в терминале

    if((pid1 = fork()) == 0){           // Последовательное формирование процессов-сыновей
        execl("son1", "son1", NULL);
    }
    if((pid2 = fork()) == 0){
        execl("son2", "son2", NULL);
    }

    sprintf(command, "ps > %s", argv[1]);
    system(command);

    kill(pid1, SIGUSR1);
    kill(pid2, SIGUSR1);

    time_t s = time(NULL);          // Замер времени когда посланы все сигналы
    printf("Signals sent at %s", ctime(&s));
    sleep(2);
    sprintf(command, "echo >> %s && ps >> %s", argv[1], argv[1]);
    system(command);

    return 0;
}