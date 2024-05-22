#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

int main(int argc, char** argv){
    if(argc < 3){
    	puts("2 files for reading and writing required");
    	exit(1);
    }
    char* source = argv[1];
    char* destination = argv[2];
    int fd[2];

    pipe(fd);

    puts("Pipe created");
    if(fork() == 0){
        close(fd[0]);
        FILE* f = fopen(source, "r");
        if(f){
            char buf[100];
            int res;
            while(!feof(f)){
                res = fread(buf, sizeof(char), 100, f);
                write(fd[1], buf, res);
            }
            fclose(f);
            return 0;
        }
        else{
            puts("pipe(): error");
            exit(1);
        }
    }

    close(fd[1]);
    FILE* f = fopen(destination, "w");
    if(f){
        int n = 100;
        printf("-----Pipe output every %d symbols at every string-----\n", n);
        char buf[n + 1];
        int res;
        while(1){
            bzero(buf, n);
            res = read(fd[0], buf, n);
            if(!res){
                break;
            }
            buf[n] = '\0';
            printf("%s\n", buf);
            fwrite(buf, sizeof(char), res, f);
        }
        fclose(f);
        close(fd[0]);
        return 0;
    }
    return 1;
}

