#include<stdio.h>
#include<omp.h>
int main()
{
	printf("Hello World\n");
	omp_set_num_threads(4);
	#pragma omp parallel

	//#pragma omp parallel num_threads(5)
	{
	printf("Hello Parallel\n");
	}
	return 0;
}
