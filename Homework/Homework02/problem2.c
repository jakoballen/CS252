#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int baseToDec(int base, char* value);
char* decToBase(int base, int dec);

/*
 *CS252 - Homework 02 Problem 02
 *Author: Jakob Allen (allenjd4061)
 */
 
int main(){
  printf("This is a variety base math program.\nEnter a number in the format NSN.\n(N = number in the given base) (S = mathemathical symbol)\nBinary numbers may exceed 7 characters, while\nnumbers of other base may not exceed 4 characters.\n ");

  char end[10];

  while(strcmp("n", end)!= 0){ //make sure the user wants to do another calculation
    int k, base, result, maxlen, number1, number2;

    printf("\nBase: ");
    scanf("%d",&base);
    while(!(base<=16 && base>=2)){ //verify a valid base was given
      printf("Error: Base is out of bounds. Enter a number between 2 and 16, inclusive.\n");
      printf("\nBase: ");
      scanf("%d",&base);
    }
	int success = 1;
	while(success != 0){
		int operation = 0;
		int i=0;
		int j=0;

		if(base==2){
		  maxlen = 7;
		}else{
		  maxlen = 4;
		}

		char* input = (char*) calloc((maxlen*3),sizeof(char)); //size of array is larger than necessary to allow for some error of input
		char* firstnum = (char*) calloc((maxlen+1), sizeof(char));
		char* secondnum = (char*) calloc((maxlen+1), sizeof(char));

		printf("Input: ");
		scanf("%s",input);
		
		if(strlen(input) > maxlen*2+1){
			printf("Error: Too many characters in input. The most characters allowed is %d.\n",maxlen*2+1);
		}else if(input[0] == '+' || input[0] == '-' || input[0] == '/' || input[0] == '*' || input[0] == '%'){
			printf("Error: The operation symbol cannot be the first character in your input.\n");
		}else{
			while(input[i] != '\0'){ //split up the input into parts the program can work with
				if(operation == 0 && (input[i] != '+' && input[i] != '-' && input[i] != '/' && input[i] != '*' && input[i] != '%')){ //the first number ends before the mathematical symbol
					firstnum[i] = input[i];
					i++;
				}else if(input[i] == '+' || input[i] == '-' || input[i] == '/' || input[i] == '*' || input[i] == '%'){ //the second number starts after the mathematical symbol
					firstnum[i] = '\0'; //add null so it is a valid string
					operation = input[i];
					i++;
				}else{
					secondnum[j] = input[i];
					j++;
					i++;
				}
			}
		}
			secondnum[j] = '\0';//add null so it is a valid string
		
			number1 = baseToDec(base, firstnum); //calculate the decimal values of the user's input
			number2 = baseToDec(base, secondnum);

			if(operation == '+'){ //figure out desired operation and complete the calculation
			  result = number1 + number2;
			}else if(operation == '-'){
			  result = number1 - number2;
			}else if(operation == '/' && number2 != 0){
			  result = number1 / number2;
			}else if(operation == '*'){
			  result = number1 * number2;
			}else if(operation == '%' && number2 != 0){
			  result = number1 % number2;
			}

			char* baseResult = decToBase(base, result);
			int resultLen = strlen(baseResult);

			if(strlen(firstnum)>maxlen){ //validate the input given
				printf("Error: Too many digits in first number. Max of %d digits.\n", maxlen);
			}else if(strlen(secondnum)>maxlen){
				printf("Error: Too many digits in second number. Max of %d digits.\n", maxlen);
			}else if(operation == 0 || firstnum[0] == '\0'){
				printf("Error: No operation symbol detected.\n");
			}else if(resultLen>maxlen){
				printf("Error: Bit overflow. max of %d bits allowed to represent resulting number.\n", maxlen);
			}else if(secondnum[0] == '\0'){
				printf("Error: Enter a second number after the operation symbol.\n");
			}else if(number2 == 0 && operation == '/'){
				printf("Error: Division by 0 is not allowed.\n");
			}else if(number2== 0 && operation == '%'){
				printf("Error: Mod by 0 is not allowed.\n");
			}else if (number2 > number1 && operation == '-'){
				printf("Error: Negative results are not allowed. Your second number must be smaller than the first while subtracting\n");
			}else{ //if the input given is valid, print the results of the computation
				printf("%s = ",input);
				while(maxlen - resultLen > 0){printf("0"); maxlen--;}
				for(k = resultLen; k>=0; k--){
					printf("%c", baseResult[k]); //print the array in reverse order
				}
				printf("\n");
				success = 0;
			}
			
			free(input);
			free(firstnum);
			free(secondnum);
			free(baseResult);
	}
	
    printf("\nWould you like to do another calculation? Enter 'n' to quit. ");
    scanf("%s",end);
  }
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
  	int j=0;
  	while(pow(base,j)<dec){
  		j++; //find the largest power that fits into dec
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
