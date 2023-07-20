#include<stdio.h>
#define N 1000
void do_nothing(){
	int del = 0;
	printf("Inside do_nothing\n");
	for(int x=1; x<N; x++)
		del /= 10 * x;
}

void do_something(int n){
	long long sum = 0;
	printf("Inside do_something\n");
	for(int k=1; k<n; k++){
		sum += 10 + (k * n) / (k * 10);
	}
	do_nothing();
}

int main(int argc, char *argv[]){
	printf("Inside main\n");
	for(int i=1; i<N; i++){
		for(int j=0; j<N; j++){
			do_something(N);
		}
	}
	do_nothing();
	printf("Done\n");
}