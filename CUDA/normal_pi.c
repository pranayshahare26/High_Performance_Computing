#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define N 1000000

int main()
{

        double step;
        int i;
        double x, pi, sum = 0.0;
        double exe_time;
	struct timeval stop_time, start_time;
        gettimeofday(&start_time, NULL);
        step = 1.0/(double)N;

        for(i=0; i<N; i++)
        {
                x = (i)*step;
                sum = sum + 4.0/(1.0+x*x);
        }
        pi = step*sum;
        gettimeofday(&stop_time, NULL);	
	exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));
        printf("Approximate Value of pi is %f\nExecution time is = %lf seconds\n", pi, exe_time);

        return 0;
}
