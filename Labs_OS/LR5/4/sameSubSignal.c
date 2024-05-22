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
    sigfillset(&act.sa_mask);
    if(sigaction(sig, &act, &oldact) < 0){
        return SIG_ERR;
    }
    return act.sa_handler;
}

void sigusr1Handler(int sig){
    puts("SIGUSR1 caught");    
    kill(getpid(), SIGUSR1);
    for(int i = 1; i <= 10; i++){
    	printf("SIGUSR1: %d\n", i);
    	sleep(1);
    }
}

int main() {   
    mysig(SIGUSR1, sigusr1Handler);

    kill(getpid(), SIGUSR1);
    
    return 0;
}

