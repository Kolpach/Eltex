#include <stdio.h>
#include <string.h>
#include <malloc.h>
unsigned char* fileRead(FILE* f,unsigned char* name){
    unsigned char* text;
    //trying to read file
    if( (f = fopen(name, "r")) != NULL){
	//reading string of unknown size
	unsigned int N = 10, delta=10, i = 0;   
    	unsigned char* buf = (unsigned char*) malloc (sizeof(char)*N);
	//reading from file    
    	while ( !feof(f)  )  {
	    buf [i] = fgetc(f);
	    //if max length < current length                
            if (++i >= N) {
            	N += delta;
		//appending string
                buf = (unsigned char*) realloc (buf, sizeof(char)*N);        
            }
	}
    	fclose(f);
    	buf[i] = '\0';
	//Final text of file
	text = (unsigned char*)malloc(sizeof(char)*(i+1));
	strcpy(text, buf);
    	free (buf);
    }
    else {
	printf("wrong file");
	return NULL;
    }
    return text;
}

