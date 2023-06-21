#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#define N 1000000

/*
                N  PRIME_NUMBER

                1           0
               10           4
              100          25
            1,000         168
           10,000       1,229
          100,000       9,592
        1,000,000      78,498
       10,000,000     664,579
      100,000,000   5,761,455
    1,000,000,000  50,847,534

*/
int main()
{
    int i, j;
    int count = 1;
    double exe_time;
    struct timeval stop_time, start_time;
    gettimeofday(&start_time, NULL);
    #pragma omp parallel for reduction(+:count)
    for (i = 3; i < N; i++) 
    {
        int flag = 0;
        #pragma omp parallel for reduction(+:flag)
        for (j = 2; j < i; j++) 
        {
            if ((i % j) == 0) 
            {
                flag = 1;
            }
        }
        if (flag == 0) 
        {
            count++;
        }
    }
    gettimeofday(&stop_time, NULL);
    exe_time = (stop_time.tv_sec + (stop_time.tv_usec / 1000000.0)) - (start_time.tv_sec + (start_time.tv_usec / 1000000.0));
    printf("\n Number of prime numbers = %d \n Execution time is = %lf seconds\n", count, exe_time);
    return 0;
}