#ifndef FHEADERS_H
#define FHEADERS_H
struct line {
	int countOfSpecSymbols;
	unsigned char* string;
	struct line* next;
	struct line* previous;
};
unsigned char* readLine(FILE* f);
void sort(struct line** fr, struct line** ba );
int calculateSpecSymbols(unsigned char* string);

unsigned char** getArray(FILE* file, unsigned int bufferSize, int* countOfStrings);
void bubleSort(unsigned char** arrayOfStrings, int countOfStrings);
int compareStrings(char* a, char* b);
#endif
