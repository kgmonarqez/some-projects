#include "cmd.h"
#include "DataBaseEditing.h"
#include "DataBaseIO.h"
#include <string.h>

int main(int argc, char** argv){
    system("clear");
    MoviesDataBase MDB = {NULL, 0};
    operation op = CMD_NONE;
    char* sourceName = NULL;
    if(argc == 2){
        sourceName = argv[1];
        MDB = readDB(sourceName);
    }

    while(1){
        char* command = NULL;
        char* fileName = NULL;
        int n = -1;
        dataTypes dt = NONE;
        char* data = NULL;
        sortingOrder so = ASCENDING;

        if(op == CMD_EXIT){
            break;
        }
        printf(">");
        command = readSTDIN();
        int length = strlen(command);
        char* ptr = strtok(command, " ");
        
        op = menu(ptr);
        if(op != CMD_NONE){
            system("clear"); 
        }
        switch(op){
            case CMD_OPEN:
                if(MDB.movieList && isEdited){
                    if(askForSaving()){
                        printf("File name: ");
                        fileName = readSTDIN();
                        if(!strlen(fileName)){
                            free(fileName);
                            saveDB(MDB, sourceName);
                        }
                        else{
                            saveDB(MDB, fileName);
                            free(fileName);
                        }
                    }
                }
                if(MDB.movieList){
                    free(MDB.movieList);
                    MDB.movieList = NULL;
                    MDB.n = 0;
                }

                sourceName = strtok(NULL, " ");
                MDB = readDB(sourceName);
                if(MDB.movieList){
                    isEdited = 0;
                }
                break;
            case CMD_SAVE:
                printf("File name: ");
                fileName = readSTDIN();
                if(!strlen(fileName)){
                    free(fileName);
                    saveDB(MDB, sourceName);
                }
                else{
                    saveDB(MDB, fileName);
                    free(fileName);
                }
                break;
            case CMD_SHOW:
                printDB(MDB);
                break;
            case CMD_EDIT:
                if((n = extractNum()) < 0){
                    break;
                }
                dt = defineDataType(strtok(NULL, " "));
                data = strtok(NULL, " ");
                data = recoverFromStrtok(data, (length - (data - command)) / sizeof(char));
                editMovie(&MDB, n, dt, data);
                break;
            case CMD_ADD:
                data = strtok(NULL, " ");
                data = recoverFromStrtok(data, (length  - (data - command)) / sizeof(char));
                addMovie(&MDB, data);
                break;
            case CMD_POP:
                if((n = extractNum()) < 0){
                    break;
                }
                popMovie(&MDB, n);
                break;
            case CMD_SORT:
                dt = defineDataType(strtok(NULL, " "));
                so = defineSortingOrder(strtok(NULL, " "));
                sortList(&MDB, dt, so);
                break;
            case CMD_SEARCH:
                dt = defineDataType(strtok(NULL, " "));
                data = strtok(NULL, " ");
                data = recoverFromStrtok(data, (length  - (data - command)) / sizeof(char));
                searchMovies(&MDB, dt, data);
                break;
            case CMD_EXIT:
                if(MDB.movieList && isEdited){
                    if(askForSaving()){
                        printf("File name: ");
                        fileName = readSTDIN();
                        if(!strlen(fileName)){
                            free(fileName);
                            saveDB(MDB, sourceName);
                        }
                        else{
                            saveDB(MDB, fileName);
                            free(fileName);
                        }
                    }
                }
                break;
            case CMD_HELP:
                printHelp();
                break;
            case CMD_STAT:
                dt = defineDataType(strtok(NULL, " "));
                showStatistics(MDB, dt);
                break;
            default:
                puts("Unknown command\nType 'help' for manual");
                break;
        }
        free(command);
    }
    if(MDB.movieList){
        free(MDB.movieList);
    }
    system("clear");
}