#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[])
{
	// Use 4 threads when creating OpenMP parallel regions
	omp_set_num_threads(4);
	int total = 0;
	// Create the parallel region
	#pragma omp parallel default(none) shared(total)
	{
		for(int i = 0; i < 10; i++)
		{
			// Atomically add one to the total
			#pragma omp atomic
			total++;
		}
	}
	printf("Total = %d.\n", total);
	return 0;
}
