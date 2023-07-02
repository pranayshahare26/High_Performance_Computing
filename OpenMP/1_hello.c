#include<stdio.h>
#include<omp.h>
int main()
{
	printf("Hello World\n");
	#pragma omp parallel num_threads(4)

	#pragma omp parallel
	{
	printf("Hello Parallel\n");
	}
	return 0;
}
