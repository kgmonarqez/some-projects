#include <sched.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int pid = getpid();     // PID текущего процесса
    int ppid = getppid();   // PPID текушего процесса
    
    printf("Son_a info: pid = %i ppid = %i\nFather creates a new process and waits it to die\n", pid, ppid);
    
    sleep(3);   // Ожидание, чтобы процесс-родитель не завершился, пока не завершится данный процесс-сын
    return 0;
}