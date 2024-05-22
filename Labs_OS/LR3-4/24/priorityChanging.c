#include "stdio.h"
#include "unistd.h"
#include "pthread.h"
#include "stdlib.h"
#include "sched.h"
#include "time.h"
 
const int STOP_AT = 1000;
const int THREADS_COUNT = 10;
 
void mill(){
  int ind = 0;
  while (ind != 1000000){
    ind += 1;
  }
}
 
void* thread(void* args) {
  int n = *(int*)args;
  
  int time_used = 0;
  clock_t temp_time_start = 0;
  clock_t temp_time_stop = 0;
  
  int policy;
  struct sched_param param;
  pthread_getschedparam(pthread_self(), &policy, &param);
  param.sched_priority = n;
  sched_setscheduler(0, SCHED_FIFO, &param);
  printf("Started thread with pause %d; it has priority %d\n", n, param.sched_priority);
  sleep(100);
  
  temp_time_start = clock();
  for (int i = 0; i < STOP_AT; i++) {
    mill();
  }
  temp_time_stop = clock();
  time_used = temp_time_stop - temp_time_start;
  
  printf("Finished thread with pause %d; time %d\n", n, time_used);
  
  pthread_exit(0);
}
 
int main() {
  pthread_t tid[THREADS_COUNT];
  pthread_attr_t tattr[THREADS_COUNT];
  int data[THREADS_COUNT];
  
  int policy;
  struct sched_param param;
  sched_setscheduler(0, SCHED_FIFO, &param);
  sched_getparam(0, &param);
  printf("Process has priority %d\n", param.sched_priority);
  
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
