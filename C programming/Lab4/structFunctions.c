#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "fHeaders.h"
int calculateSpecSymbols(unsigned char* string){
	int count = 0;
	char sym;
	for(int i = 0; string[i] != '\0'; ++i) {
		sym = string[i];
		if(!( sym <= 'Z' && sym >= 'A' || sym >= 'a' && sym <= 'z') ){
			++count;
		}
	}
	return count;
}
void sort(struct line** fr, struct line** ba ) {
	struct line* front = *fr;
	struct line* back = *ba;
	for(struct line* current = front; current != back; current = current->next){
		for(struct line* lesser = back; lesser != current; lesser = lesser->previous) {
			if(lesser->countOfSpecSymbols < current->countOfSpecSymbols) {
				//when current and lesser were near each other was a mistake
				if(current->next == lesser) {
					current->next = lesser->next;
					lesser->previous = current->previous;
					current->previous = lesser;
					lesser->next = current;
				}
				else {
					//changing inner pointers between members of exchange
					struct line* buf = current->next;
					current->next = lesser->next;
					lesser->next = buf;
				
					buf = current->previous;
					current->previous = lesser->previous;
					lesser->previous = buf;
				}

				//setting begining and ending of a list
				if(current == front) {
					front = lesser;
					lesser->previous = NULL;
				}
				if(lesser == back) {
					back = current;
					current->next = NULL;
				}

				//changing outter pointers in neighbor members of a chain
				if(lesser != front) {
					lesser->previous->next = lesser;
				}
				lesser->next->previous = lesser;

				if(current != back) {
					current->next->previous = current;
				}
				current->previous->next = current;

				//swaping pointers
				struct line* buf = current;
				current = lesser;
				lesser = buf;
			}
		}
	}
	*fr = front;
	*ba = back;
}
/*void sort(struct line* front, struct line* back ){
	for(struct line* current = front; current != back; current = current->next){
		for(struct line* lesser = current->next; lesser != NULL; lesser = lesser->next) {
			if(lesser->countOfSpecSymbols < current->countOfSpecSymbols) {

				//when current and lesser were near each other was a mistake
				if(current->next == lesser) {
					current->next = lesser->next;
					lesser->previous = current->previous;
					current->previous = lesser;
					lesser->next = current;
				}
				else {
					//changing inner pointers between members of exchange
					struct line* buf = current->next;
					current->next = lesser->next;
					lesser->next = buf;
				
					buf = current->previous;
					current->previous = lesser->previous;
					lesser->previous = buf;
				}

				//setting begining and ending of a list
				if(current == front) {
					front = lesser;
					lesser->previous = NULL;
				}
				if(lesser == back) {
					back = current;
					current->next = NULL;
				}

				//changing outter pointers in neighbor members of a chain
				if(lesser != front) {
					lesser->previous->next = lesser;
				}
				lesser->next->previous = lesser;

				if(current != back) {
					current->next->previous = current;
				}
				current->previous->next = current;
				
				//swaping pointers
				struct line* buf = current;
				current = lesser;
				lesser = buf;
			}
		}
	}
}*/