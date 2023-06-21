#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 

const int MAX_THREADS = 64;
/* Global variables: accessible to all threads */
int thread_count;  
int sum = 0; /* store the sum of numbers */
void *Sum(void* rank);  /* Thread function */
/*--------------------------------------------------------------------*/
int main() 
{
   long thread;  /* Use long in case of a 64-bit system */
   pthread_t* thread_handles; 
    /* Get number of threads from command line */
    thread_count = 4; 
    thread_handles = malloc (thread_count*sizeof(pthread_t)); 
    for (thread = 0; thread < thread_count; thread++)  
        pthread_create(&thread_handles[thread], NULL,
            Sum, (void*) thread);  
    printf("Hello from the main thread\n");
    for (thread = 0; thread < thread_count; thread++) 
        pthread_join(thread_handles[thread], NULL); 
    /* Calculate the sum in the main thread */
    int i;
    for (i = 1; i <= 1000; i++)
        sum += i;
    printf("The sum of numbers from 1 to 1000 is %d\n", sum);
    free(thread_handles);
    return 0;
}  /* main */
 /*-------------------------------------------------------------------*/
void *Sum(void* rank) 
{
    long my_rank = (long) rank;  /* Use long in case of 64-bit system */ 
    int i;
    int local_sum = 0;
    int start = my_rank * 250 + 1;
    int end = start + 249;
    /* Calculate the sum for this thread */
    for (i = start; i <= end; i++)
        local_sum += i;
    printf("Thread %ld calculated the sum from %d to %d: %d\n", my_rank, start, end, local_sum);
    /* Add the local sum to the global sum */
    sum += local_sum;
    return NULL;
}  /* Sum */