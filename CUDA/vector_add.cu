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

/*

The following code performs vector addition using CUDA. It initializes two arrays, A and B, with values from 0 to 19. It then allocates memory on the GPU for arrays A, B, and C, and copies the data from the CPU to the GPU. The vectorAdd kernel function is then called, which adds the corresponding elements of A and B and stores the result in C. The execution time of the kernel is measured using gettimeofday. Finally, the result is copied back from the GPU to the CPU and printed along with the execution time.
 Step-wise explanation of the code:
1. Include necessary header files: stdio.h, stdlib.h, sys/time.h.
2. Define constants ARRSIZE and BLOCK_SIZE.
3. Define the vectorAdd kernel function, which takes three integer pointers A, B, and C, and an integer elements_per_thread.
4. Inside the kernel function, calculate the thread index (tid) using threadIdx.x and blockIdx.x, and the start and end indices for the thread's portion of the arrays.
5. Use a for loop to add the corresponding elements of A and B and store the result in C.
6. Define the main function.
7. Declare pointers A, B, and C for the arrays on the CPU.
8. Calculate the number of elements per thread by dividing ARRSIZE by BLOCK_SIZE.
9. Allocate memory on the CPU for arrays A, B, and C using malloc.
10. Initialize the data in arrays A and B with values from 0 to 19.
11. Print the initial data in arrays A and B.
12. Declare pointers d_A, d_B, and d_C for the arrays on the GPU.
13. Declare variables exe_time, start_time, and stop_time for measuring the execution time.
14. Allocate memory on the GPU for arrays d_A, d_B, and d_C using cudaMalloc.
15. Copy the data from arrays A and B on the CPU to arrays d_A and d_B on the GPU using cudaMemcpy.
16. Measure the start time using gettimeofday.
17. Call the vectorAdd kernel function with BLOCK_SIZE blocks and elements_per_thread threads per block.
18. Measure the stop time using gettimeofday.
19. Calculate the execution time by subtracting the start time from the stop time.
20. Print the vector addition output from array C on the CPU.
21. Copy the result from array d_C on the GPU to array C on the CPU using cudaMemcpy.
22. Print the execution time.
23. Free the memory on the GPU using cudaFree.
24. Free the memory on the CPU using free.
25. Return 0 to indicate successful execution.

*/