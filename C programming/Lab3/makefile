runnable: main.o structFunctions.o fileFunctions.o
	gcc -o runnable main.o structFunctions.o fileFunctions.o
main.o: main.c fHeaders.h
	gcc -c -o main.o main.c
structFunctions.o: structFunctions.c fHeaders.h
	gcc -c -o structFunctions.o structFunctions.c
fileFunctions.o: fileFunctions.c
	gcc -c -o fileFunctions.o fileFunctions.c
