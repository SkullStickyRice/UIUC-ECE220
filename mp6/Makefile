CC=gcc
CFLAGS= -g -Wall -Wextra

mp6: main.o maze.o
	$(CC) $(CFLAGS) main.o maze.o -o mp6

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

maze.o: maze.c
	$(CC) $(CFLAGS) -c maze.c

clean:
	rm -f *.o mp6
