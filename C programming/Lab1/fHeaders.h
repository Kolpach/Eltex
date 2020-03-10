void encriptWord(unsigned char* text, int length);
char isValidSym(unsigned char sym);
void changeSpecialSymbol(unsigned char* pToSym, unsigned char* additionalArguments);

unsigned char* encript(unsigned char* input, unsigned char* additionalArguments);
unsigned char* decript(unsigned char* input, unsigned char* additionalArguments);

unsigned char* fileRead(FILE* f, unsigned char* name);
