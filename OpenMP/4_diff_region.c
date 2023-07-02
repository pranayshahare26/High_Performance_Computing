#include<stdio.h>
#include<omp.h>
int main()
{
	printf("First parallel region:\n");
	#pragma omp parallel if(omp_in_parallel) num_threads(8)
	{
		printf("The threads is %d\n",omp_get_thread_num());
	}

	printf("Second parallel region:\n");
	#pragma omp parallel if(omp_in_parallel) num_threads(4)
	{
		printf("The threads is %d\n",omp_get_thread_num());
	}
return 0;
}
