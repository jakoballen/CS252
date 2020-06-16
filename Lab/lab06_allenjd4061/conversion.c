#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int binToDec(char* bin);
char* decToBin(int dec);

/*
 *CS252 - Lab 06 Problem 01
 *Author: Jakob Allen (allenjd4061)
 */

int main(){
	char* bin = "11001";
	int test = binToDec(bin);

	int dec = 9;
	char* d2b = decToBin(dec);

	printf("Call to binToDec given %s results in: %d\n", bin, test);
	printf("Call to decToBin given %d results in: ", dec);
	int len = strlen(d2b);
	int i;
	for(i = len; i>=0; i--){
		printf("%c", d2b[i]); //print the array in reverse order
	}
	printf("\n");

	free(d2b);
	return 0;
}

int binToDec(char* bin){
	int result = 0;
	int i = 0;
	while(*(bin+i) != '\0'){
		result +=(*(bin+i)-48); //add the character to the result

		if(*(bin+i+1) != '\0'){
			result = result*2; //multiply by two if the next character is not null
		}
		i++;
	}
	return result;
}

char* decToBin(int dec){

	double j=0.0;
	while(pow(2.0,j)<dec){
		j+= 1.0; //find the largest power that fits into dec
	}

	char* bin = (char*) malloc((j+1)*sizeof(char));

	int i=0;
	while(dec>0){
		*(bin+i) = dec % 2 + 48; //add the character '0' or '1' to the array
		dec = dec / 2;
		i++;
	}

	*(bin+i) = '\0'; //add null character to finish the string
	return bin;
}
