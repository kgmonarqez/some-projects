#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>

#define MAX_DEPTH 5

void set_scheduler(){
    struct sched_param sp;
    sp.sched_priority = 49;
    sched_setscheduler(0, SCHED_FIFO, &sp);
}

void forkBomb(int depth){
    if(depth > MAX_DEPTH){
    	system("ps xf > log.txt");
        return;
    }
    pid_t pid = getpid();
    pid_t ppid = getppid();
    printf("Process %d created: pid=%d, ppid=%d\n", depth, pid, ppid);

    pid_t child_pid = fork();
    if(child_pid == 0){
        forkBomb(++depth);
    }
    else{
        for(int i = 0; i < 100000000; i++);
        printf("Termination: process %d\n", depth);
        wait(NULL);
    }
}

int main(int argc, char* argv[]){
    //set_scheduler();
    forkBomb(1);
    return 0;
}
