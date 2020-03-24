#include <stdio.h>
#include <string.h>
#include <malloc.h>

unsigned char** getArray(FILE* file, unsigned int bufferSize, int* countOfStrings){
	*countOfStrings = 0;//будем считать слова по ходу программы
	unsigned char** array;

	//fread считывает \0 неправильно поэтому последний буффер "подгоняется под размер + 1 символ для \0"
	//ниже ищем размер последнего буфера и их общее количество
	fseek(file, 0, SEEK_END);
	int shortenBuffer = (ftell(file) + 1) % bufferSize;
	int countOfBufferBlocks = ftell(file) / bufferSize + 1;
	fseek(file, 0, SEEK_SET); 

	//массив строк будет динамически расширятся с шагом deltaOfArrayCapacity
	unsigned int maxCountOfStrings = 5,deltaOfArrayCapacity = 5; 
	array = (unsigned char **) malloc(sizeof(char*) * maxCountOfStrings);

	unsigned char* buffer = (unsigned char*)malloc(bufferSize * sizeof(char));

	int previousStringSize = 0;//размер незаконченной в буфере строки
	int quit = 0;
	while(!quit){
		int startIndex = 0;//нужен для расчёта previousStringSize и проверки некоторых условий

		//выбирает сокращённый буффер для последнего считывания
		--countOfBufferBlocks;
		if(countOfBufferBlocks <= 0 && shortenBuffer != 0) {
			fread(buffer, 1, shortenBuffer, file);
			buffer[shortenBuffer - 1] = '\0';
		}
		else{
			fread(buffer, 1, bufferSize, file);
			if(!shortenBuffer && countOfBufferBlocks <= 0){
				buffer[bufferSize - 1] = '\0';
			}
		}
		
		int i = 0;
		//проходимся по буферу и ищем конец строки или перевод
		while(i < bufferSize) {
			if(buffer[i] == '\n' || buffer[i] == '\0'){
				//Если предыдущие строки завершены
				if(previousStringSize == 0){
					//Мы не знаем сколько всего строк. Можем ли мы принять ещё одну?
					if(++(*countOfStrings) > maxCountOfStrings) {
						//Если не можем то увеличим массив
						maxCountOfStrings += deltaOfArrayCapacity;
						array = (unsigned char **) realloc(array, sizeof(char*) * maxCountOfStrings);
					}
					//скопируем в массив строку из буффера
					array[*countOfStrings - 1] = (char *) malloc((i - startIndex + 1) * sizeof(char));
					strncpy(array[*countOfStrings - 1], buffer + startIndex, i - startIndex + 1);
					array[*countOfStrings - 1][i - startIndex] = '\0';
				}
				//если строка не была завершина расширим её
				else {
					array[*countOfStrings - 1] = (char *) realloc(array[*countOfStrings - 1], (i - startIndex + 1 + previousStringSize) * sizeof(char));
					strncpy(array[*countOfStrings - 1 ] + previousStringSize, buffer + startIndex, i - startIndex + 1);
					array[*countOfStrings - 1][i - startIndex + previousStringSize] = '\0';
				}
				previousStringSize = 0;
				
				//обрабатываем условие выхода
				if(buffer[i] == '\0'){
					startIndex = -1;
					quit = 1;
					break;
				}

				//нужны для поиска длинны оставшейся в буффере части
				if(i+1 < bufferSize) {
					startIndex = i+1;
				}
				else {
					startIndex = -1;
				}

			}
			++i;
			
		}
		//Если в буффере есть что-то
		if(startIndex != -1) {
			//Но до этого в буффере ничего не было
			if(previousStringSize == 0){
				//Мы не знаем сколько всего строк. Можем ли мы принять ещё одну?
				if(++(*countOfStrings) > maxCountOfStrings) {
					//Если не можем то увеличим массив
					maxCountOfStrings += deltaOfArrayCapacity;
					array = (unsigned char **) realloc(array, sizeof(char*) * maxCountOfStrings);
				}
				previousStringSize += bufferSize - startIndex;
				array[*countOfStrings - 1] = (char *) malloc((previousStringSize) * sizeof(char));
				strncpy(array[*countOfStrings - 1], buffer + startIndex, previousStringSize);
			}
			//Строка началась в предыдущих буфферах и до сих пор не завершилась
			else {
				array[*countOfStrings - 1] = (char *) realloc (array[*countOfStrings - 1], (previousStringSize + bufferSize) * sizeof(char));
				strcpy(array[*countOfStrings - 1] + previousStringSize, buffer);
				previousStringSize += bufferSize;
			}
		}
		else {
			previousStringSize = 0;
		}

		//вывод для отладки
		/*printf("!!!\n");
		for(int l = 0; l < *countOfStrings; ++l){
			int li = 0;
			while(array[l][li] != '\0'){
				if(l == (*countOfStrings) - 1 && previousStringSize == 0 && li == previousStringSize - 1){
					break;
				}
				printf("%c", array[l][li]);
				li++;
			}
				printf("\n");
		}
		printf("!!!\n");*/
		
	}
	free(buffer);
	array = (unsigned char **) realloc(array, sizeof(char*) * *countOfStrings);
	return array;
}

//сравнивает строки 1 - больше  0 - равны  -1 - меньше
int compareStrings(char* a, char* b) {
	int i = 0; 
	while(a[i] != '\0' && b[i] != '\0'){
		if(a[i] != b[i]){
			if(a[i] < b[i]) {
				return -1;
			}
			return 1;
		}
		++i;
	}

	//если одна строка равна другой
	if(a[i] == b[i])
		return 0;
	//если одна строка короче другой
	if(a[i] == '\0') {
		return -1;
	}
	return 1;
	
}
void bubleSort(unsigned char** arrayOfStrings, int countOfStrings){
	//compare 1 string with other (countOfStrings - 1) strings
	for(int sortIteration = 0; sortIteration < countOfStrings - 1; ++sortIteration){
		for(int i = 0; i < countOfStrings - 1 - sortIteration; ++i) {
			if(1 == compareStrings(arrayOfStrings[i], arrayOfStrings[i+1])) {
				unsigned char* buf;
				buf = arrayOfStrings[i+1];
				arrayOfStrings[i+1] = arrayOfStrings[i];
				arrayOfStrings[i] = buf;
			}
		}
	}
}

