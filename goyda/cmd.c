#include "cmd.h"

char* readSTDIN(){
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
    }
    return ASCENDING;
}

char* recoverFromStrtok(char* str, int n){
    if(str){
        for(int i = 0; i < n; i++){
            if(*(str + i) == '\0'){
                *(str + i) = ' ';
            }
        }
    }
    return str;
}

int checkIsNum(char* str){
    for(int i = 0; i < strlen(str); i++){
        if(!isdigit(str[i])){
            return 0;
        }
    }
    return 1;
}

int extractNum(){
    char* data = strtok(NULL, " ");
    if(data && checkIsNum(data)){
        return atoi(data) - 1;
    }
    else{
        puts("Movie number must be an integer");
        return -1;
    }
}

void printHelp(){
    puts("MDB - Movie's data base manual\n");
    puts("This data base keeps 5 categories of a movie:");
    puts("\tDirector");
    puts("\tName");
    puts("\tYear");
    puts("\tCopies");
    puts("\tCost");
    puts("\nAll the data is editable and can be saved in another file");
    puts("\n\topen [filename] - opens and reads data base\n");
    puts("\t\t[filename] - name of the data base file");
    puts("\n\tsave - saves current data base state in a file. If file name is not written, data is saved in the opened\n");
    puts("\n\tshow - prints data base in a table format");
    puts("\n\tedit [n] [dataType] [newData] - edit movie data\n");
    puts("\t\t[n] - number of a movie in the table");
    puts("\t\t[dataType] - category of an editable movie");
    puts("\t\t[newData] - new data to an editable movie");
    puts("\n\tadd [movieInfo] - adds a new movie in the data base\n");
    puts("\t\t[movieInfo] - string with a format '[Director] / [Name] / [Year] / [Copies] / [Cost]'. Every not mentioned data will be pointed as None");
    puts("\n\tremove [n] - delete a movie from the data base\n");
    puts("\t\t[n] - number of a movie in the table");
    puts("\n\tsort [dataType] [order] - sort movies by data\n");
    puts("\t\t[dataType] - category by which data base is sorted");
    puts("\t\t[order] - order of sorting: '+' for ascending, '-' for descending. Typing command without sorting order sorting it ascendingly");
    puts("\n\tfind [dataType] [data] - find movies by data\n");
    puts("\t\t[dataType] - category of a searchable data");
    puts("\t\t[data] - searched data in the table");
    puts("\n\tquit - quit the program");
    puts("\n\thelp - print help info\n");
}

int askForSaving(){
    printf("Changes are not saved\nDo you want to save them? [y, n]: ");
    char* ans = readSTDIN();
    while(strcmp(ans, "y") && strcmp(ans, "n")){
        if(ans){
            free(ans);
        }
        ans = readSTDIN();
    }
    if(!strcmp(ans, "n")){
        free(ans);
        return 0;
    }
    free(ans);
    return 1;
}