#include <omp.h>
#include <stdio.h>
int main (int argc, char *argv[]){
printf("First parallel region\n");
#pragma omp parallel if(omp_in_parallel) num_threads(8)
    {
        printf("The threads is %d\n",omp_get_thread_num());
    }
printf("second parallel region\n");
#pragma omp parallel if(omp_in_parallel) num_threads(4)
    {
        printf("The threads is %d\n",omp_get_thread_num());
    }

return 0;
}
