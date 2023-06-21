#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#define N 400

__global__ void calc_square(int* a, int* aa)
{
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < N)
    {
        aa[tid] = a[tid] * a[tid];
    }
}
 int main()
{
    int a[N], aa[N];
    int* d_a, *d_aa;
    double exe_time;
    struct timeval stop_time, start_time;
     // Initialize the input array
    for (int i = 0; i < N; i++)
    {
        a[i] = i;
    }
    cudaMalloc(&d_a, N * sizeof(int));
    cudaMalloc(&d_aa, N * sizeof(int));
    cudaMemcpy(d_a, a, N * sizeof(int), cudaMemcpyHostToDevice);
    gettimeofday(&start_time, NULL);
    calc_square <<< (N + 255) / 256, 256 >>> (d_a, d_aa);
    cudaDeviceSynchronize();
    gettimeofday(&stop_time, NULL);	
    cudaMemcpy(aa, d_aa, N * sizeof(int), cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_aa);

    for (int i = 0; i < N; i++)
    {
        printf("%d ", aa[i]);
    }
    printf("\n");

	exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));
    printf("Execution time: %lf seconds\n", exe_time);
    return 0;
}