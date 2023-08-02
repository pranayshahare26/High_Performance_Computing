#include<stdio.h>

int main (int argc, char *argv[]){
	
	int sum = 0;
	
	for(int i=0; i<10; i++)
		sum += i;
	
	
	printf("Sum = %d\n", sum);
	return 0;
}