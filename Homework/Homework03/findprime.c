#include <stdio.h>
#include <math.h>

int isPrime(int num);

int main(){
  int min = 1000;
  int max = 1000000;
  int i = min;
  int count = 0;

  while(i<=max){
    count += isPrime(i);
    i++;
  }
  printf("start: %d, end: %d\n",min,max);
  printf("total number of primes: %d\n",count);
}

int isPrime(int num){
  if(num == 1){
    return 0;
  }
  
  int i = 2;
  int flag = 1;

  while(i<=sqrt(num)+1 && flag != 0){
    if(num%i==0){
      flag = 0; //set the flag to 0 if the number is not prime
    }
    i++;
  }
  return flag;

}
