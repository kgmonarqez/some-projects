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
    if(sigaction(sig, &act, &oldact) < 0){
        return SIG_ERR;
    }
    return act.sa_handler;
}

void firstGroupSignalHandler(int sig){
    printf("First-group signal: %d\n", sig);
}

void secondGroupSignalHandler(int sig){
    printf("\tSecond-group signal: %d\n", sig);
}

int main() {
    int signals[] = {SIGUSR1, SIGUSR2, SIGQUIT, SIGINT, SIGSYS};
    for(int i = 0; i < sizeof(signals)/sizeof(int); i++){
    	if(i%2){
    	    mysig(signals[i], firstGroupSignalHandler);
    	}
    	else{
    	    mysig(signals[i], secondGroupSignalHandler);
    	}
    }

    for(int i = 0; i < sizeof(signals)/sizeof(int); i++){
    	kill(getpid(), signals[i]);
	sleep(1);
    }
    
    kill(getpid(), SIGKILL);
    return 0;
}

