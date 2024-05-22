#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    char* file = "uname";
    char* path = "/bin/uname";
    char* args[] = {"uname", "-r", NULL };
    char* env[] = {(char*) NULL};
    int pid, switch_flag = (int)argv[1][0];
    pid = fork(); 
    if(pid == 0){
        switch(switch_flag){
            case '1':
                execl(path, path, "-r", (char*) NULL);
                break;
            case '2':
                execv(path, args);
                break;
            case '3':
                execlp(file, file, "-r", (char*) NULL); 
                break; 
            case '4': 
                execvp(file, args);
                break;
            case '5':
                execle(path, file, "-r", (char*) NULL, env);
                break;
            case '6':
                execve("uname", args, env);
                break; 
        }
    }
}
// Пример когда переаются реальные аргументы или не передаются
