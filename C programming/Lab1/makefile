runnable: main.o cypher.o fileFunctions.o
	gcc -o runnable main.o cypher.o fileFunctions.o
fileFunctions.o: fileFunctions.c
	gcc -c -o fileFunctions.o fileFunctions.c
main.o: main.c fHeaders.h
	gcc -c -o main.o main.c
cypher.o: cypher.c
	gcc -c -o cypher.o cypher.c
