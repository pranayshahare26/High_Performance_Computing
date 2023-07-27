#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

#define VECTORSIZE 	5000
#define NUM_THDS	256

__global__ void matmul(int *A, int *B, int *C)
{
	int myid = blockIdx.x*blockDim.x+threadIdx.x;
	int i = myid / VECTORSIZE;	
	int j = myid % VECTORSIZE;
	int k;
	int sum = 0;
	if(myid < (VECTORSIZE*VECTORSIZE))
	{
		for(k=0;k<VECTORSIZE;k++)
		{
			sum = sum + A[i*VECTORSIZE+k]*B[k*VECTORSIZE+j];	
		}
		C[i*VECTORSIZE+j] =  sum;
	}
}

int main(int argc, char **argv)
{
	int i, j;
	int *A, *B, *C, *Ad, *Bd, *Cd;		
	double exe_time;
	struct timeval stop_time, start_time;
	
	//Allocate and initialize the arrays
	A = (int *)malloc(VECTORSIZE*VECTORSIZE*sizeof(int));
	B = (int *)malloc(VECTORSIZE*VECTORSIZE*sizeof(int));
	C = (int *)malloc(VECTORSIZE*VECTORSIZE*sizeof(int));
	
	//Initialize data to some value
	for(i=0;i<VECTORSIZE;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			A[i*VECTORSIZE+j] = 1;
			B[i*VECTORSIZE+j] = 2;
			C[i*VECTORSIZE+j] = 0;	
		}
	}
	
	//print the data
	/*printf("\nInitial data: \n");
	printf("\n A matrix:\n");
	for(i=0;i<VECTORSIZE;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			printf("\t%d ", A[i*VECTORSIZE+j]);	
		}
		printf("\n");
	}
	printf("\n B matrix:\n");
	for(i=0;i<VECTORSIZE;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			printf("\t%d ", B[i*VECTORSIZE+j]);	
		}
		printf("\n");
	}*/	
	
	gettimeofday(&start_time, NULL);
	
	int total_threads = VECTORSIZE*VECTORSIZE;
	int num_thds_per_block = NUM_THDS; 
	int num_blocks = total_threads / num_thds_per_block + 1;
	
	cudaMalloc(&Ad, VECTORSIZE*VECTORSIZE*sizeof(int));
	cudaMemcpy(Ad, A, VECTORSIZE*VECTORSIZE*sizeof(int), cudaMemcpyHostToDevice);
	
	cudaMalloc(&Bd, VECTORSIZE*VECTORSIZE*sizeof(int));
	cudaMemcpy(Bd, B, VECTORSIZE*VECTORSIZE*sizeof(int), cudaMemcpyHostToDevice);
	
	cudaMalloc(&Cd, VECTORSIZE*VECTORSIZE*sizeof(int));
	
	matmul<<<num_blocks,num_thds_per_block>>>(Ad,Bd,Cd);
	
	cudaMemcpy(C, Cd, VECTORSIZE*VECTORSIZE*sizeof(int), cudaMemcpyDeviceToHost);
		
	/*for(i=0;i<VECTORSIZE;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			sum = 0;
			for(k=0;k<VECTORSIZE;k++)
			{
				sum = sum + A[i*VECTORSIZE+k]*B[k*VECTORSIZE+j];	
			}
			C[i*VECTORSIZE+j] =  sum;
		}
	}*/
	
	gettimeofday(&stop_time, NULL);	
	exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));
	
	//print the data
	/*printf("\n C matrix:\n");
	for(i=0;i<VECTORSIZE;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			printf("\t%d ", C[i*VECTORSIZE+j]);	
		}
		printf("\n");
	}*/
	
	printf("\nC[5*VECTORSIZE+5] = %d ", C[5*VECTORSIZE+5]);	
	
	printf("\nExecution time is = %lf seconds\n", exe_time);
	
	printf("\nProgram exit!\n");
	
	//Free arrays
	free(A); 
	free(B);
	free(C);
	cudaFree(Ad); 
	cudaFree(Bd);
	cudaFree(Cd);
}

/*

The code is performing matrix multiplication using CUDA parallel programming. It defines the size of the vectors and the number of threads to be used. It then defines a kernel function  `matmul`  which performs the matrix multiplication for a given block and thread. The main function initializes the arrays A, B, and C, and then allocates memory on the GPU for A, B, and C. It copies the data from the host to the device, calls the  `matmul`  kernel function, and then copies the result back to the host. Finally, it calculates the execution time and prints the result.
Step-wise explanation of the code:
1. Include necessary header files:  `stdio.h` ,  `stdlib.h` ,  `sys/time.h` .
2. Define the size of the vectors ( `VECTORSIZE` ) and the number of threads ( `NUM_THDS` ).
3. Define the kernel function  `matmul`  which performs matrix multiplication for a given block and thread.
4. Define the main function.
5. Declare variables:  `i` ,  `j` ,  `A` ,  `B` ,  `C` ,  `Ad` ,  `Bd` ,  `Cd` ,  `exe_time` ,  `stop_time` ,  `start_time` .
6. Allocate memory for arrays A, B, and C using  `malloc` .
7. Initialize the data in arrays A, B, and C.
8. Get the start time using  `gettimeofday` .
9. Calculate the total number of threads, number of threads per block, and number of blocks.
10. Allocate memory on the GPU for A, B, and C using  `cudaMalloc` .
11. Copy data from host to device using  `cudaMemcpy` .
12. Call the  `matmul`  kernel function with the specified number of blocks and threads.
13. Copy the result from the device to the host using  `cudaMemcpy` .
14. Get the stop time using  `gettimeofday` .
15. Calculate the execution time.
16. Print the result of C[5*VECTORSIZE+5].
17. Print the execution time.
18. Free the allocated memory for A, B, and C using  `free` .
19. Free the allocated memory on the GPU using  `cudaFree` .
20. End the program.

*/