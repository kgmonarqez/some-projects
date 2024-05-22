#include <signal.h>
#include <stdio.h>
#include <sched.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


void signalActions(int sig_no){     // Действия при обработке полученного сигнала
    time_t s = time(NULL);
    printf("Passive son1 received signal at %s\n", ctime(&s));
    exit(0);
}

int main() {
    signal(SIGUSR1, signalActions); // Вызов функции signalActions()
    printf("son1 running\n");
    sleep(3);
    return 0;
}