#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<mpi.h>
#define VECTORSIZE 10
int main(int argc, char **argv)
{
    int rank, size;
    int i, j, k, sum;
    int *A, *B, *C, *a, *c;
    double exe_time;
    struct timeval stop_time, start_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int rows = VECTORSIZE / size;
    int remaining_rows = VECTORSIZE % size;
    int start_row = rank * rows;
    int end_row = start_row + rows;
    if (rank == size - 1) 
    {
        end_row += remaining_rows;
    }
     //Allocate and initialize the arrays
    A = (int *)malloc(VECTORSIZE*VECTORSIZE*sizeof(int));
    B = (int *)malloc(VECTORSIZE*VECTORSIZE*sizeof(int));
    C = (int *)malloc(VECTORSIZE*VECTORSIZE*sizeof(int));
    a = (int *)malloc(rows*VECTORSIZE*sizeof(int));
    c = (int *)malloc(rows*VECTORSIZE*sizeof(int));
    if (rank == 0) 
    {
        //Initialize data to some value
        for(i=0;i<VECTORSIZE;i++)
        {
            for(j=0;j<VECTORSIZE;j++)
            {
                A[i*VECTORSIZE+j] = 1;
                B[i*VECTORSIZE+j] = 2;
                C[i*VECTORSIZE+j] = 0;    
            }
        }
         //print the data
        printf("\nInitial data: \n");
        printf("\n A matrix:\n");
        for(i=0;i<VECTORSIZE;i++)
        {
            for(j=0;j<VECTORSIZE;j++)
            {
                printf("\t%d ", A[i*VECTORSIZE+j]);    
            }
            printf("\n");
        }
        printf("\n B matrix:\n");
        for(i=0;i<VECTORSIZE;i++)
        {
            for(j=0;j<VECTORSIZE;j++)
            {
                printf("\t%d ", B[i*VECTORSIZE+j]);    
            }
            printf("\n");
        }   
    }
    
    gettimeofday(&start_time, NULL);
    MPI_Scatter(A, rows*VECTORSIZE, MPI_INT, a, rows*VECTORSIZE, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(B, VECTORSIZE*VECTORSIZE, MPI_INT, 0, MPI_COMM_WORLD);
    
    for(i=0;i<rows;i++)
    {
        for(j=0;j<VECTORSIZE;j++)
        {
            sum = 0;
            for(k=0;k<VECTORSIZE;k++)
            {
                sum = sum + a[i*VECTORSIZE+k]*B[k*VECTORSIZE+j];    
            }
            c[i*VECTORSIZE+j] =  sum;
        }
    }
    MPI_Gather(c, rows*VECTORSIZE, MPI_INT, C, rows*VECTORSIZE, MPI_INT, 0, MPI_COMM_WORLD);
    gettimeofday(&stop_time, NULL);    
    exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));
    if (rank == 0) 
    {
        //print the data
        printf("\n C matrix:\n");
        for(i=0;i<VECTORSIZE;i++)
        {
            for(j=0;j<VECTORSIZE;j++)
            {
                printf("\t%d ", C[i*VECTORSIZE+j]);    
            }
            printf("\n");
        }
        printf("\n Execution time is = %lf seconds\n", exe_time);
        printf("\nProgram exit!\n");
    }
     //Free arrays
    free(A); 
    free(B);
    free(C);
    free(a);
    free(c);
    MPI_Finalize();
}