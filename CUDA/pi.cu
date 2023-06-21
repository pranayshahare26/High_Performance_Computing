#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#define N 1000000
#define THREADS_PER_BLOCK 256

__global__ void calculate_pi(double step, double* sum) 
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    double x = (i + 0.5) * step;
    if (i < N) 
    {
        sum[i] = 4.0 / (1.0 + x * x);
    }
}
int main() 
{
    double step = 1.0 / (double)N;
    double* sum_host = (double*)malloc(N * sizeof(double));
    double* sum_device;
    cudaMalloc(&sum_device, N * sizeof(double));
    int num_blocks = (N + THREADS_PER_BLOCK - 1) / THREADS_PER_BLOCK;
    calculate_pi<<<num_blocks, THREADS_PER_BLOCK>>>(step, sum_device);
    cudaMemcpy(sum_host, sum_device, N * sizeof(double), cudaMemcpyDeviceToHost);
    double pi = 0.0;
    for (int i = 0; i < N; i++) 
    {
        pi += sum_host[i];
    }
    pi *= step;
    printf("Approximate Value of pi is %f.\n", pi);
    
    free(sum_host);
    cudaFree(sum_device);
    return 0;
}