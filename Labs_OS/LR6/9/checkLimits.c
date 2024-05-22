#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main(){
    printf("OPEN_MAX: %ld\n", sysconf(_SC_OPEN_MAX));
    printf("PIPE_BUF: %d\n", PIPE_BUF);

    return 0;
}