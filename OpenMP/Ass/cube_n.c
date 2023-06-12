#include <stdio.h>
#include <omp.h>
void main()
{
int i,ctr,num;
ctr = omp_get_num_threads();
#pragma omp parallel private(num)
for(i=1;i<=ctr;i++)
{
num = omp_get_thread_num();
printf("Number is : %d and cube of the %d is :%d \n",num,num, (num*num*num));
}
}
