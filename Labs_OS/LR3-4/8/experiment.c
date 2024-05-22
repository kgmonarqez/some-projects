#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    char* path = "/bin/uname";
    int pid = fork(); 
    if(pid == 0){
        if(argc > 2){
            printf("%d arguments\n", argc-1);
            char* new_args[argc];
            for(int i = 1; i < argc; i++){
                new_args[i-1] = argv[i];
            }
            new_args[argc-1] = NULL;
            execv(path, new_args);
        }
        else{
            puts("No arguments, default command");
            execl(path, path, NULL);
        }
    }
    sleep(1);
}
