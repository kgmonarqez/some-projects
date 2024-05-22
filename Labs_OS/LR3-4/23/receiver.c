#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
 
void handle_signal(int sig) {
    printf("Received signal %d\n", sig);
    exit(EXIT_SUCCESS); // Завершаем работу программы после получения сигнала
}
 
int main() {
    printf("My PID is %d\n", getpid());
    
    signal(SIGRTMIN, handle_signal);
    
    while(1) {
        printf("Waiting for signal...\n");
        sleep(1);
    }
    
    return 0;
}
