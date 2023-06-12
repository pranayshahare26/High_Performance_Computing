#include<stdio.h>
#include<stdlib.h>
#include <pthread.h> 

#define N 1000000

int flag;
int sum;
/* Global variable:  accessible to all threads */
int thread_count;  

void *Hello(void* rank);  /* Thread function */

/*--------------------------------------------------------------------*/
int main() {
   long       thread;  /* Use long in case of a 64-bit system */
   pthread_t* thread_handles; 

   /* Get number of threads from command line */
   thread_count = 15; 
   flag = 0;
   sum = 0;
   thread_handles = malloc (thread_count*sizeof(pthread_t)); 

   for (thread = 0; thread < thread_count; thread++)  
      pthread_create(&thread_handles[thread], NULL,
          Hello, (void*) thread);  

   //printf("Hello from the main thread\n");

   for (thread = 0; thread < thread_count; thread++) 
      pthread_join(thread_handles[thread], NULL); 

    printf("\n prime numbers = %d",(sum+1));

   free(thread_handles);
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
   int i;
   int start;
   int count; 
    count = 0;
    start = my_rank*2+3;
    
    for(i=start; i<N; i+=(2*thread_count))
    {
        count += check_prime(i);
        count += check_prime(i+1);
    }
   
   while(flag != my_rank) {};   
   sum += count;
   flag++;
   printf("\n count = %d", count);
    
   return NULL;
}  /* Hello */


