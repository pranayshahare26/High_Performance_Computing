#include<stdio.h>

void set_value(int v, int *ptr1, int *ptr2){
	ptr1 = &v;
	ptr2 = ptr1;
}

int main(int argc, char *argv[]){
	int *p1 = NULL;
	int *p2 = NULL;
	int value = 10;

	set_value(value, p1, p2);

	printf("Original value = %d\n", value);
	printf("P1 ref. value = %d\n", *p1);
	printf("P2 ref. value = %d\n", *p2);

	return 0;
}