#include "stdio.h"
#include "unistd.h"
#include "pthread.h"
 
const int STOP_AT = 10;
const int THREADS_COUNT = 5;
 
void* thread(void* args) {
  int n = *(int*)args;
  
  printf("Started thread with pause %d\n", n);
  
  for (int i = 0; i < STOP_AT; i++) {
    printf("Thread %d: counted to %d...\n", n, i);
    sleep(n);
  }
  
  printf("Finished thread with pause %d\n", n);
  
  pthread_exit(0);
}
 
int main() {
  pthread_t tid[THREADS_COUNT];
  pthread_attr_t tattr[THREADS_COUNT];
  int data[THREADS_COUNT];
  
  for (int n = 0; n < THREADS_COUNT; n++) {
    data[n] = n + 1;
    
    pthread_attr_init(&tattr[n]);
    int r = pthread_create(&tid[n], &tattr[n], thread, (void*)&data[n]);
  }
  
  for (int n = 0; n < THREADS_COUNT; n++) {
    pthread_join(tid[n], NULL);
  }
  
  return 0;
}
