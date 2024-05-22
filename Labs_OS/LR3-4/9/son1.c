#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pid, ppid;
    pid = getpid();
    ppid = getppid();
    printf("\n Son parameters was: pid=%i, ppid=%i\n", pid, ppid);

    sleep(10);
    return 0;
}
