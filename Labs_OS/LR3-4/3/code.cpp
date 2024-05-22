#include <iostream>
#include <unistd.h>


int main(int argc, char* argv[])
{
    int pid;
    int n = 0;
    int m = 100;
    int counter = 0;
    char command[64];
    pid = fork();
    printf("\nParent: %d\nSon: %d\n", getpid(), pid);
    //sprintf(command, "taskset -p 0x00000001 %d", getpid());
    //system(command);
    sleep(10);

    if(pid == -1)
    {
        perror("Fork function error");
        exit(1);
    }
    while(true)
    {
        if(pid != 0){
            std::cout << "Current pid: " << pid << '\n';
            for (int i = 0; i < 100; i++)
            {
                n += 1;
            }
            std::cout << "Parent: " << n << ", with pid " << pid << '\n';
        }
        else{
            std::cout << "	" << "Current pid: " << pid << '\n';
            for (int j = 0; j < 100; j++)
            {
                m -= 1;
            }
            std::cout << "	" << "Son: " << m << ", with pid " << pid << '\n';
        }
        counter++;
        if (counter == 50){
            break;
        }
    }
    
    std::cout << "Program with pid " << pid << " done!" << '\n';
    exit(1);
}