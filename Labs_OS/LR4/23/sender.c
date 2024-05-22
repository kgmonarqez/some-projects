#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
 
int main() {
    pid_t target_pid;
    printf("Enter PID of the target process: ");
    scanf("%d", &target_pid);
    
    printf("Sending signal to process with PID %d\n", target_pid);
    kill(target_pid, SIGRTMIN);
    
    return 0;
}
