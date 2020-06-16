#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
* CS252 - Homework 1 Problem 2
* Author: Jakob Allen (allenjd4061)
*/

void mostfrequent(int *counts, char *most_freq, int *qty_most_freq, int num_counts);

int main(){
	int num_counts, qty_most_freq;
	char most_freq;
	char* str = (char*) malloc(1000*sizeof(char));
	int* counts = (int*) calloc(26, sizeof(int));


	printf("Enter a string: ");	//prompt the user for input
	scanf("%s",str);


	num_counts=0;
	while(*(str+num_counts) != '\0'){

		*(counts+(*(str+num_counts)-97))+=1;
		num_counts++;
	}

	mostfrequent(counts, &most_freq, &qty_most_freq, num_counts);
	printf("The most frequent character was '%c' with %d occurences. %lu characters were entered.\n", most_freq, qty_most_freq, strlen(str));
	printf("Address of counts: %p, address of string: %p\n",counts,str);
	free(counts);
	free(str);
}

void mostfrequent(int *counts, char *most_freq, int *qty_most_freq, int num_counts){ //find the most typed character
	*qty_most_freq =0;
	*most_freq = 0;

	for (num_counts = 0; num_counts < 26; num_counts++) {	//find which index has the highest value
		if(*(counts+num_counts) > *qty_most_freq){
			*qty_most_freq = *counts+num_counts;
			*most_freq = num_counts+97;	//index+'a'
		}
	}
}
