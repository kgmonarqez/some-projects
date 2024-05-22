#include <stdio.h>
#include <sys/resource.h>

int main() {
    printf("Минимальный приоритет: %d\n", PRIO_MIN);
    printf("Максимальный приоритет: %d\n", PRIO_MAX);
    return 0;
}
