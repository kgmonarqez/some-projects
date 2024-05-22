#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int i, pid[6], ppid, status, result;
    pid[0]=getpid();  //возвращает идентификатор процесса
    ppid=getppid();   //возвращает идентификатор процесса, являющегося родительским по отношению к вызвавшему процессу
    printf("\nFather parameters was: pid=%i ppid=%i\n", pid[0],ppid);

    if((pid[1] = fork()) == 0)
    {
        execl("son1", "son1", NULL); //execl() позволяет запускать программу с помощью списка аргументов (подробнеее в отчёте)
    }
    if((pid[2] = fork()) == 0)      //создания нового процесса
    {
        execl("son2", "son2", NULL);
    }
    if((pid[3] = fork()) == 0)
    {
        execl("son3", "son3", NULL);
    }
    if((pid[4] = fork()) == 0)
    {
        execl("son4", "son4", NULL);
    }
    if((pid[5] = fork()) == 0)
    {
        execl("son5", "son5", NULL);
    }

    system("ps xf > log.txt");
    for (i = 1; i < 6; i++)
    {
        // WUNTRACED - сообщает статус остановленного процесса-потомка
        result = waitpid(pid[i], &status, WUNTRACED);
        printf("\n%d) Child proccess with pid = %d is finished with status %d\n", i, result, status);
    }

    return 0;
}
