CFLAG = -std=c99

all: main.o cmd.o DataBaseEditing.o DataBaseIO.o
	gcc $(CFLAG) main.o cmd.o DataBaseEditing.o DataBaseIO.o
main.o: main.c cmd.h DataBaseEditing.h DataBaseIO.h
	gcc $(CFLAG) -c main.c
cmd.o: cmd.c
	gcc $(CFLAG) -c cmd.c
DataBaseEditing.o: DataBaseEditing.c cmd.h
	gcc $(CFLAG) -c DataBaseEditing.c
DataBaseIO.o: DataBaseIO.c cmd.h
	gcc $(CFLAG) -c DataBaseIO.c
