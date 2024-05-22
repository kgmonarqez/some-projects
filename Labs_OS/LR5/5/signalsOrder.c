#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t t1, t2;
void hnd(int sig) {                             // Обработка сигнала
    if(sig != SIGUSR1){                         // Обработка любого сигнала, отличного от SIGUSR1
        if(sig == SIGRTMIN){
            puts("Signal caught: SIGRTMIN");
        }
        else if(sig == SIGRTMIN+1){
            puts("Signal caught: SIGRTMIN+1");
        }
        else if(sig == SIGRTMIN+2){
            puts("Signal caught: SIGRTMIN+2");
        }
        else if(sig == SIGRTMIN+3){
            puts("Signal caught: SIGRTMIN+3");
        }
        else if(sig == SIGRTMIN+4){
            puts("Signal caught: SIGRTMIN+4");
        }
        else if(sig == SIGRTMIN+5){
            puts("Signal caught: SIGRTMIN+5");
        }
        else if(sig == SIGUSR2){
            puts("Signal caught: SIGUSR2");
        }
        else if(sig == SIGSYS){
            puts("Signal caught: SIGSYS");
        }
        else if(sig == SIGBUS){
            puts("Signal caught: SIGBUS");
        }
        else if(sig == SIGQUIT){
            puts("Signal caught: SIGQUIT");
        }
        else if(sig == SIGINT){
            puts("Signal caught: SIGINT");
        }
        else{
            puts("Unknown signal");
        }
    }
    else{                           // Обработка для SIGUSR1
        puts("SIGUSR1 caught");
        kill(getpid(), SIGRTMIN+1);     // Посыл различных сигналов
        kill(getpid(), SIGRTMIN+2);
        kill(getpid(), SIGRTMIN+4);
        kill(getpid(), SIGRTMIN);
        kill(getpid(), SIGINT);
        kill(getpid(), SIGRTMIN+1);
        kill(getpid(), SIGRTMIN+2);
        kill(getpid(), SIGRTMIN+2);
        kill(getpid(), SIGQUIT);
        kill(getpid(), SIGRTMIN+5);
        kill(getpid(), SIGRTMIN+3);
        kill(getpid(), SIGUSR2);
        sleep(3);
        puts("SIGUSR1 processed");
    }
}

void (*mysig(int sig,void (*hnd)(int)))(int){       
    struct sigaction act, oldact;           // Структура для изменения действия конкретных сигналов
    act.sa_handler = hnd;           // Помещение функции обработки в структуру
    sigfillset(&act.sa_mask);      // Применение маски со всеми сигналами для блокировки
    act.sa_flags = 0;               
    if(sigaction(sig, &act, &oldact) < 0){  // Обновление инструкции обработки сигнала sig
        return SIG_ERR;
    }
    return act.sa_handler;
}

void setSignalAction(){     // Установка гибкой обработки сигналов
    int signals[] = {SIGRTMIN, SIGRTMIN+1, SIGRTMIN+2, SIGRTMIN+3, SIGRTMIN+4, SIGRTMIN+5, SIGUSR2, SIGSYS, SIGBUS, SIGQUIT, SIGINT};
    for(int i = 0; i < sizeof(signals)/sizeof(int); i++){
        mysig(signals[i], hnd);
    }
}

int main(){
    char command[64];
    sprintf(command, "taskset -p 0x1 %d", getpid());
    system(command);
    mysig(SIGUSR1, hnd);
    setSignalAction();
    kill(getpid(), SIGUSR1);
}

