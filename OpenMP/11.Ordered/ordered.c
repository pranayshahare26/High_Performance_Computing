#include <stdio.h>
#include <omp.h>

int main(void)
{    
#pragma omp parallel for ordered
for (int i = 1; i <= 8; i++)
{
    #pragma omp ordered
    printf("Thread %d is executing iteration %d \n", omp_get_thread_num(), i);
}
    return 0;
}