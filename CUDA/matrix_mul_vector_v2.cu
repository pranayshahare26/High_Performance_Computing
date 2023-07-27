#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

#define VECTORSIZE 10000
#define NUM_THDS_PER_BLK 256

__global__ void matrix_vec_mul(int *A, int *B, int *C)
{
	int i = blockIdx.x;
	int j;
	int sum = 0;
	int range = NUM_THDS_PER_BLK/2;
	__shared__ int sum_arr[NUM_THDS_PER_BLK];
	sum_arr[threadIdx.x] = 0;
	if(blockIdx.x < VECTORSIZE)
	{
		for(j=threadIdx.x;j<VECTORSIZE;j+=blockDim.x)
		{
			sum = sum + A[i*VECTORSIZE+j]*B[i];	
		}
		sum_arr[threadIdx.x] = sum;
		__syncthreads();

		while(range>0)
        {
            if(threadIdx.x < range)
            {
                sum_arr[threadIdx.x] += sum_arr[threadIdx.x + range];
            }
            range = range /2;
            __syncthreads(); 
        }
		
		if(threadIdx.x == 0)
		{
		    C[i] =  sum_arr[0];
	    }
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
	
	int num_threads_per_block = NUM_THDS_PER_BLK;
	int numblocks = VECTORSIZE;
	
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

The code is a CUDA program that performs matrix-vector multiplication. 
It multiplies a matrix A of size VECTORSIZE x VECTORSIZE with a vector B of size VECTORSIZE to produce a vector C of size VECTORSIZE.
The main function starts by allocating and initializing the arrays A, B, and C.
A is initialized as a matrix of all 1s, and B is initialized as a vector of all 1s.
Then, the code measures the execution time using gettimeofday function.
Next, it allocates memory on the GPU for the arrays Ad, Bd, and Cd using cudaMalloc function.
It then copies the data from the CPU arrays A and B to the GPU arrays Ad and Bd using cudaMemcpy function.
The code defines the number of total threads as VECTORSIZE and the number of threads per block as NUM_THDS_PER_BLK.
It calculates the number of blocks needed as VECTORSIZE.
Then, it calls the kernel function matrix_vec_mul with the specified number of blocks and threads per block.
The kernel function performs the matrix-vector multiplication using parallel threads on the GPU.
Each thread calculates a partial sum and stores it in the shared array sum_arr.
The shared array is then reduced using a binary tree reduction algorithm until only one thread remains. 
The result is then stored in the output array C.
After the kernel execution, the result is copied back from the GPU array Cd to the CPU array C using cudaMemcpy function.
Finally, the code measures the execution time again and prints it along with a message indicating the program exit.
It also frees the allocated memory on the GPU using cudaFree function, and frees the arrays A, B, and C on the CPU using free function.

*/