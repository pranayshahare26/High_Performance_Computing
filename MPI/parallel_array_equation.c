#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sys/time.h>
#include<mpi.h>
#define N 10
int main(int argc, char *argv[])
{
    int i, j, rank, size, num;
    double *c, *x, *y, *sub_c, *sub_x, *sub_y;
    double a;
    double exe_time;
    struct timeval stop_time, start_time;
   
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    num = N / size;
    sub_c = (double *) malloc(num * sizeof(double));
    sub_x = (double *) malloc(num * sizeof(double));
    sub_y = (double *) malloc(num * sizeof(double));
    if (rank == 0) 
    {
        c = (double *) malloc(N * sizeof(double));
        x = (double *) malloc(N * sizeof(double));
        y = (double *) malloc(N * sizeof(double));
        a = 0.01;
        for (i = 0; i < N; i++) 
        {
            x[i] = i;
            y[i] = i;
            c[i] = 0;
        }
        printf("\n Initial Array :\n");
        for (i = 0; i < N; i++) 
        {
            printf("%lf,%lf\t", x[i], y[i]);
        }
    }
    
    MPI_Scatter(x, num, MPI_DOUBLE, sub_x, num, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(y, num, MPI_DOUBLE, sub_y, num, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    gettimeofday(&start_time, NULL);
    for (i = 0; i < num; i++) 
    {
        sub_c[i] = a * sub_x[i] + sub_y[i];
    }
    
    MPI_Gather(sub_c, num, MPI_DOUBLE, c, num, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    gettimeofday(&stop_time, NULL);
    exe_time = (stop_time.tv_sec + (stop_time.tv_usec / 1000000.0)) - (start_time.tv_sec + (start_time.tv_usec / 1000000.0));
    
    if (rank == 0) 
    {
        printf("\n Final Array :\n");
        for (i = 0; i < N; i++) 
        {
            printf(" %lf", c[i]);
        }
        printf("\n");
        free(c);
        free(x);
        free(y);
    }
    free(sub_c);
    free(sub_x);
    free(sub_y); 
    MPI_Finalize();
    return 0;
}