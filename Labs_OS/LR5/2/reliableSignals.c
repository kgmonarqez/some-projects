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

void signalHandler(int sig){
    if(sig == SIGUSR1){
    	printf("SIGUSR1 caught\n");
    	sleep(1);
    }
    else if(sig == SIGUSR2){
    	printf("SIGUSR2 caught\n");
    	sleep(1);
    }
    else if(sig == SIGQUIT){
    	printf("SIGQUIT caught\n");
    	sleep(1);
    }
    else if(sig == SIGINT){
    	printf("SIGINT caught\n");
    	sleep(1);
    }
    else if(sig == SIGSYS){
    	printf("Processing SIGSYS for 10 seconds\n");
    	kill(getpid(), SIGINT);
    	kill(getpid(), SIGINT);
    	kill(getpid(), SIGUSR1);
    	kill(getpid(), SIGUSR2);
    	kill(getpid(), SIGUSR1);
    	kill(getpid(), SIGQUIT);
    	kill(getpid(), SIGUSR2);
    	for(int i = 1; i <= 10; i++){
    	    printf("%d\n", i);
    	    sleep(1);
    	}
    }
    else{
    	puts("Unknown signal");
    }
}

int main() {   
    int signals[] = {SIGUSR1, SIGUSR2, SIGQUIT, SIGINT, SIGSYS};
    for(int i = 0; i < sizeof(signals)/sizeof(int); i++){
    	mysig(signals[i], signalHandler);
    }

    kill(getpid(), SIGSYS);
    
    return 0;
}

