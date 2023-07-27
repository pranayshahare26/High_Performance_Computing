#include<stdio.h>
#include<stdlib.h>

#define ARRSIZE 100000

__global__ void arradd(int* md, int* nd, int* pd)
{
	int myid = threadIdx.x;
	pd[myid] = md[myid] + nd[myid];
}


int test_result(int *m, int *n, int *p, int *md, int *nd, int *pd, int num_threads)
{
	int size = num_threads*sizeof(int);
	int i, flag;
	flag = 0;
	cudaMalloc(&md, size);
	cudaMemcpy(md, m, size, cudaMemcpyHostToDevice);

	cudaMalloc(&nd, size);
	cudaMemcpy(nd, n, size, cudaMemcpyHostToDevice);

	cudaMalloc(&pd, size);

	dim3   DimGrid(1, 1);     
	dim3   DimBlock(num_threads, 1);

	arradd<<< DimGrid,DimBlock >>>(md,nd,pd);

	cudaMemcpy(p, pd, size, cudaMemcpyDeviceToHost);
	
	for(i=0;i<num_threads;i++)
	{
		if(p[i] != 2*i)
		{
			flag = 1;
			break;
		}
	}
	return flag;
}
int main()
{
	//int size = ARRSIZE * sizeof(int);
	int m[ARRSIZE], n[ARRSIZE], p[ARRSIZE],*md, *nd,*pd;
	int i=0;
    int start, end, num_threads;
    int flag;
	for(i=0; i<ARRSIZE; i++ )
	{
		m[i] = i;
		n[i] = i;
		p[i] = 0;
	}
    start = 1;
    end = 10000;
    printf("\n Choosing Start...");
    while(1)
    {   
        printf("\n Start = %d", start);
        flag = test_result(m, n, p, md, nd, pd, start);
	    if(flag != 0)   // Answers match
	    {
	        start = start/2;
	    }
	    else
	    {
	        break;
	    }
    }    
    printf("\n Choosing End...");
    while(1)
    {
	    printf("\n End = %d", end);
        flag = test_result(m, n, p, md, nd, pd, end);
	    if(flag == 0)   // Answers match
	    {
	        end = end *2;
	    }
	    else
	    {
	        break;
	    }	    
    }
    printf("\n Setting Start = %d and End = %d", start, end);
    while(1)
    {
	    num_threads = (start + end)/2;
	    printf("\n Start = %d, End = %d, num_threads = %d", start, end,num_threads);
	    flag = test_result(m, n, p, md, nd, pd, num_threads);
	    if(flag == 0)   // Answers match
	    {
	        start = num_threads;
	        if((start == end) || ((end-start) == 1))
	        {
	            break;
	        }
	    }
	    else
	    {
	        end = num_threads;
	    }
    }
	printf("\nFinal value of num_threads = %d \n", num_threads);
		
	cudaFree(md); 
	cudaFree(nd);
	cudaFree(pd);	
}

/*

The code is performing a binary search to find the optimal number of threads for the kernel function "arradd". 
The "arradd" function is a CUDA kernel function that takes three integer arrays as input: "md", "nd", and "pd".
It calculates the sum of the corresponding elements of "md" and "nd" and stores the result in "pd".
The "test_result" function is used to test the correctness of the "arradd" function.
It takes six integer pointers as input: "m", "n", "p", "md", "nd", and "pd", and the number of threads.
It allocates memory on the GPU for "md", "nd", and "pd", copies the data from the host to the GPU, calls the "arradd" kernel function, copies the result back to the host, and checks if the result is correct.
If the result is not correct, it sets the "flag" variable to 1. Finally, it returns the value of "flag".
In the "main" function, the arrays "m", "n", and "p" are initialized with values from 0 to ARRSIZE-1. 
The variables "start" and "end" are initialized with values 1 and 10000 respectively.
The code then performs a binary search to find the optimal number of threads for the "arradd" kernel function. 
In the first while loop, the code repeatedly calls the "test_result" function with different values of "start" and checks if the result is correct. 
If the result is correct, it divides the value of "start" by 2. This loop continues until the result is not correct.
In the second while loop, the code repeatedly calls the "test_result" function with different values of "end" and checks if the result is correct. 
If the result is correct, it multiplies the value of "end" by 2. This loop continues until the result is not correct.
In the third while loop, the code calculates the value of "num_threads" as the average of "start" and "end". 
It calls the "test_result" function with this value and checks if the result is correct.
If the result is correct, it updates the value of "start" to "num_threads". If the difference between "end" and "start" is 1 or "start" is equal to "end", the loop breaks.
Otherwise, it updates the value of "end" to "num_threads".
Finally, the code prints the final value of "num_threads" and frees the allocated memory on the GPU.
Overall, the code is trying to find the optimal number of threads for the "arradd" kernel function by performing a binary search.

*/