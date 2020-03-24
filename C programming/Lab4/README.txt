Лабораторная работа 4.
Выполнил: Кущенко Максим

Команды для создания и использования статической библиотеки.
ar rc lib_myLib.a sort.o fileFunctions.o structFunctions.o

gcc -o runnable_for_3lab_static main_for_3lab.o -L. -l _myLib
gcc -o runnable_for_2lab_static main_for_2lab.o -L. -l _myLib


Команды для создания и использования динамической библиотеки.
gcc -shared -o lib_myLib.so -fPIC sort.c fileFunctions.c structFunctions.c

gcc -L. -Wl,-rpath,. -o runnable_for_2lab_dynamic main_for_2lab.c -l _myLib
gcc -L. -Wl,-rpath,. -o runnable_for_3lab_dynamic main_for_3lab.c -l _myLib

Пример запуска.
./runnable_for_2lab_static input 10 output 
./runnable_for_2lab_dynamic input 10 output 
./runnable_for_3lab_static input output 
./runnable_for_3lab_dynamic input output

P.S.
Динамическая библиотека (.so) должна находиться в папке с остальными исходниками.
