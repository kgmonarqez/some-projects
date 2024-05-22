#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

#define DEF_KEY_FILE "key"

typedef struct {
	long type;      // Тип сообщения
	char buf[100];  // Само сообщение
} Message;

int getQueue(char* keyFile, char identificator){
    key_t key;
	key = ftok(keyFile, 'Q');   // Взятие ключа по известным имени файла и идентификатору. Должен получиться тот же, что и у сервера
	if(key == -1) {
		printf("no got key for key file %s and id 'Q'\n",keyFile);
		exit(1);
	}
	int queue = msgget(key, 0);  // Получение доступа к очереди через получившийся ключ
	if (queue < 0) {
		printf("Can't open queue\n");
		exit(4);
	}
}

int queue;
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

    queue = getQueue(keyFile, 'Q');
    puts("Connected to queue");
    puts("Type any message to server");

	Message mes;
	int res;
	while(1){
		bzero(mes.buf,100);         
		fgets(mes.buf,100,stdin);   // Чтение сообщения с терминала
		mes.buf[strlen(mes.buf) - 1] = '\0'; // Установка конца строки

		mes.type = 1L;
		res = msgsnd(queue,(void*)&mes, sizeof(Message),0); // Помещение сообщения в очередь
		if(res != 0) {
			printf("Error while sending msg\n");
			exit(1);
		}

		res = msgrcv(queue,&mes, sizeof(Message), 2L, 0);     // Получение сообщения об успешном получении сервером
		if(res < 0) {
			printf("Error while recving msg\n");
			exit(1);
		}
		printf("New message from server: %s\n",mes.buf);
	}
	return 0;
}
