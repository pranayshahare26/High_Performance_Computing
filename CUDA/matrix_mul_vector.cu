#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define VECTORSIZE 10000

__global__ void matrix_multiply(int *A, int *B, int *C, int size)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j, k, sum;
    if (i < size)
    {
        for (j = 0; j < size; j++)
        {
            sum = 0;
            for (k = 0; k < size; k++)
            {
                sum += A[i * size + k] * B[k * size + j];
            }
            C[i * size + j] = sum;
        }
    }
}
int main(int argc, char **argv)
{
    int *A, *B, *C;
    int *d_A, *d_B, *d_C;
    double exe_time;
    struct timeval stop_time, start_time;
     //Allocate and initialize the arrays
    A = (int *)malloc(VECTORSIZE * VECTORSIZE * sizeof(int));
    B = (int *)malloc(VECTORSIZE * VECTORSIZE * sizeof(int));
    C = (int *)malloc(VECTORSIZE * VECTORSIZE * sizeof(int));
     //Initialize data to some value
    for (int i = 0; i < VECTORSIZE; i++)
    {
        for (int j = 0; j < VECTORSIZE; j++)
        {
            A[i * VECTORSIZE + j] = 1;
            B[i * VECTORSIZE + j] = 2;
            C[i * VECTORSIZE + j] = 0;
        }
    }
     //print the data
  /*  printf("\nInitial data: \n");
    printf("\n A matrix:\n");
    for (int i = 0; i < VECTORSIZE; i++)
    {
        for (int j = 0; j < VECTORSIZE; j++)
        {
            printf("\t%d ", A[i * VECTORSIZE + j]);
        }
        printf("\n");
    }
    printf("\n B matrix:\n");
    for (int i = 0; i < VECTORSIZE; i++)
    {
        for (int j = 0; j < VECTORSIZE; j++)
        {
            printf("\t%d ", B[i * VECTORSIZE + j]);
        }
        printf("\n");
    }*/
     //Allocate memory on the device
    cudaMalloc((void **)&d_A, VECTORSIZE * VECTORSIZE * sizeof(int));
    cudaMalloc((void **)&d_B, VECTORSIZE * VECTORSIZE * sizeof(int));
    cudaMalloc((void **)&d_C, VECTORSIZE * VECTORSIZE * sizeof(int));

     // Copy data from host to device
    cudaMemcpy(d_A, A, VECTORSIZE * VECTORSIZE * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, VECTORSIZE * VECTORSIZE * sizeof(int), cudaMemcpyHostToDevice);

     // Launch the kernel on the GPU
    int threadsPerBlock = 256;
    int blocksPerGrid = (VECTORSIZE + threadsPerBlock - 1) / threadsPerBlock;
    gettimeofday(&start_time, NULL);
    matrix_multiply<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, VECTORSIZE);
    gettimeofday(&stop_time, NULL);

     // Copy the result from device to host
    cudaMemcpy(C, d_C, VECTORSIZE * VECTORSIZE * sizeof(int), cudaMemcpyDeviceToHost);
    exe_time = (stop_time.tv_sec + (stop_time.tv_usec / 1000000.0)) - (start_time.tv_sec + (start_time.tv_usec / 1000000.0));

     //print the data
  /*  printf("\n C matrix:\n");
    for (int i = 0; i < VECTORSIZE; i++)
    {
        for (int j = 0; j < VECTORSIZE; j++)
        {
            printf("\t%d ", C[i * VECTORSIZE + j]);
        }
        printf("\n");
    }*/
    printf("\nExecution time is = %lf seconds\n", exe_time);
    printf("\nProgram exit!\n");

     //Free arrays
    free(A);
    free(B);
    free(C);

     // Free memory on the device
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    return 0;
}

/*

This program performs matrix multiplication on a GPU using CUDA. It multiplies two matrices A and B of size 10,000 x 10,000 and stores the result in matrix C. The program also measures the execution time of the matrix multiplication operation.
Here's a step-by-step explanation of the code:
1. It includes necessary libraries and defines the size of the vectors to be used.
2. The  `matrix_multiply`  function is a CUDA kernel that performs the matrix multiplication. It calculates the index  `i`  for each thread and then checks if  `i`  is less than  `size`  (the size of the matrix). If it is, it performs the multiplication and sum operations for the elements of the matrices A and B, and stores the result in matrix C.
3. In the  `main`  function, it first allocates memory for the matrices A, B, and C on the host (CPU) using  `malloc` .
4. It initializes the elements of matrices A and B to 1 and 2 respectively, and the elements of matrix C to 0.
5. It allocates memory for matrices A, B, and C on the device (GPU) using  `cudaMalloc` .
6. It copies the data from the host to the device using  `cudaMemcpy` .
7. It calculates the number of blocks needed for the GPU execution and records the start time.
8. It launches the  `matrix_multiply`  kernel on the GPU.
9. It records the stop time after the kernel execution.
10. It copies the result (matrix C) from the device to the host using  `cudaMemcpy` .
11. It calculates the execution time and prints it out.
12. Finally, it frees the memory allocated for the matrices on the host and the device using  `free`  and  `cudaFree`  respectively.

*/