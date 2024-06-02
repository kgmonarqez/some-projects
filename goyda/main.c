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
        
        command = readSTDIN(">");
        int length = strlen(command);
        op = menu(command);
        
        switch(op){
            case CMD_OPEN:
                if(MDB.movieList && isEdited){
                    if(askForSaving()){
                        fileName = readSTDIN("File name: ");
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

                sourceName = readSTDIN("File name: ");
                system("clear");
                MDB = readDB(sourceName);
                if(MDB.movieList){
                    isEdited = 0;
                }
                break;
            case CMD_SAVE:
                fileName = readSTDIN("Leave file name field empty to overwrite opened file\nFile name: ");
                system("clear");
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
                system("clear");
                printDB(MDB);
                break;
            case CMD_EDIT:
                if(!MDB.n){
                    system("clear");
                    puts("Empty data base");
                    break;
                }

                while((n = extractNum(readSTDIN("Movie №: "))) < 0 || n >= MDB.n){
                    if(n < 0){
                        puts("Movie number must be a positive integer");
                    }
                    else if(n >= MDB.n){
                        puts("Movie number is higher than actual size of the data base");
                    }
                }

                while((dt = defineDataType(readSTDIN("Category: "))) == NONE);
                
                while(!strlen(data = readSTDIN("New data: "))){
                    puts("Please type any data");
                }

                system("clear");
                editMovie(&MDB, n, dt, data);
                break;
            case CMD_ADD:
                addMovie(&MDB, initMovie());
                system("clear");
                puts("Movie added");
                break;
            case CMD_POP:
                if(!MDB.n){
                    system("clear");
                    puts("Empty data base");
                    break;
                }

                while((n = extractNum(readSTDIN("Movie №: "))) < 0);
                popMovie(&MDB, n);
                system("clear");
                printf("Movie №%d removed", n);
                break;
            case CMD_SORT:
                while((dt = defineDataType(readSTDIN("Category: "))) == NONE);
                so = defineSortingOrder(readSTDIN("Sorting order (+/-): "));
                sortList(&MDB, dt, so);
                system("clear");
                puts("Data base is sorted");
                break;
            case CMD_SEARCH:
                while((dt = defineDataType(readSTDIN("Category: "))) == NONE);
                while(!strlen(data = readSTDIN("New data: "))){
                    puts("Please type any data");
                }
                system("clear");
                searchMovies(&MDB, dt, data);
                break;
            case CMD_EXIT:
                if(MDB.movieList && isEdited){
                    if(askForSaving()){
                        fileName = readSTDIN("Leave file name field empty to overwrite opened file\nFile name: ");
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
                system("clear");
                printHelp();
                break;
            case CMD_STAT:
                while((dt = defineDataType(readSTDIN("Category: "))) == NONE);
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