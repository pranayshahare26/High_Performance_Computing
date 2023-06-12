#include <omp.h>
#include <stdio.h>
int main (){
#pragma omp parallel if(omp_in_parallel)
{
    printf("The threads is %d\n",omp_get_thread_num());
}
return 0;
}
