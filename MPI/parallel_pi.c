#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
 #define N 1000000000
 int main(int argc, char *argv[]) 
 {
    int rank, size, i;
    double step, x, pi, sum = 0.0, local_sum = 0.0;
 
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
 
    step = 1.0 / (double)N;
    for (i = rank; i < N; i += size) 
    {
        x = (i + 0.5) * step;
        local_sum += 4.0 / (1.0 + x * x);
    }
    MPI_Reduce(&local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) 
    {
        pi = step * sum;
        printf("Approximate Value of pi is %f.\n", pi);
    }
    MPI_Finalize();
return 0;
}
