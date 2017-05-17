
matmult: matmult.o main.o
	gcc -std=c99 matmult.o main.o -o matMult

matmult.o: matmult.c
	gcc -std=c99 -c matmult.c -o matmult.o

main.o: main.c
	gcc -std=c99 -c main.c -o main.o

clean:
	rm -rf *.o *~ 

cleanall: clean
	rm -rf matMult
