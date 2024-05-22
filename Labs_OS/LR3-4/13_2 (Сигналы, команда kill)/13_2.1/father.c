#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){ 
    if(argc < 2){           // Проверка на наличие аргумента при вызове программы
        puts("failed");     // Выход из программы в случае недостаточного кол-ва аргументов
        return -1;
    }

    pid_t pid1, pid2, pid3; // PID процессов-сыновей
    int status;             
    char command[128];      // Команда для исполнения в терминале

    if((pid1 = fork()) == 0){           // Последовательное формирование процессов-сыновей
        execl("son1", "son1", NULL);
    }
    if((pid2 = fork()) == 0){
        execl("son2", "son2", NULL);
    }
    if((pid3 = fork()) == 0){
        execl("son3", "son3", argv[1], NULL);
    }

    sprintf(command, "echo Active processes: > %s && ps -l >> %s", argv[1], argv[1]);   // Формирование команды для вывода команды ps -l в отдельный файл
    system(command);    // Исполнение получившейся команды

    kill(pid1, SIGUSR1);    // Посыл пользовательского сигнала SIGUSR1 трем сыновьям
    kill(pid2, SIGUSR1);
    kill(pid3, SIGUSR1);
    
    sprintf(command, "echo >> %s && echo Proceses after sending signal: >> %s && ps -l >> %s", argv[1], argv[1], argv[1]);  // Формирование команды
    system(command);    // Исполнение получившейнся команды
}