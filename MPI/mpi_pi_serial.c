#include<stdio.h>
#include<stdlib.h>
#define N 1000000000

int main(){

        double step;
        int i;
        double x, pi, sum = 0.0;

        step = 1.0/(double)N;

        for(i=0; i<N; i++){
                x = (i)*step;
                sum = sum + 4.0/(1.0+x*x);
        }
        pi = step*sum;
        printf("Approximate Value of pi is %f.\n", pi);
        return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define N 10000000
int main()
{
        double step;
        int i;
        double x, pi, sum = 0.0;
        double start_time, end_time;
        
        step = 1.0/(double)N;
        start_time = omp_get_wtime();
        
        #pragma omp parallel for reduction(+:sum)
        for(i=0; i<N; i++)
        {
                x = (i)*step;
                sum = sum + 4.0/(1.0+x*x);
        }
        pi = step*sum;
        end_time = omp_get_wtime();
        printf("Approximate Value of pi is %f.\n", pi);
        printf("Execution Time: %f seconds.\n", end_time - start_time);
return 0;
}


#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define N 1000000000
int main()
{
        double step;
        int i;
        double x, pi, sum = 0.0;
        double start_time, end_time;
        int num_threads, tid;
        
        step = 1.0/(double)N;
        start_time = omp_get_wtime();
        
        #pragma omp parallel private(tid) shared(sum)
        {
                num_threads = omp_get_num_threads();
                tid = omp_get_thread_num();
                for(i=tid; i<N; i+=num_threads)
                {
                        x = (i)*step;
                        sum = sum + 4.0/(1.0+x*x);
                }
                printf("Thread %d: Sum = %f\n", tid, sum);
        }
        pi = step*sum;
        end_time = omp_get_wtime();
        
        printf("Approximate Value of pi is %f.\n", pi);
        printf("Execution Time: %f seconds.\n", end_time - start_time);
        return 0;
}