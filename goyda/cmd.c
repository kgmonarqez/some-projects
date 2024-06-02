#include "cmd.h"

char* readSTDIN(char* message){
    if(message){
        printf("%s", message);
    }
    int size = STRING_SIZE;
    char* command = malloc(sizeof(char) * size);
    int length = 0;
    char s;
    while((s = getchar()) != '\n'){
        if(length >= size - 2){
            size += STRING_SIZE;
            char* tmp = realloc(command, sizeof(char) * size);
            command = tmp;
        }
        command[length++] = s;
    }
    command[length] = '\0';
    return command;
}

operation menu(char* command){
    if(command && strlen(command)){
        if(!strcmp(command, STR_EXIT)){
            return CMD_EXIT;
        }
        else if(!strcmp(command, STR_OPEN)){
            return CMD_OPEN;
        }
        else if(!strcmp(command, STR_SAVE)){
            return CMD_SAVE;
        }
        else if(!strcmp(command, STR_SHOW)){
            return CMD_SHOW;
        }
        else if(!strcmp(command, STR_EDIT)){
            return CMD_EDIT;
        }
        else if(!strcmp(command, STR_ADD)){
            return CMD_ADD;
        }
        else if(!strcmp(command, STR_POP)){
            return CMD_POP;
        }
        else if(!strcmp(command, STR_SORT)){
            return CMD_SORT;
        }
        else if(!strcmp(command, STR_SEARCH)){
            return CMD_SEARCH;
        }
        else if(!strcmp(command, STR_HELP)){
            return CMD_HELP;
        }
        else if(!strcmp(command, STR_STAT)){
            return CMD_STAT;
        }
    }
    return CMD_NONE;
}

dataTypes defineDataType(char* dt){
    if(dt){
        if(!strcmp(dt, STR_DIRECTOR)){
            return DIRECTOR;
        }
        else if(!strcmp(dt, STR_NAME)){
            return NAME;
        }
        else if(!strcmp(dt, STR_YEAR)){
            return YEAR;
        }
        else if(!strcmp(dt, STR_COPIES)){
            return COPIES;
        }
        else if(!strcmp(dt, STR_COST)){
            return COST;
        }
    }
    puts("Wrong category");
    return NONE;
}

sortingOrder defineSortingOrder(char* so){
    if(so){
        if(!strcmp(so, STR_ASCENDING)){
            return ASCENDING;
        }
        else if(!strcmp(so, STR_DESCENDING)){
            return DESCENDING;
        }
        else{
            puts("Wrong sorting type, switched to ascending (+)");
        }
    }
    return ASCENDING;
}

int checkIsNum(char* str){
    for(int i = 0; i < strlen(str); i++){
        if(!isdigit(str[i])){
            return 0;
        }
    }
    return 1;
}

int extractNum(char* data){
    int res = -1;
    if(data && checkIsNum(data)){
        res = atoi(data) - 1;
    }
    free(data);
    return res;
}

void printHelp(){
    puts("MDB - Movie's data base manual\n");
    puts("This data base keeps 5 categories of a movie:");
    printf("    %s\n", STR_DIRECTOR);
    printf("    %s\n", STR_NAME);
    printf("    %s\n", STR_YEAR);
    printf("    %s\n", STR_COPIES);
    printf("    %s\n", STR_COST);
    puts("\nAll the data is editable and can be saved in another file");
    printf("\n\t%s - opens and reads data base\n", STR_OPEN);
    printf("\n\t%s - saves current data base state in a file\n", STR_SAVE);
    printf("\n\t%s - prints data base in a table format\n", STR_SHOW);
    printf("\n\t%s - edit movie data\n", STR_EDIT);
    printf("\n\t%s - adds a new movie in the data base\n", STR_ADD);
    printf("\n\t%s - delete a movie from the data base\n", STR_POP);
    printf("\n\t%s - sort movies by data\n", STR_SORT);
    printf("\n\t%s - find movies by data\n", STR_SEARCH);
    printf("\n\t%s - get some mathematical statistics\n", STR_STAT);
    printf("\n\t%s - quit the program\n", STR_EXIT);
    printf("\n\t%s - print help info\n", STR_HELP);
}

int askForSaving(){
    char* ans = readSTDIN("Changes are not saved\nDo you want to save them? [y, n]: ");
    while(strcmp(ans, "y") && strcmp(ans, "n")){
        if(ans){
            free(ans);
        }
        ans = readSTDIN(NULL);
    }
    if(!strcmp(ans, "n")){
        free(ans);
        return 0;
    }
    free(ans);
    return 1;
}