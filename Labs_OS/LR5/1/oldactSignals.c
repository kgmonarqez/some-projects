#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

struct sigaction mysig(int sig,void (*handler)(int)){
    struct sigaction act, oldact;           
    act.sa_handler = handler;            
    act.sa_flags = 0;               
    if(sig == SIGBUS){
    	sigfillset(&act.sa_mask);
    }
    if(sigaction(sig, &act, &oldact) < 0){
	exit(1);
    }
    return oldact;
}

void signalHandler(int sig){
    printf("Signal %d\n", sig);
}

int main() {  
    int signals[] = {SIGUSR1, SIGUSR2, SIGQUIT, SIGINT, SIGSYS};
    struct sigaction oldacts[sizeof(signals)/sizeof(int)];
    for(int i = 0; i < sizeof(signals)/sizeof(int); i++){
    	oldacts[i] = mysig(signals[i], signalHandler);
    }
    
    for(int i = 0; i < sizeof(signals)/sizeof(int); i++){
    	kill(getpid(), signals[i]);
    	sigaction(signals[i], &oldacts[i], NULL);
    }
    
    while(1);
    return 0;
}

