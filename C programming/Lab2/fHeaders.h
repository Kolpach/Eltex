#include <stdio.h>
unsigned char** getArray(FILE* file, unsigned int bufferSize, int* countOfStrings);
void bubleSort(unsigned char** arrayOfStrings, int countOfStrings);
int compareStrings(char* a, char* b);
