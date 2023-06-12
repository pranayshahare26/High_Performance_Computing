#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main(void)
{    
    int a = 100;

    #pragma omp parallel for
    for (int i = 0; i < 2; i++)
    {
        if (0 == omp_get_thread_num())
        {
            a++;
            #pragma omp flush
        }
        else
        {
            sleep(1);
            printf("a is %d\n", a);
        }
    }

    return 0;
}