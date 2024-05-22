#include <sched.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int pid = getpid();     // Взятие PID
	int ppid = getppid();   // Взятие PPID

	printf("Son_c info: pid = %i, ppid = %i\nSon_c terminated before father, it is zombie now\n", pid, ppid);    // Вывод информации
	
    return 0;
}