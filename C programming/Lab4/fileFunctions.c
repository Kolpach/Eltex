#include <stdio.h>
#include <string.h>
#include <malloc.h>
unsigned char* readLine(FILE* f){
    unsigned char* line;
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
		if(buf[i-1] == '\n'){
			--i;
			break;
		}
	}
	if(feof(f)){
		buf[--i] = '\0';
	}
	else {
		buf[i] = '\0';
	}
	//Final text of file
	line = (unsigned char*)malloc(sizeof(char)*(i+1));
	strncpy(line, buf, i+1);
	free (buf);
	return line;
}

