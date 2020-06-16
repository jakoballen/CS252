#include <stdio.h>

/*
* CS252 - Homework 1 Problem 1
* Author: Jakob Allen (allenjd4061)
*/

void removeElement(int *array, int *length, int index);
void removeDupes(int *array, int *length);
void print_array(int *array, int length);

int main(){
	int arr[] = {9,3,5,4,3,3,5,6,7,1};
	int size = 10;

	printf("Number of elements: %d\nOriginal elements: ",size);
	print_array(arr,size);
	removeDupes(arr,&size);

	printf("\nNumber of unique elements: %d\nElements: ",size);
	print_array(arr,size);
	printf("\n");

	return 0;
}

void print_array(int *array, int length){
	int i;
	for(i=0; i<length; i++){
		if(i==0){
			printf("{%d",*array+0); //print first element of the array
		}else if(i == length-1){
			printf(", %d}", *(array+i)); //print the last element
		}else{
		printf(", %d", *(array+i)); //print the middle elements of the array
		}
	}
}

void removeDupes(int *array, int *length){
	int i,j;
	for (i = 0; i < *length; i++){
	        for (j = i + 1; j < *length; j++){
	            if (*(array+j) == *(array+i)) { //check if duplicate
	                removeElement(array, length, j);
									j--;
	            }
	        }
	    }
}
void removeElement(int *array, int *length, int index){
	int i;
	for (i = index; i < *length; i++){
			*(array+i) = *(array+i+1); //shift array elements to remove the element at the given index
	}
	(*length)--;
}
