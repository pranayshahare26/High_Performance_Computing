#include<stdio.h>
#include<omp.h>
#define N 8
int main()
{
	int a = 10; //shared
	int b = 20; //shared
	int c, i;
	omp_set_num_threads(N);
	#pragma omp parallel for
	//#pragma omp parallel
	for(i=0;i<N;i++)
	{
		c = a + b;
		printf("The thread %d value is %d\n",omp_get_thread_num(),c);
	}
	return 0;
}
