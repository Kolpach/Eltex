runnable: main.o sort.o
	gcc -o runnable main.o sort.o
main.o: main.c fHeaders.h
	gcc -c -o main.o main.c
sort.o: sort.c
	gcc -c -o sort.o sort.c
