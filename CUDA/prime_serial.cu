#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sys/time.h>
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
    printf("\nNumber of prime numbers = %d \nExecution time is = %lf seconds\n", count, exe_time);
    return 0;
}

/*

The given code is a CUDA program that calculates the number of prime numbers from 3 to N, where N is defined as 1,000,000. It uses the concept of parallel computing to speed up the calculation process.
Here is a step-wise explanation of the code:
1. The code includes necessary header files and defines a constant N as 1,000,000.
2. The code defines a CUDA kernel function named "is_prime" that takes an integer pointer as an argument. This function will be executed on the GPU.
3. Inside the "is_prime" kernel function, each thread is assigned an index (idx) based on the block and thread dimensions. The index represents a number from 3 to N.
4. The kernel function checks if the index (idx) is divisible by any number from 2 to idx-1. If it is divisible, a flag is set to 1.
5. If the flag remains 0 after checking all the numbers, it means the index (idx) is a prime number. In that case, the atomicAdd function is used to increment the value pointed by d_count by 1.
6. The main function begins by initializing a count variable to 1. This count variable will store the number of prime numbers found.
7. Memory is allocated on the GPU for an integer variable d_count using cudaMalloc.
8. The value of count is copied from the host to the device using cudaMemcpy.
9. The block and thread dimensions are calculated based on the value of N. This determines the number of threads and blocks that will be used for parallel execution.
10. The start time is recorded using the clock function.
11. The "is_prime" kernel function is called with the calculated block and thread dimensions.
12. cudaDeviceSynchronize is used to ensure that all the threads have finished executing before proceeding.
13. The stop time is recorded using the clock function.
14. The value of count is copied from the device to the host using cudaMemcpy.
15. The memory allocated for d_count is freed using cudaFree.
16. The execution time is calculated using the start and stop times.
17. Finally, the number of prime numbers and the execution time are printed on the console.
In summary, the code calculates the number of prime numbers from 3 to 1,000,000 using parallel computing with CUDA. It utilizes multiple threads on the GPU to perform the calculations in parallel, which reduces the execution time compared to a sequential approach.

*/