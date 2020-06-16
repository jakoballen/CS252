#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int baseToDec(int base, char* value);
char* decToBase(int base, int dec);

/*
 *CS252 - Homework 02 Problem 01
 *Author: Jakob Allen (allenjd4061)
 */

int main(){
	//char* bin = "11001";
	char* hex = "24361f";
	int test = baseToDec(16, "24361f");

	int dec = test;
	char* d2b = decToBase(16, test);

	printf("Call to baseToDec given %s results in: %d\n", hex, test);
	printf("Call to decToBase given %d results in: ", dec);
	int len = strlen(d2b);
	int i;
	for(i = len; i>=0; i--){
		printf("%c", d2b[i]); //print the array in reverse order
	}
	printf("\n");

	free(d2b);
	return 0;
}

int baseToDec(int base, char* value){
	int result = 0;
	int i = 0;
	while(*(value+i) != '\0'){
		if(*(value+i)>='0' && *(value+i)<='9'){
			result +=(*(value+i)-'0'); //add the value to the result
		}else if(*(value+i)>='a' && *(value+i)<='f'){
			result +=(*(value+i)-'a'+10); //add the value to the result
		}else if(*(value+i)>='A' && *(value+i)<='F'){
			result +=(*(value+i)-'A'+10); //add the value to the result
		}

		if(*(value+i+1) != '\0'){
			result = result*base; //multiply by the base if the next character is not null
		}
		i++;
	}
	return result;
}

char* decToBase(int base, int dec){
	double j=0.0;
	while(pow(base,j)<dec){
		j+= 1.0; //find the largest power that fits into dec
	}

	char* bin = (char*) malloc((j+1)*sizeof(char));

	int i=0;
	int remainder;
	int quotient = dec;
	while(quotient!=0){
		remainder = quotient % base;
		if(remainder < 10){
			*(bin+i) = remainder + '0';
		}else{
				*(bin+i) = remainder + 'A' - 10;
		}
		i++;
		quotient = quotient / base;
	}

	*(bin+i) = '\0'; //add null character to finish the string
	return bin;
}
