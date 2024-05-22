#include "stdio.h"
#include "unistd.h"
#include "pthread.h"
#include "stdlib.h"
#include "sched.h"
#include "time.h"
 
const int STOP_AT = 100;
const int THREADS_COUNT = 10;
 
void mill(){
  int ind = 0;
  while (ind != 10000000){
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
  //printf("Started thread %d; priority %d\n", n, param.sched_priority);
  
  temp_time_start = clock();
  for (int i = 0; i < STOP_AT; i++) {
    mill();
    if(i%10 == 0){
    	printf("%d ", n);
    }
  }
  temp_time_stop = clock();
  time_used = temp_time_stop - temp_time_start;
  
  //printf("Finished thread with pause %d; time %d\n", n, time_used);
  
  pthread_exit(0);
}

int main() {
  char command[100];
  sprintf(command, "taskset -p 0x1 %d", getpid());
  system(command);
  pthread_t tid[THREADS_COUNT];
  pthread_attr_t tattr[THREADS_COUNT];
  int data[THREADS_COUNT];
  
  int policy;
  struct sched_param param;
  sched_setscheduler(getpid(), SCHED_RR, &param);
  sched_getparam(getpid(), &param);
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
