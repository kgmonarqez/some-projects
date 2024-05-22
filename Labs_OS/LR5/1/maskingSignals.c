#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void (*mysig(int sig,void (*handler)(int)))(int){
    struct sigaction act, oldact;           
    act.sa_handler = handler;            
    act.sa_flags = 0;               
    if(sig == SIGBUS){
    	sigfillset(&act.sa_mask);
    }
    if(sigaction(sig, &act, &oldact) < 0){
        return SIG_ERR;
    }
    return act.sa_handler;
}

void signalHandler(int sig){
    printf("Signal with number %d\n", sig);
}

void sigbusHandler(int sig){
    puts("SIGBUS caught: 5 sec pause");
    sleep(20);
    puts("SIGBUS procession ended");
}

int main() {
    mysig(SIGBUS, sigbusHandler);
    
    int signals[] = {SIGUSR1, SIGUSR2, SIGQUIT, SIGINT, SIGSYS};
    for(int i = 0; i < sizeof(signals)/sizeof(int); i++){
    	mysig(signals[i], signalHandler);
    }
    
    kill(getpid(), SIGBUS);
    kill(getpid(), SIGKILL);
    return 0;
}

