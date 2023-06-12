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
		// Calculate my factorial
		int my_value = 1;
		for(int i = 2; i <= omp_get_thread_num(); i++)
		{
			my_value *= i;
		}

		// Add my value to the total
		#pragma omp critical
		{
			printf("[Thread %d] Total before I add my value (%d): %d.\n", omp_get_thread_num(), my_value, total);
			total += my_value;
			printf("[Thread %d] Total after I added my value: %d.\n", omp_get_thread_num(), total);
		}
	}

	return 0;
}
