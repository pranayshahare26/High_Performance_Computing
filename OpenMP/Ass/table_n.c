#include <stdio.h>
#include <omp.h>
void main()
{
   int j,n;
   printf("Input the number (Table to be calculated) : ");
   scanf("%d",&n);
   printf("\n");
   omp_set_num_threads(n);
   #pragma omp parallel
   for(j=1;j<=10;j++)
   {
     printf("%d X %d = %d \n",n,j,n*j);
   }
}
