#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define N 400

__global__ void calc_sum(double* a, double* b, double* c, double alpha)
{
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < N)
    {
        c[tid] = a[tid] + alpha * b[tid];
    }
}
int main()
{
    double a[N], b[N], c[N], alpha;
    double* d_a, *d_b, *d_c;
    alpha = 0.001;
    struct timeval stop_time, start_time;
    double exe_time;

    for (int i = 0; i < N; i++)
    {
        a[i] = i;
        b[i] = i;
        c[i] = 0;
    }
    cudaMalloc(&d_a, N * sizeof(double));
    cudaMalloc(&d_b, N * sizeof(double));
    cudaMalloc(&d_c, N * sizeof(double));
    cudaMemcpy(d_a, a, N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, N * sizeof(double), cudaMemcpyHostToDevice);

    gettimeofday(&start_time, NULL);
    calc_sum<<<(N + 255) / 256, 256>>>(d_a, d_b, d_c, alpha);
    cudaDeviceSynchronize();
    gettimeofday(&stop_time, NULL);

    cudaMemcpy(c, d_c, N * sizeof(double), cudaMemcpyDeviceToHost);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    for (int i = 0; i < N; i++)
    {
        printf("\t%lf", c[i]);
    }
    printf("\n");
    exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));
    printf("Execution time: %lf seconds\n", exe_time);
    return 0;
}
