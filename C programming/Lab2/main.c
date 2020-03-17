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

    FILE* inputFile;
    if( (inputFile = fopen(arg[1], "r")) == NULL){
	    printf("wrong file");
    }

    FILE* outputFile = fopen(arg[3], "w");
    
    int countOfStrings = 0;
    int bufferSize = 0;
    //считываем bufferSize из строки
    for(int i = 0; i < strlen(arg[2]); ++i){
        if(arg[2][i] >= '0' && arg[2][i] <= '9'){
            bufferSize *= 10;
            bufferSize += (arg[2][i] - '0');
        }
        else {
            printf("Wrong parametr. Must be integer\n");
            break;
        }
    }
    //получаем массив
    unsigned char** arrayOfStrings = getArray(inputFile, bufferSize, &countOfStrings);

    //сортируем пузырьком
    bubleSort(arrayOfStrings, countOfStrings);

    //вывод и уборка
    for(int i = 0; i < countOfStrings; ++i){
		fprintf(outputFile, "%s\n", arrayOfStrings[i]);
        free(arrayOfStrings[i]);
	}
    free(arrayOfStrings);
    return 0;
}
