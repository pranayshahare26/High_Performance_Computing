#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define N 5
int main()
{
    int i;
    float a[N], b[N], c[N], d[N], e[N];

    for (i = 0; i< N; i++) 
    {
        a[i] = i * 1.5;
        b[i] = i+ 22.35;
    }

    #pragma omp parallel shared(a,b,c,d,e) private(i)
    {
        #pragma omp sections nowait
        {
            #pragma omp section
            for (i=0; i < N; i++)
            {
                c[i] = a[i] + b[i];
                printf("section 1 # working thread : %d | %f + %f =%f\n", omp_get_thread_num(), a[i], b[i], c[i]);
            }
            #pragma omp section
            for(i =0; i< N; i++)
            {
                d [i] = a[i] * b[i];
                printf("section 2 # working thread : %d| %f * %f = %f\n", omp_get_thread_num(), a[i],b[i], d[i]);
            }
        }
    }
}
