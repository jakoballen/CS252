#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
* CS252 - Lab 04
* Author: Jakob Allen (allenjd4061)
*/

void mostfrequent(int *counts, char *most_freq, int *qty_most_freq, int num_counts);

int main(){
	int num_counts, qty_most_freq;
	char most_freq;
	char str[80];
	int counts[26];

	printf("Enter a string: ");	//prompt the user for input
	scanf("%s",str);

	num_counts = 0;
	while(num_counts<26){	//set elements in counts to 0
		counts[num_counts]=0;
		num_counts++;
	}

	num_counts=0;
	while(str[num_counts] != '\0'){
		counts[(str[num_counts]-97)]++;	//increment counts at the char value - 97(a)
		num_counts++;
	}

	char* str1 = (char*) malloc(1000*sizeof(char));
	int* counts1 = (int*) calloc(26, sizeof(int));

	mostfrequent(counts, &most_freq, &qty_most_freq, num_counts);
	printf("Address of counts: %p, address of string: %p\n",counts,str);
	printf("HEAPAddress of counts: %p, address of string: %p\n",counts1,str1);
	printf("The most frequent character was '%c' with %d occurences. %lu characters were entered.\n", most_freq, qty_most_freq, strlen(str));
}

void mostfrequent(int *counts, char *most_freq, int *qty_most_freq, int num_counts){ //find the most typed character
	*qty_most_freq =0;
	*most_freq = 0;

	for (num_counts = 0; num_counts < 26; num_counts++) {	//find which index has the highest value
		if(counts[num_counts] > *qty_most_freq){
			*qty_most_freq = counts[num_counts];
			*most_freq = num_counts+97;	//index+'a'
		}
	}
}
