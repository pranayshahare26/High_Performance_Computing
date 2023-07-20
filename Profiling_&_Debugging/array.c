#include<stdio.h>
int main ()
{
	float marks[5];
	int i;
	int roll[5] = {1,2,3,4,5};
	marks[0] = 78.67;
	marks[1] = 67.34;
	marks[2] = 52.47;
	marks[3] = 43.56;
	marks[4] = 12.67;
	for(i=0; i<5; i++)
		printf("Roll %d = %.2f\n", roll[i], marks[i]);
	return 0;
}
		
