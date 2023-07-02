#include<stdio.h>
#include<omp.h>
#define N 5
int main()
{
	int a=10; //shared
	int b=20;
	int c=30;
	omp_set_num_threads(N);
	#pragma omp parallel for
	//#pragma omp prallel
	for(int i=0; i<N; i++)
	{
		c=a+b; //private
		printf("The thread %d value is %d\n",omp_get_thread_num(),c);
	}
	return 0;
}
