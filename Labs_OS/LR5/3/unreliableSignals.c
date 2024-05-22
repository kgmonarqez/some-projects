#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void h(int sig){
    for(int i = 1; i <= 10; i++){
    	if(sig == SIGUSR1){
    	    printf("SIGUSR1: %d\n", i);
    	    if(i == 3){
    	    	kill(getpid(), SIGINT);
    	    }
    	    if(i == 7){
    	    	puts("SIGQUIT sent");
    	        kill(getpid(), SIGQUIT);
    	    }
    	}
    	else if(sig == SIGINT){
    	    printf("\tSIGINT: %d\n", i);
    	}
    	sleep(1);
    }
}

int main(){
    signal(SIGUSR1, h);
    signal(SIGINT, h);
    signal(SIGQUIT, SIG_DFL);
    kill(getpid(), SIGUSR1);
    sleep(5);
}
