#include <stdio.h>
#include <unistd.h>

int main() {
    for(int i = 0; i < 5; ++i) {
        printf("Iteration %d\n", i);
        sleep(1);
    }
    return 0;
}
