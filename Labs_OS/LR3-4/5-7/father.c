#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

int main(){
    int pid, ppid, status;
    pid = getpid();
    ppid = getppid();
    printf("PARENT PROC: pid=%i, ppid=%i\n", pid, ppid);
    if(fork() == 0){
        execl("son.out", "son.out", NULL);
    }
    system("ps -xf > proc_table.txt");
    wait(&status);
    printf("Дочерний процесс завершился со статусом %d\n", status);
}
