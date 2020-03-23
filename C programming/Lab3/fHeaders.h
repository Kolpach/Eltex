
struct line {
	int countOfSpecSymbols;
	unsigned char* string;
	struct line* next;
	struct line* previous;
};
unsigned char* readLine(FILE* f);
void sort(struct line** fr, struct line** ba );
int calculateSpecSymbols(unsigned char* string);