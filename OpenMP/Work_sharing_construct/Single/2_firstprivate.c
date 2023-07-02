#include<stdio.h>
#include<omp.h>
#define N 5
int main()
{
	int i=1;
	float a[N], b[N], c[N], d[N];
	for(i=0; i<N; i++)
	{
		a[i] = i*1.5;
		b[i] = i*22.35;
	}
	#pragma omp parallel shared(a,b,c,d) firstprivate(i)
	{
		#pragma omp single
		{
			for(i=0; i<N; i++)
			{
				c[i] = a[i] + b[i];
				printf("!st loop a Working thread : %d # %f + %f = %f\n", omp_get_thread_num(),a[i],b[i],c[i]);
			}
			for(i=0; i<N; i++)
			{
				d[i] = a[i] * b[i];
				printf("2nd loop a working thread : %d # %f + %f = %f\n", omp_get_thread_num(),a[i],b[i],d[i]);
			}
		}
	}
return 0;
}
