#include<stdio.h>
#include<stdlib.h>
#include <pthread.h> 

#define N 900000000

int flag;
double sum;
/* Global variable:  accessible to all threads */
int thread_count;  

void *Hello(void* rank);  /* Thread function */

/*--------------------------------------------------------------------*/
int main() {
   long       thread;  /* Use long in case of a 64-bit system */
   pthread_t* thread_handles; 

   /* Get number of threads from command line */
   thread_count = 4; 
   flag = 0;
   sum = 0;
   thread_handles = malloc (thread_count*sizeof(pthread_t)); 

   for (thread = 0; thread < thread_count; thread++)  
      pthread_create(&thread_handles[thread], NULL,
          Hello, (void*) thread);  

   //printf("Hello from the main thread\n");

   for (thread = 0; thread < thread_count; thread++) 
      pthread_join(thread_handles[thread], NULL); 

    printf("\n pi = %lf",sum);

   free(thread_handles);
   return 0;
}  /* main */

/*-------------------------------------------------------------------*/
void *Hello(void* rank) {
   long my_rank = (long) rank;  /* Use long in case of 64-bit system */ 
   double step;
   int i;
   int start, end;
   int work_per_thd;
   double x, pi, tmp_sum;
    tmp_sum = 0.0;
    step = 1.0/(double)N;
    
    work_per_thd = N/thread_count;
    start = my_rank*work_per_thd;
    end = start + work_per_thd;
    
    for(i=start; i<end; i++)
    {
        x = (i)*step;
        tmp_sum = tmp_sum + 4.0/(1.0+x*x);
    }
   tmp_sum = step*tmp_sum;
   
   while(flag != my_rank) {};   
   sum += tmp_sum;
   flag++;
    
   return NULL;
}  /* Hello */


