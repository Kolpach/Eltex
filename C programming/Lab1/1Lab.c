#include <stdio.h>
#include <string.h>
#include <malloc.h>
void encriptWord(char* text, int length){
    char* pToFirstSym;
    char* pToSecondSym;
    int countOfIterations = length / 2;
    if(length % 2 == 0) {
        pToFirstSym = &(text[length / 2 - 1]);
        pToSecondSym = &(text[length / 2]);
    }
    else {
        pToFirstSym = &(text[length / 2 - 1]);
        pToSecondSym = &(text[length / 2  + 1]);
    }
    //saving first letter register
    for(int i = 0; i < countOfIterations; ++i, --pToFirstSym, ++pToSecondSym) {
        if(i + 1 == countOfIterations) {
            if(*pToFirstSym <= 'Z' && *pToFirstSym >= 'A' && *pToSecondSym <= 'z' && *pToSecondSym >= 'a') {
                *pToFirstSym = ('a' + *pToFirstSym - 'A');//First sym to lowercase
                *pToSecondSym = ('A' + *pToSecondSym - 'a');//Second sym to Uppercase
            }
            else if(*pToFirstSym <= 'z' && *pToFirstSym >= 'a' && *pToSecondSym <= 'Z' && *pToSecondSym >= 'A') {
                *pToFirstSym = ('A' + *pToFirstSym - 'a');//First sym to uppercase
                *pToSecondSym = ('a' + *pToSecondSym - 'A');//Second sym to lowercase
            }
        }
        //changing symbols
        char local = *pToFirstSym;
        *pToFirstSym = *pToSecondSym;
        *pToSecondSym = local;
    }
}

char isValidSym(char sym) {
    if(sym <= 'z' && sym >= 'a')
        return 1;
    if(sym <= 'Z' && sym >= 'A')
        return 1;
    if(sym <= '9' && sym >= '0')
        return 1;
    return 0;
}

void changeSpecialSymbol(char* pToSym, char* additionalArguments){
    int i = 0;
    while(additionalArguments[i] != *pToSym && additionalArguments[i] != '\0'){
        ++i;
    }
    //changing symbol only if symbol in string
    if(additionalArguments[i] != '\0'){
        //getting index of another element in pair
        *pToSym = additionalArguments[i + 1 - 2 * (i % 2) ];
    }
}

char* encript(char* input, char* additionalArguments) {
    int size = strlen(input);
    char* text = (char*)malloc(size + 1);
    text = strcpy(text, input);
    
    char* pFirst = &text[0];
    char* pSecond = &text[0];
    //char symbol = '!';//any sym exept \0
    for(int i = 0; *pSecond != '\0'; ++i, ++pSecond) {
        //symbol = text[i];
        if(!isValidSym(*pSecond)){
            //заменить особый символ
            changeSpecialSymbol(pSecond, additionalArguments);
            //encripts one of words
            encriptWord(pFirst, pSecond - pFirst);
            //finding begining of next word
            pFirst = pSecond + 1;
        }
    }
    return text;
}

char* decript(char* input, char* additionalArguments) {
    return encript(input, additionalArguments);
}

int main(int argc, char* arg[])
{
    if(argc < 4){
        printf("No valid arguments detected\n");
        return 0;
    }
    char* input = arg[1];
    char* additionalArguments;
    FILE* f;
    FILE* outputFile = fopen(arg[3], "w");

    //trying to read 

    //trying to read additional
    if( (f = fopen(arg[2], "r")) != NULL){
	//reading string of unknown size
	unsigned int N = 10, delta=10, i = 0;   
    	char* buf = (char*) malloc (sizeof(char)*N);    
    	while ((buf [i] = fgetc(f)) != EOF  )  {                
            if (++i >= N) {
            	N += delta;
		//appending string
                buf = (char*) realloc (buf, sizeof(char)*N);        
            }
	}   
    	fclose(f);
    	buf[i] = '\0';
	//Final text of file
	additionalArguments = malloc(sizeof(char)*N);
	strcpy(additionalArguments, buf);
    	free (buf);
    }
    else {
	printf("wrong file");
    }
    printf("type \'e\' to encript, \'d\' to decript\n");
    char inputMode;
    scanf("%c", &inputMode);
    char* text;

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
	printf("Wrong symbol");
	break;
    }
    fprintf(outputFile, "%s\n", text);
    free(text);
    free(additionalArguments);
    
    return 0;
}
