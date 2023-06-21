#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<cuda_runtime.h>
 #define N 1000000
 __global__ void is_prime(int* d_count)
{
    int flag = 0;
    for(int i=3; i<N; i++)
    {
        flag = 0;
        for(int j=2; j<i && flag == 0; j++)
        {
            if((i % j) == 0)
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
     clock_t start_time = clock();
    is_prime<<<1, 1>>>(d_count);
    cudaDeviceSynchronize();
    clock_t stop_time = clock();
     cudaMemcpy(&count, d_count, sizeof(int), cudaMemcpyDeviceToHost);
    cudaFree(d_count);
     double exe_time = ((double) (stop_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n Number of prime numbers = %d \n Execution time is = %lf seconds\n", count, exe_time);
     return 0;
}