#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(int argc, char* argv[])
{
    omp_set_num_threads(3);
    int val = 0;
    #pragma omp parallel default(shared)
    {
        if(omp_get_thread_num() == 0)
        {
            printf("Thread 0 sets the value of \"val\" to 123.\n");
            val = 123;
        }
        #pragma omp barrier
        if(omp_get_thread_num() == 1)
        {
            printf("Thread 1 reads the value of \"val\": %d.\n", val);
        }
    }
    return 0;
}

