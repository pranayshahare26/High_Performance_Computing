#include <stdio.h>
#include <omp.h>

long long factorial(int n)
{
	long long result = 1;
	int i;
    	#pragma omp parallel for
    	for (i = 1; i <= n; i++)
	{
		#pragma omp atomic	
		result *= i;
    	}
   	 return result;
}
int main()
{
    int num = 5;
    long long fact;
    fact = factorial(num);
    printf("Factorial of %d is %lld\n", num, fact);
    return 0;
}

