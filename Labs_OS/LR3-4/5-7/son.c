#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

int main(){
    int pid, ppid;
    pid = getpid();
    ppid = getppid();
    printf("SON PROC: pid=%i, ppid=%i\n", pid, ppid);
    sleep(8); 
    return 0;
}
