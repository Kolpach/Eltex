#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "fHeaders.h"

int main(int argc, unsigned char* arg[])
{
    if(argc < 4){
        printf("No valid arguments detected\n");
        return 0;
    }

    unsigned char* input;
    unsigned char* additionalArguments;

    FILE* inputFile;
    FILE* additionalFile;
    FILE* outputFile = fopen(arg[3], "w");
    input = fileRead(inputFile, arg[1]);
    additionalArguments = fileRead(additionalFile, arg[2]);

    printf("type \'e\' to encript, \'d\' to decript\n");

    unsigned char inputMode;
    scanf("%c", &inputMode);
    unsigned char* text;

    switch(inputMode){
    case 'e':
    case 'E':
	text = encript(input, additionalArguments);
	break;
    case 'd':
    case 'D':
	text = decript(input, additionalArguments);
	break;
    default:
	printf("Wrong symbol\n");
	return 0;
    }

    fprintf(outputFile, "%s\n", text);
    free(text);
    free(input);
    free(additionalArguments);
    
    return 0;
}
