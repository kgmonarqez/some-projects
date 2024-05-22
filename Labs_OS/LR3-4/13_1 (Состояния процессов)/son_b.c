#include <sched.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	pid_t pid = getpid();         // Получение PID
	pid_t ppid = getppid();       // Получение PPID
	char command[64];             // Строка с будущей командой
	
    sprintf(command, "ps xjf | grep son_b >> %s", argv[1]);      // Формирование команды
	
    printf("Son_b info: pid = %i ppid = %i\nFather finished before son termination without waiting for it \n", pid, ppid);  // Вывод информации о процессе
	sleep(10);  // Ожидание, чтобы процесс завершился после процесса-родителя
	
    ppid = getppid();
	
    printf("New changes in son_b: pid = %i, ppid = %i\n", pid, ppid);   // Повторный вывод информации 
	system(command);    // Исполнение команды в терминале
    return 0;
}