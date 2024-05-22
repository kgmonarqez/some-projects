#include <iostream>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int pid;
    int n = 0;
    int m = 100;
    pid = fork();
    if(pid == -1)
    {
        perror("Fork function error");
        exit(1);
    }

    std::cout << "Current pid: " << pid << '\n';
    if(pid != 0) // родительский процесс
    {
        for (int i = 0; i < 100; i++)
        {
            n += 1;
        }
        std::cout << "Parent's variable: " << n << '\n';
    }
    else // дочерний
    {
        for (int j = 0; j < 100; j++)
        {
            m -= 1;
        }
        std::cout << "Son's variable: " << m << '\n';
    }

    std::cout << "Program done!" << '\n';
    exit(1);
}
