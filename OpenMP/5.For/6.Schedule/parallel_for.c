#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[])
{
	omp_set_num_threads(3);
 
	printf("With no chunksize passed:\n");
	#pragma omp parallel for schedule(static)
	for(int i = 0; i < 10; i++)
	{
		printf("Thread %d processes iteration %d.\n", omp_get_thread_num(), i);
	}
	printf("With a chunksize of 2:\n");

	#pragma omp parallel for schedule(static, 2)
	for(int i = 0; i < 10; i++)
	{
		printf("Thread %d processes iteration %d.\n", omp_get_thread_num(), i);
	}
 
	return 0;
}
