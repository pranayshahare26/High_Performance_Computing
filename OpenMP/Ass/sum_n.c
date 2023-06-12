#include <stdio.h>
#include <omp.h>
int main() {
    int n, i, sum = 0;

    printf("Enter a positive integer: ");
    scanf("%d", &n);
    int val = omp_get_thread_num();
    #pragma omp parallel private(sum)
    { 
    for (i = 1; i <= n; ++i) {
        sum += i;
    }
    #pragma omp barrier
    val = omp_get_thread_num();
    if(val == 0)
    printf("Sum = %d\n", sum);
    }	
    return 0;
}
