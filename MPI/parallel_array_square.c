#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <mpi.h>
#define N 10
int main(int argc, char *argv[])
{
    int i, j, rank, size;
    int *A, *subA;
    double exe_time;
    struct timeval stop_time, start_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    A = (int *) malloc(N*sizeof(int));
    subA = (int *) malloc(N/size);

    if (rank == 0) 
    {
        for(i=0;i<N;i++)
        {
            A[i] = i;
        }
        printf("\n Initial Array :\n");
        for(i=0;i<N;i++)
        {
            printf(" %d", A[i]);
        }
    }

    MPI_Scatter(A, N/size, MPI_INT, subA, N/size, MPI_INT, 0, MPI_COMM_WORLD);
    gettimeofday(&start_time, NULL);
    for(i=0;i<N/size;i++)
    {
        subA[i] = subA[i]*subA[i];
    }
    
    MPI_Gather(subA, N/size, MPI_INT, A, N/size, MPI_INT, 0, MPI_COMM_WORLD);
    gettimeofday(&stop_time, NULL);    
    exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));

    if (rank == 0) 
    {
        printf("\n Final Array :\n");
        for(i=0;i<N;i++)
        {
            printf(" %d", A[i]);
        }
        printf("\n");
        free(A);
    }
    free(subA);
    MPI_Finalize();
    return 0;
}