#include <string.h>
#include <malloc.h>
void encriptWord(unsigned char* text, int length){
    unsigned char* pToFirstSym;
    unsigned char* pToSecondSym;
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
        unsigned char local = *pToFirstSym;
        *pToFirstSym = *pToSecondSym;
        *pToSecondSym = local;
    }
}

unsigned char isValidSym(unsigned char sym) {
    if(sym <= (unsigned char)('z') && sym >= (unsigned char)('a'))
        return 1;
    if(sym <= (unsigned char)('Z') && sym >= (unsigned char)('A'))
        return 1;
    if(sym <= (unsigned char)('9') && sym >= (unsigned char)('0'))
        return 1;
    return 0;
}

void changeSpecialSymbol(unsigned char* pToSym,unsigned char* additionalArguments){
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

unsigned char* encript(unsigned char* input, unsigned char* additionalArguments) {
    //creating new string
    int size = strlen(input);
    unsigned char* text = (unsigned char*)malloc(size + 1);
    text = strcpy(text, input);
    
    unsigned char* pFirst = &text[0];
    unsigned char* pSecond = &text[0];
    int i = 0;
    for(; *pSecond != '\0'; ++pSecond, ++i) {
        //symbol = text[i];
        if(!isValidSym(*pSecond)) {
            changeSpecialSymbol(pSecond, additionalArguments);
	    if(*pSecond == ' ') {
		//encripts one word   with pSecond - pFirst length from pFirst pos   in line
                encriptWord(pFirst, pSecond - pFirst);
                //finding begining of next word
                pFirst = pSecond + 1;
	    }
	    if(*pSecond == '\n'){
		encriptWord(pFirst, pSecond - pFirst - 1);
                pFirst = pSecond + 1;
	    }
        }
    }
    return text;
}

unsigned char* decript(unsigned char* input, unsigned char* additionalArguments) {
    return encript(input, additionalArguments);
}
