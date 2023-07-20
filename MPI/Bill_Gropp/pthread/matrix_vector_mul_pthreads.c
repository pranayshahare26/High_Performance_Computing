#include<stdio.h>
#include<stdlib.h>
#include <pthread.h> 
#include<sys/time.h>

#define VECTORSIZE 12

int flag;
int *A, *B, *C;

/* Global variable:  accessible to all threads */
int thread_count;  

void *Hello(void* rank);  /* Thread function */

/*--------------------------------------------------------------------*/
int main() {
	long		 thread;  /* Use long in case of a 64-bit system */
	pthread_t* thread_handles; 
	 double exe_time;
	 int i,j;
	struct timeval stop_time, start_time;
	
	/* Get number of threads from command line */
	thread_count = 4; 
	thread_handles = malloc (thread_count*sizeof(pthread_t)); 
	
	
	//Allocate and initialize the arrays
	A = (int *)malloc(VECTORSIZE*VECTORSIZE*sizeof(int));
	B = (int *)malloc(VECTORSIZE*sizeof(int));
	C = (int *)malloc(VECTORSIZE*sizeof(int));
	
	//Initialize data to some value
	for(i=0;i<VECTORSIZE;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			A[i*VECTORSIZE+j] = 1;	
		}
		B[i] = 1;
	} 
	//print the data
	printf("\nInitial data: \n");
	printf("\nMatrix: \n");
	for(i=0;i<VECTORSIZE;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			printf("\t%d ", A[i*VECTORSIZE+j]);	
		}
		printf("\n");
	}
	printf("\nVector: \n");
	for(i=0;i<VECTORSIZE;i++)
	{
		printf("\t%d", B[i]);
	}
	
	gettimeofday(&start_time, NULL);
	 
	for (thread = 0; thread < thread_count; thread++)  
		pthread_create(&thread_handles[thread], NULL,
			 Hello, (void*) thread);  

	//printf("Hello from the main thread\n");

	for (thread = 0; thread < thread_count; thread++) 
		pthread_join(thread_handles[thread], NULL); 

	 
	free(thread_handles);
	
	gettimeofday(&stop_time, NULL);	
	exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));
	
	//print the data
	printf("\nVector addition output: \n");
	for(i=0;i<VECTORSIZE;i++)
	{
		printf("\t%d", C[i]);	
	}
	printf("\n Execution time is = %lf seconds\n", exe_time);
	
	printf("\nProgram exit!\n");
	
	//Free arrays
	free(A); 
	free(B);
	free(C);
	
	return 0;
}  /* main */

int check_prime(int i)
{
	 int j, flag1;
	flag1 = 1;
	for(j=2;j<i;j++)	
	{
		 if((i%j) == 0)
		{
			 flag1 = 0;
			  break;
		 }
	 }
	return flag1;
}

/*-------------------------------------------------------------------*/
void *Hello(void* rank) {
	long my_rank = (long) rank;  /* Use long in case of 64-bit system */ 
	int i,j;
	int count; 
	int start, end;
	int sum,work_per_thd;
	work_per_thd = VECTORSIZE/thread_count;
    start = my_rank*work_per_thd;
    end = start + work_per_thd;
	
	for(i=start;i<end;i++)
	{
		sum = 0;
		for(j=0;j<VECTORSIZE;j++)
		{
			sum = sum + A[i*VECTORSIZE+j]*B[j];	
		}
		C[i] =  sum;
	}
	 
	return NULL;
}  /* Hello */


