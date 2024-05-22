#include <iostream>
#include <unistd.h>


int main(int argc, char* argv[])
{
    int pid;
    int ITERATIONS = 10;
    pid = fork();
    if(pid == -1)
    {
        perror("Fork function error");
        exit(1);
    }

    std::cout << "Current pid: " << pid << '\n';
    if(pid != 0)
    {
        for (int i = 0; i < ITERATIONS; i++)
        {
            std::cout << "Step = " << i << ", parent's cycle with pid: " << pid << '\n';
        }
    }
    else
    {
        for (int i = 0; i < ITERATIONS; i++)
        {
            std::cout << "Step = " << i << ", son's cycle with pid: " << pid << '\n';
        }
    }

    std::cout << "Program with pid " << pid << " done!" << '\n';
    exit(1);
}
