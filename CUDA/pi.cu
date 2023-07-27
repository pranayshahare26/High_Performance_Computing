#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
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
double get_time() 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}
int main() 
{
    double step = 1.0 / (double)N;
    double* sum_host = (double*)malloc(N * sizeof(double));
    double* sum_device;
    
    cudaMalloc(&sum_device, N * sizeof(double));
    int num_blocks = (N + THREADS_PER_BLOCK - 1) / THREADS_PER_BLOCK;
    
    double start_time = get_time();
    calculate_pi<<<num_blocks, THREADS_PER_BLOCK>>>(step, sum_device);
    
    cudaMemcpy(sum_host, sum_device, N * sizeof(double), cudaMemcpyDeviceToHost);
    
    double pi = 0.0;
    for (int i = 0; i < N; i++) 
    {
        pi += sum_host[i];
    }
    pi *= step;
    
    double end_time = get_time();
    double exe_time = end_time - start_time;
    
    printf("Approximate Value of pi is %f.\n", pi);
    printf("Execution time: %lf seconds\n", exe_time);
    
    free(sum_host);
    cudaFree(sum_device);
    return 0;
}

/*

This code calculates an approximate value of pi using the Monte Carlo method in parallel using CUDA.
Here is a step-by-step explanation of the code:
1. The code includes necessary header files and defines constants N (number of iterations) and THREADS_PER_BLOCK (number of threads per block in the GPU).
2. The code defines a CUDA kernel function  `calculate_pi`  which takes in the step size and a pointer to the device memory for storing the intermediate sums. The function calculates the value of pi for each thread using the Monte Carlo method and stores it in the device memory.
3. The code defines a helper function  `get_time`  which returns the current time in seconds.
4. In the  `main`  function:
   - The step size is calculated as 1.0 divided by the number of iterations.
   - Memory is allocated on the host for storing the intermediate sums.
   - Memory is allocated on the device for storing the intermediate sums.
   - The number of blocks required for the given number of iterations is calculated.
   - The start time is recorded using  `get_time` .
   - The  `calculate_pi`  kernel is launched on the device with the specified number of blocks and threads per block, passing the step size and device memory pointer.
   - The intermediate sums are copied from the device memory to the host memory.
   - The final value of pi is calculated by summing up all the intermediate sums and multiplying by the step size.
   - The end time is recorded using  `get_time` .
   - The execution time is calculated as the difference between the end time and start time.
   - The approximate value of pi and the execution time are printed.
   - The host and device memory are freed.
In summary, this code uses CUDA to calculate an approximate value of pi in parallel by dividing the work among multiple threads on the GPU. The intermediate sums are calculated in parallel and then combined on the host to obtain the final result. The execution time is also measured and printed.

*/