#include <omp.h>
#include <stdio.h>
int main (int argc, char *argv[]){
int n, i, sum = 0;
printf("Enter a positive integer: ");
scanf("%d", &n);
int val = omp_get_thread_num();

printf("First parallel region\n");
#pragma omp parallel if(omp_in_parallel) num_threads(8)
    {
    #pragma omp parallel private(sum)
    {
    for (i = 1; i <= n; ++i) {
        sum += i;
    }
    #pragma omp barrier
    val = omp_get_thread_num();
    #pragma omp single
    {
    printf("Sum = %d\n", sum);
    }
    }
  }
printf("second parallel region\n");
int m;
unsigned long long fact = 1;
printf("Enter an integer: ");
scanf("%d", &m);
val = omp_get_thread_num();
#pragma omp parallel num_threads(4)
    {
    //shows error if the user enters a negative integer
    if (m < 0)
        printf("Error! Factorial of a negative number doesn't exist.");
    else {
        #pragma omp parallel firstprivate(fact)
        {
        for (int i = 1; i <= m; ++i) {
            fact *= i;
        }
        #pragma omp barrier
   	val = omp_get_thread_num();     
        #pragma omp single
	{
        printf("Factorial of %d = %llu\n", m, fact);
	}
        }
    }

    }

return 0;
}

