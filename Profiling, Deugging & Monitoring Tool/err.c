#include<stdio.h>

int main (int argc, char *argv[]){
	int arr[10] = {10, 20, 30, 40, 50, 60, 70};
	int arr_len = 7;
	float sum = 0;

	for (int i = arr_len-1; i>0; i--)
		sum += arr[i]/(i*10);

	printf("Sum = %f\n", sum);	
	return 0;
}