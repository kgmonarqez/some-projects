#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void signalActions(){
    puts("Signal SIGUSR1 appears!");    // Вывод простого сообщения в терминал
}

int main(){
    signal(SIGUSR1, signalActions);     // Действие при получение сигнала SIGUSR1: вызвать функцию signalActions()
    sleep(5);   // Задержка, чтобы процесс не закончился быстрее отца
    return 0;
}