#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define ARRSIZE 20
#define BLOCK_SIZE 5

__global__ void vectorAdd(int *A, int *B, int *C, int elements_per_thread)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    int start = tid * elements_per_thread;
    int end = start + elements_per_thread;
     for (int i = start; i < end; i++)
    {
        C[i] = A[i] + B[i];
    }
}
int main()
{
    int *A, *B, *C;
    int elements_per_thread = ARRSIZE / BLOCK_SIZE;
    A = (int *)malloc(ARRSIZE * sizeof(int));
    B = (int *)malloc(ARRSIZE * sizeof(int));
    C = (int *)malloc(ARRSIZE * sizeof(int));
     // Initialize data to some value
    for (int i = 0; i < ARRSIZE; i++)
    {
        A[i] = i;
        B[i] = i;
    }
    printf("Initial data: \n");
    for (int i = 0; i < ARRSIZE; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
    for (int i = 0; i < ARRSIZE; i++)
    {
        printf("%d ", B[i]);
    }
    printf("\n");
    int *d_A, *d_B, *d_C;
    double exe_time;
    struct timeval start_time, stop_time;

    cudaMalloc((void **)&d_A, ARRSIZE * sizeof(int));
    cudaMalloc((void **)&d_B, ARRSIZE * sizeof(int));
    cudaMalloc((void **)&d_C, ARRSIZE * sizeof(int));
    cudaMemcpy(d_A, A, ARRSIZE * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, ARRSIZE * sizeof(int), cudaMemcpyHostToDevice);

    gettimeofday(&start_time, NULL);
    vectorAdd<<<BLOCK_SIZE, elements_per_thread>>>(d_A, d_B, d_C, elements_per_thread);
    gettimeofday(&stop_time, NULL);
    exe_time = (stop_time.tv_sec + (stop_time.tv_usec / 1000000.0)) - (start_time.tv_sec + (start_time.tv_usec / 1000000.0));

    printf("Vector addition output: \n");
    cudaMemcpy(C, d_C, ARRSIZE * sizeof(int), cudaMemcpyDeviceToHost);
    for (int i = 0; i < ARRSIZE; i++)
    {
        printf("%d ", C[i]);
    }
    printf("\n");
    printf("Execution time is = %lf seconds\n", exe_time);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    free(A);
    free(B);
    free(C);
    return 0;
}
