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
    kill(getpid(), SIGINT);
    kill(getpid(), SIGQUIT);
    for(int i = 1; i <= 10; i++){
    	printf("SIGUSR1: %d\n", i);
    	sleep(1);
    }
}

void sigintHandler(int sig){
    puts("\tSIGINT caught");
    kill(getpid(), SIGQUIT);
    for(int i = 1; i <= 10; i++){
    	printf("\tSIGINT: %d\n", i);
    	sleep(1);
    }
}

void sigquitHandler(int sig){
    puts("\t\tSIGQUIT caught");
    for(int i = 1; i <= 10; i++){
    	printf("\t\tSIGQUIT: %d\n", i);
    	sleep(1);
    }
}

int main() {   
    mysig(SIGUSR1, sigusr1Handler);
    mysig(SIGINT, sigintHandler);
    mysig(SIGQUIT, sigquitHandler);

    kill(getpid(), SIGUSR1);
    
    return 0;
}

