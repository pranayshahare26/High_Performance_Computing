#include <stdio.h>
#include <omp.h>
int main() {
    int n, i,val;
    unsigned long long fact = 1;
    printf("Enter an integer: ");
    scanf("%d", &n);

    //shows error if the user enters a negative integer
    if (n < 0)
        printf("Error! Factorial of a negative number doesn't exist.");
    else {
        #pragma omp parallel firstprivate(fact)
	{
        for (i = 1; i <= n; ++i) {
            fact *= i;
        }
	#pragma omp barrier
        val = omp_get_thread_num();
        if(val == 1)
        printf("Factorial of %d = %llu\n", n, fact);
	}
    }

    return 0;
}
