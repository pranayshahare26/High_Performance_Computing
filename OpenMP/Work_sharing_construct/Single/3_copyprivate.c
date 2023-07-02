#include<stdio.h>
#include<omp.h>
int main()
{
	int a = 123;
	#pragma omp parallel default(none) firstprivate(a)
	{
		printf("Thread %d: a = %d.\n", omp_get_thread_num(), a);
		#pragma omp barrier
		#pragma onp single copyprivate(a)
		{
			a = 456;
			printf("Thread %d executes the single construct and changes a to %d.\n", omp_get_thread_num(), a);
		}
		printf("Thread %d: a = %d.\n", omp_get_thread_num(),a);
	}
return 0;
}
