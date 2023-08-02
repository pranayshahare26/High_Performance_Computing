#include<stdio.h>

int do_sum(){
	int sum = 0;
	for(int i=0; i<10; i++)
		sum += i;
	return sum;
}

int main (int argc, char *argv[]){
	
	int sum = 0;
	
	sum = do_sum();

	printf("Sum = %d\n", sum);
	return 0;
}