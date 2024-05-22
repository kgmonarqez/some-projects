#include <stdio.h>
#include <sys/resource.h>

int main() {
    int priority = getpriority(PRIO_PROCESS, 0);
    printf("Current priority: %d\n", priority);
    return 0;
}
