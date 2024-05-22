#include <signal.h>
#include <stdio.h>
#include <sched.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


void signalActions(int sig_no){
    time_t s = time(NULL);
    printf("Active son2 received signal at time %s\n", ctime(&s));
    exit(0);
}


int main() {
    signal(SIGUSR1, signalActions);
    printf("son2 running\n");
    while(1);
    return 0;
}