#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <unistd.h>

void sigrtminHandler(int sig) {                             // Обработка сигнала
    puts("SIGRTMIN caught");
    kill(getpid(), SIGRTMIN+1);
    kill(getpid(), SIGRTMIN+2);
    kill(getpid(), SIGRTMIN+3);
    kill(getpid(), SIGRTMIN+4);
    kill(getpid(), SIGRTMIN+5);
}

void sigrtmin1Handler(int sig) {                             // Обработка сигнала
    puts("SIGRTMIN+1 caught");
    kill(getpid(), SIGRTMIN+2);
    kill(getpid(), SIGRTMIN+3);
    kill(getpid(), SIGRTMIN+4);
    kill(getpid(), SIGRTMIN+5);
}

void sigrtmin2Handler(int sig) {                             // Обработка сигнала
    puts("SIGRTMIN+2 caught");
    kill(getpid(), SIGRTMIN+3);
    kill(getpid(), SIGRTMIN+4);
    kill(getpid(), SIGRTMIN+5);
}

void sigrtmin3Handler(int sig) {                             // Обработка сигнала
    puts("SIGRTMIN+3 caught");
    kill(getpid(), SIGRTMIN+4);
    kill(getpid(), SIGRTMIN+5);
}

void sigrtmin4Handler(int sig) {                             // Обработка сигнала
    puts("SIGRTMIN+4 caught");
    kill(getpid(), SIGRTMIN+5);
}

void sigrtmin5Handler(int sig) {                             // Обработка сигнала
    puts("SIGRTMIN+5 caught");
}

void (*mysig(int sig,void (*hnd)(int)))(int){       
    struct sigaction act, oldact;           // Структура для изменения действия конкретных сигналов
    act.sa_handler = hnd;           // Помещение функции обработки в структуру
    //sigfillset(&act.sa_mask);      // Применение маски со всеми сигналами для блокировки
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;               
    if(sigaction(sig, &act, &oldact) < 0){  // Обновление инструкции обработки сигнала sig
        return SIG_ERR;
    }
    return act.sa_handler;
}

int main(){
    char command[64];
    sprintf(command, "taskset -p 0x1 %d", getpid());
    system(command);
    mysig(SIGRTMIN, sigrtminHandler);
    mysig(SIGRTMIN+1, sigrtmin1Handler);
    mysig(SIGRTMIN+2, sigrtmin2Handler);
    mysig(SIGRTMIN+3, sigrtmin3Handler);
    mysig(SIGRTMIN+4, sigrtmin4Handler);   
    mysig(SIGRTMIN+5, sigrtmin5Handler);
    kill(getpid(), SIGRTMIN);
}
