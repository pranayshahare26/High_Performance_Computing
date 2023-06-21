#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<cuda_runtime.h>
#define N 1000000
/*
                N  PRIME_NUMBER

                1           0
               10           4
              100          25
            1,000         168
           10,000       1,229
          100,000       9,592
        1,000,000      78,498
       10,000,000     664,579
      100,000,000   5,761,455
    1,000,000,000  50,847,534

*/
__global__ void is_prime(int* d_count)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if(idx >= 3 && idx < N)
    {
        int flag = 0;
        for(int j=2; j<idx && flag == 0; j++)
        {
            if((idx % j) == 0)
            {
                flag = 1;
            }
        }
        if(flag == 0)
        {
            atomicAdd(d_count, 1);
        }
    }
}
int main()
{
    int count = 1;
    int* d_count;
    cudaMalloc(&d_count, sizeof(int));
    cudaMemcpy(d_count, &count, sizeof(int), cudaMemcpyHostToDevice);
    
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;
    clock_t start_time = clock();
    is_prime<<<blocksPerGrid, threadsPerBlock>>>(d_count);
    
    cudaDeviceSynchronize();
    clock_t stop_time = clock();
    cudaMemcpy(&count, d_count, sizeof(int), cudaMemcpyDeviceToHost);
    cudaFree(d_count);
    
    double exe_time = ((double) (stop_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n Number of prime numbers = %d \n Execution time is = %lf seconds\n", count, exe_time);
    return 0;
}