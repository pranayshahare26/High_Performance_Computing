#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

#define VECTORSIZE 10

__global__ void matrix_vec_mul(int *A, int *B, int *C)
{
	int i = blockIdx.x*blockDim.x + threadIdx.x;
	int j;
	int sum = 0;
	if(i<VECTORSIZE)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			sum = sum + A[i*VECTORSIZE+j]*B[i];	
		}
		C[i] =  sum;
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
	B = (int *)malloc(VECTORSIZE*sizeof(int));
	C = (int *)malloc(VECTORSIZE*sizeof(int));
	
	//Initialize data to some value
	for(i=0;i<VECTORSIZE;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			A[i*VECTORSIZE+j] = 1;	
		}
		B[i] = 1;
	}
	
	//print the data
	/*printf("\nInitial data: \n");
	for(i=0;i<VECTORSIZE;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			printf("\t%d ", A[i*VECTORSIZE+j]);	
		}
		printf("\n");
	}
	printf("\n");
	for(i=0;i<VECTORSIZE;i++)
	{
		printf("\t%d", B[i]);
	}*/
	
	gettimeofday(&start_time, NULL);
	
	/*for(i=0;i<VECTORSIZE;i++)
	{
		sum = 0;
		for(j=0;j<VECTORSIZE;j++)
		{
			sum = sum + A[i*VECTORSIZE+j]*B[i];	
		}
		C[i] =  sum;
	}*/
	
	cudaMalloc(&Ad,VECTORSIZE*VECTORSIZE*sizeof(int));
	cudaMalloc(&Bd,VECTORSIZE*sizeof(int));
	cudaMalloc(&Cd,VECTORSIZE*sizeof(int));
	
	cudaMemcpy(Ad,A,VECTORSIZE*VECTORSIZE*sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(Bd,B,VECTORSIZE*sizeof(int),cudaMemcpyHostToDevice);
	
	int Total_num_Threads = VECTORSIZE;
	int num_threads_per_block = 256;
	int numblocks = Total_num_Threads/num_threads_per_block + 1;
	
	matrix_vec_mul<<<numblocks,num_threads_per_block>>>(Ad,Bd,Cd);
	
	cudaMemcpy(C,Cd,VECTORSIZE*sizeof(int),cudaMemcpyDeviceToHost);
	
	gettimeofday(&stop_time, NULL);	
	exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));
	
	//print the data
	/*printf("\n Matrix-Vector Multiplication output: \n");
	for(i=0;i<VECTORSIZE;i++)
	{
		printf("\t%d", C[i]);	
	}*/
	printf("\nExecution time is = %lf seconds\n", exe_time);	
	printf("\nProgram exit!\n");
	
	cudaFree(Ad);
	cudaFree(Bd);
	cudaFree(Cd);
	
	//Free arrays
	free(A); 
	free(B);
	free(C);
}

/*

The code is performing matrix-vector multiplication using CUDA. 
 1. The code defines the size of the vectors as VECTORSIZE.
2. The code then defines a CUDA kernel function called matrix_vec_mul, which takes three integer pointers as input: A, B, and C.
3. Inside the kernel function, it calculates the index i based on the block and thread indices, and initializes the sum variable.
4. It checks if i is less than VECTORSIZE, and if so, it enters a loop to calculate the sum by multiplying each element of row i in matrix A with the corresponding element in vector B, and adding it to the sum.
5. Finally, it stores the sum in the corresponding index of vector C.
6. The main function starts by declaring variables and allocating memory for arrays A, B, and C.
7. It then initializes the data in arrays A and B with the value 1.
8. It allocates memory on the GPU for arrays Ad, Bd, and Cd, and copies the data from arrays A and B on the host to the corresponding arrays on the GPU.
9. It calculates the number of blocks and threads per block needed to process the data, and calls the matrix_vec_mul kernel function with the specified number of blocks and threads per block.
10. It then copies the result from array Cd on the GPU back to array C on the host.
11. It calculates the execution time by measuring the start and stop time using the gettimeofday function.
12. It prints the execution time.
13. It frees the memory on the GPU.
14. It frees the memory for arrays A, B, and C on the host.

*/