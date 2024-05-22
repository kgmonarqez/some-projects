#include "stdlib.h"
#include "stdio.h"
#include "signal.h"
#include "unistd.h"
#include "pthread.h"
#include "sys/syscall.h"
 
const int STOP_AT = 10;
const int THREADS_COUNT = 3;
const int NUMBER_OF_INTS_TO_HANDLE = 3;
 
void handleCtrlC(int sig) {
  if (sig == SIGINT) {
    static int intCounter = 0;
    
    int tid = syscall(SYS_gettid);
    printf("Received interruption signal (Ctrl+C) number %d in thread %d\n", ++intCounter, tid);
    
    if (intCounter < NUMBER_OF_INTS_TO_HANDLE) {
      signal(SIGINT, handleCtrlC); // Recover default handler
    } else {
      signal(SIGINT, SIG_DFL); // Recover default handler
    }
  }
}
 
void* thread(void* args) {
  int n = *(int*)args;
  char ps_cmd1[128];
  char ps_cmd2[128];
  
  int pid = getpid();
  int tid = syscall(SYS_gettid);
  
  printf("Started thread with pause %d; process id: %d, thread id: %d\n", n, pid, tid);
  
  for (int i = 0; i < STOP_AT; i++) {
    printf("Thread %d: counted to %d...\n", n, i);
    sleep(n);
  }
  
  printf("Finished thread with pause %d\n", n);
    
  // Trying to kill the thread
  // kill(tid, SIGKILL);
    
  pthread_exit(0);
}
 
int main() {
  pthread_t tid[THREADS_COUNT];
  pthread_attr_t tattr[THREADS_COUNT];
  int data[THREADS_COUNT];
  
  signal(SIGINT, handleCtrlC);
  
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
