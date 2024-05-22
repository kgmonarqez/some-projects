#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <unistd.h>

void sigrtmaxHandler(int sig, siginfo_t* info, void* p){
    puts("SIGRTMAX started");
    for(int i = 1; i <= 10; i++){
        union sigval val;
        val.sival_int = i;
        sigqueue(getpid(), SIGRTMIN+1, val);
    }
    puts("Signals sent, 3 seconds pause");
    sleep(3);
}

void sigrtmin1Handler(int sig, siginfo_t* info, void* p){
    printf("SIGRTMIN+1 №%d\n", info->si_value.sival_int);
}

void (*mysig(int sig,void (*hnd)(int, siginfo_t*, void*)))(int){       
    struct sigaction act, oldact;           // Структура для изменения действия конкретных сигналов
    act.sa_sigaction = hnd;           // Помещение функции обработки в структуру
    sigfillset(&act.sa_mask);      // Применение маски со всеми сигналами для блокировки
    act.sa_flags = SA_SIGINFO;               
    if(sigaction(sig, &act, &oldact) < 0){  // Обновление инструкции обработки сигнала sig
        return SIG_ERR;
    }
    return act.sa_handler;
}

int main(){
    char command[64];
    sprintf(command, "taskset -p 0x1 %d", getpid());
    system(command);
    mysig(SIGRTMAX, sigrtmaxHandler); 
    mysig(SIGRTMIN+1, sigrtmin1Handler);
    kill(getpid(), SIGRTMAX);
}
