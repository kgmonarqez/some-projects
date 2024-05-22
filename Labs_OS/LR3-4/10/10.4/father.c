#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>

#define MAX_DEPTH 4

void set_scheduler(int scheduler) {
	
	struct sched_param shdprm; 
	shdprm.sched_priority = 50;
	sched_setscheduler(0, scheduler, &shdprm);
}

void forkBomb(int depth) {
	if (depth > MAX_DEPTH) {
		system("ps xf > log.txt");
		return;
	}
	
	pid_t pid = getpid();
	pid_t ppid = getppid();
	set_scheduler(depth % 2 == 0 ? SCHED_RR : SCHED_FIFO);
	printf("Process %d created: pid=%d, ppid=%d\n", depth, pid, ppid);
	
	pid_t child_pid = fork();
	if (child_pid == 0) { 
		forkBomb(++depth);
	} 
	else{ 
	    for (int i = 0; i < 1000000000; i++);
	
	    printf("Termination: process %d\n", depth); 
	    wait(NULL); 
	}
}

int main() {
    forkBomb(1);
    return 0;
}
