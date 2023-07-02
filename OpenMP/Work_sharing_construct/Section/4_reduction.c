#include<stdio.h>
#include<omp.h>
#define NUM 100
int isprime( int x )
{
	for( int y = 2; y*y <= x; y++)
	{
		if(x % y == 0)
		return 0;
	}
	return 1;
}
int main()
{
	int sum = 0;
	int i;
	#pragma omp parallel
	{
		#pragma omp sections reduction (+:sum)
		{
			#pragma omp section
			{
				for (int i=2; i<=NUM; i++)
				{
					sum += isprime (i);
				}
			printf("Number of primes numbers: %d\n", sum);
			}
			#pragma omp section
			{
				for(int i=2; i<=NUM; i++)
				{
					sum += isprime(i);
				}
			printf("Number of primes numbers: %d\n", sum);
			}
		}
	}
return 0;
}
