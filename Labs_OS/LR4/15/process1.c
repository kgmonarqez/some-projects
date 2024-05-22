#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>

void aahh(){
    for(int i = 0; i < 1000000000; i++);
}

int main() {
    char command[100];
    sprintf(command, "taskset -p 0x1 %d > /dev/null", getpid());
    system(command);
    printf("Process 1 priority: %d\n", getpriority(PRIO_PROCESS, 0));
    for(int i = 0; i < 5; ++i) {
        printf("Process 1: iteration %d\n", i);
	aahh();
    }
    return 0;
}
