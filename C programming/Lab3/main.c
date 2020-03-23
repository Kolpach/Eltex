#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "fHeaders.h"

int main(int argc, unsigned char* arg[])
{
	if(argc < 3){
		printf("No valid arguments detected\n");
		return 0;
	}

	FILE* inputFile = fopen(arg[1], "r");
	FILE* outputFile = fopen(arg[2], "w");
	struct line* back = NULL;
	struct line* front = NULL;
	
	//setting a list
	while(!feof(inputFile)) {
		struct line* newLine = (struct line *)malloc(sizeof(struct line));
		newLine->string = readLine(inputFile);
		newLine->countOfSpecSymbols = calculateSpecSymbols(newLine->string);
		if(back != NULL) {
			back->next = newLine;
			newLine->previous = back;
			back = back->next;
		}
		else {
			newLine->previous = NULL;
			newLine->next = NULL;
			back = newLine;
			front = newLine;
		}
	}
	fclose(inputFile);

	struct line** backChangeblePointer = &back;
	struct line** frontChangeblePointer = &front;
	sort(frontChangeblePointer, backChangeblePointer);
	front = *frontChangeblePointer;
	back = *backChangeblePointer;

	//output
	struct line* current = front;
	while(current != NULL) {
		fprintf(outputFile, "%s", current->string);
		current = current->next;
		current != NULL && fprintf(outputFile, "\n");
	}
	fclose(outputFile);

	//free memory
	current = front;
	while(current != back) {
		free(current->string);
		current = current->next;
		free(current->previous);
	}
	free(current->string);
	free(current);
    
    return 0;
}
