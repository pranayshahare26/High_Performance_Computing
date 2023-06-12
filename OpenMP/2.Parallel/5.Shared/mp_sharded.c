#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(int argc, char* argv[])
{
	// Use 2 OpenMP threads
	omp_set_num_threads(2);

	// The int that will be shared among threads
	int val = 0;

	printf("Value of \"val\" before the OpenMP parallel region: %d.\n", val);

	#pragma omp parallel shared(val)
	{
		// Step 1: thread 0 writes the value
		if(omp_get_thread_num() == 0)
		{
			printf("Thread 0 sets the value of \"val\" to 123.\n");
			val = 123;
		}

		// Threads wait each other before progressing to step 2
		#pragma omp barrier
		
		// Step 2: thread 1 reads the value
		if(omp_get_thread_num() == 1)
		{
			printf("Thread 1 reads the value of \"val\": %d.\n", val);
		}
	}

	printf("Value of \"val\" after the OpenMP parallel region: %d.\n", val);

	return 0;
}
