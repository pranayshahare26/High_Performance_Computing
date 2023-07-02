#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int cube = thread_id * thread_id * thread_id;

        printf("Thread ID: %d, Cube: %d\n", thread_id, cube);
    }

    return 0;
}

