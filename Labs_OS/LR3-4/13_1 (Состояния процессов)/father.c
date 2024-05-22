#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    if(argc < 2){                   // Проверка на наличие каких либо аргументов на входе (помимо вызова программы)
        puts("failed");             // Вывод сообщения о неудаче и выход из программы
        return -1;
    }
  
    pid_t pid = getpid();             // PID (Process ID) - идентификтор процесса. getpid() - получение PID
    pid_t ppid = getppid();           // PPID (Parent Process ID) - идентификатор процесса-родителя. getppid() - получение PPID
    pid_t sid = getsid(pid);             // SID (Session ID) - идентификтор текущей сессии. getsid() - получение SID
    pid_t pidCopy;
    int status;
    char command[64];
    
    sprintf(command, "ps xjf | grep \"STAT\\|%d\" > %s", pid, argv[1]);  // Сохранение команды для вывода текущих процессов в строку
    printf("Father info: sid = %i pid=%i ppid=%i \n", sid, pid, ppid);    // Вывод информации о процессе-отце

    if((pidCopy = fork()) == 0){            // Клонирование текущего процесса для пункта a)
        execl("son_a", "son_a", argv[1], NULL);      // Замена текущего образа процесса на новый (просто говоря порождение другого процесса)
    }
    if(fork() == 0){                        
        execl("son_b", "son_b", argv[1], NULL);      // То же самое, но для пункта б)
    }
    if(fork() == 0){
        execl("son_c", "son_c", argv[1], NULL);      // То же самое, но для пункта в)
    }

    system(command);        // Исполнение команды, сохраненной ранее
    waitpid(pidCopy, &status, WNOHANG);     // Ожидание завершения процесса son_a. WNOHANG - флаг текущей команды, 
                                            // предназначеный для немедленного возвращения управления, если ни один из текущих потомков не завершился
    return 0;
}
