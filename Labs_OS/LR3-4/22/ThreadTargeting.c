#include "stdlib.h"
#include "stdio.h"
#include "signal.h"
#include "unistd.h"
#include "pthread.h"
#include "sys/syscall.h"
 
const int STOP_AT = 10;
const int THREADS_COUNT = 3;
 
void blockSignal(int sig) {
  sigset_t set;
  
  sigemptyset(&set);
  sigaddset(&set, sig);
  sigprocmask(SIG_BLOCK, &set, NULL);
}
 
void unblockSignal(int sig) {
  sigset_t set;
  
  sigemptyset(&set);
  sigaddset(&set, sig);
  sigprocmask(SIG_UNBLOCK, &set, NULL);
}
 
void handleCtrlC(int sig) {
  if (sig == SIGINT) {
      int tid = syscall(SYS_gettid);
    printf("Received interruption signal (Ctrl+C) in thread %d\n", tid);
    signal(SIGINT, SIG_DFL); // Recover default handler
  }
}
 
void* thread(void* args) {
  int n = *(int*)args;
  char ps_cmd1[128];
  char ps_cmd2[128];
  
  // We want to handle the interruption in the first thread.
  if (n == 1) {
    unblockSignal(SIGINT);
    signal(SIGINT, handleCtrlC);
  }
  
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
  
  blockSignal(SIGINT);
  
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
