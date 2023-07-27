#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#define N 100000

__global__ void pi_calc(double *sum)
{
	int myid = blockIdx.x*blockDim.x + threadIdx.x;	
	double x, step;
	if(myid<N)
	{
		step = 1.0/(double)N;
		x = (myid)*step;
		sum[myid] = 4.0/(1.0+x*x);
	}
}
/*
step = 1.0/(double)N;
		for(i=0; i<N; i++){
				x = (i)*step;
				sum = sum + 4.0/(1.0+x*x);
		}
		pi = step*sum;
*/
int main()
{
	double *sum, *sum_d;
	int i=0;
	double total = 0.0;
	double pi, step;
	double exe_time;
	step = 1.0/(double)N;
	struct timeval stop_time, start_time;
	
	sum = (double *)malloc(N*sizeof(double));
	cudaMalloc(&sum_d, N*sizeof(double));
	
	gettimeofday(&start_time, NULL);
	
	int thds_per_block = 256;
	int num_blocks = (N/thds_per_block)+1;
	
	pi_calc<<< num_blocks,thds_per_block >>>(sum_d);
	cudaMemcpy(sum, sum_d, N*sizeof(double), cudaMemcpyDeviceToHost);
	
	for(i=0; i<N; i++)
	{
		total += sum[i];
	}
	pi = step*total;
	
	gettimeofday(&stop_time, NULL);	
	exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));
		
	printf("\nValue of pi = %lf", pi);
	printf("\nExecution time is = %lf seconds\n", exe_time);
	cudaFree(sum_d); 
	free(sum);
}

/*

This code calculates the value of pi using the Monte Carlo method in parallel using CUDA. 
1. The code includes necessary header files: stdio.h, stdlib.h, and sys/time.h.
2. The constant N is defined with a value of 9000000.
3. The kernel function "pi_calc" is defined. It takes a pointer to a double variable "sum" as an argument.
4. Inside the kernel function, each thread calculates a portion of the sum required to calculate pi.
5. The myid variable is calculated based on the thread and block indices.
6. If myid is less than N, the thread calculates the value of x and the corresponding sum and stores it in the sum array.
7. The main function starts.
8. Various variables are declared including sum, sum_d (device memory for sum), i, total, pi, step, and exe_time.
9. The sum array is allocated memory using malloc.
10. Device memory for sum is allocated using cudaMalloc.
11. The start time is recorded using gettimeofday.
12. The number of threads per block is set to 256 and the number of blocks is calculated based on N and the number of threads per block.
13. The pi_calc kernel function is launched with the specified number of blocks and threads per block.
14. The sum array is copied back from device memory to host memory using cudaMemcpy.
15. The total sum is calculated by iterating over the sum array.
16. The final value of pi is calculated by multiplying the step value with the total sum.
17. The stop time is recorded using gettimeofday.
18. The execution time is calculated by subtracting the start time from the stop time.
19. The calculated value of pi and the execution time are printed.
20. Device memory for sum is freed using cudaFree.
21. Host memory for sum is freed using free.

*/