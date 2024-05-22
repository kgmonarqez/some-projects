#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <strings.h>

#define DEF_KEY_FILE "key"
typedef struct {    // Сообщение
	long type;      // Тип отправляемого сообщения
	char buf[100];  // Сама строка с сообщением
} Message;

int queue;
void SIGINT_action(int sig) {      // Обработчик сигнала SIGINT с удалением очереди сообщений
	signal(sig, SIG_DFL);
	if(msgctl(queue, IPC_RMID, 0) < 0) { // Проверка на успешность удаления очереди
		printf("Can't delete queue\n");
		exit(1);
	}
}

int initQueue(char* keyFile, char identificator){   // Инициализация очереди сообщений
    key_t key;                          // Ключ для создания очереди
	key = ftok(keyFile, identificator); // Преобразование имени файла и идентификатора проекта в ключ для системных вызовов
	if(key == -1) {
		printf("no got key for the key file %s and id 'Q'\n", keyFile);
		exit(1);
	}
	queue = msgget(key, IPC_CREAT | 0666);   // Создание очереди на полученном ключе
	if (queue < 0) {
		printf("Can't create queue\n");
		exit(4);
	}
    return queue;
}

int main(int argc, char** argv) {
	char keyFile[100];
	bzero(keyFile,100);
	if(argc < 2) {
		printf("Using default key file %s\n",DEF_KEY_FILE);
		strcpy(keyFile,DEF_KEY_FILE);
	}
	else{
		strcpy(keyFile,argv[1]);
    }

    queue = initQueue(keyFile, 'Q');        // Инициализация очереди
	puts("Queue created");
	puts("Waiting for any messages...");

	signal(SIGINT, SIGINT_action);      // Установка обработки SIGINT

	Message msg;    // Текущее сообщение
	int res;
	while(1){
		bzero(msg.buf, 100);
		res = msgrcv(queue, &msg, sizeof(Message), 1L, 0); // Извлечение сообщения из очереди
		if(res < 0) {
			printf("Error while receiving message\n");
			kill(getpid(), SIGINT);
		}
		printf("New message from client: %s\n", msg.buf);

		msg.type = 2L;          // Установка типа сообщения 2
		bzero(msg.buf, 100);    // Очищение сообщения
		strcpy(msg.buf, "OK");  // Сообщение клиенту

		res = msgsnd(queue, (void*)&msg, sizeof(Message), 0); // Отправка сообщения клиенту о том, что сообщение получено
		if(res != 0) {
			printf("error while sending msg\n");
			kill(getpid(), SIGINT);
		}
	}
	return 0;
}
