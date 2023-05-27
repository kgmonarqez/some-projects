CFLAG = -std=c99

all: main.o bmpfile.o bmptools.o BMP.h
	gcc $(CFLAG) main.o bmpfile.o bmptools.o -lm
main.o: main.c BMP.h
	gcc $(CFLAG) -c main.c
bmpfile.o: bmpfile.c BMP.h
	gcc $(CFLAG) -c bmpfile.c
bmptools.o: bmptools.c BMP.h
	gcc $(CFLAG) -c bmptools.c