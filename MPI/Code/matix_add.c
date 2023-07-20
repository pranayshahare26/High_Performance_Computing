#include <stdio.h>
#include <mpi.h>
#define ARRAY_SIZE 3
#define NUM_PROCESSES 4

int main(int argc, char** argv) 
{
    int rank, size;
    int i, start, end;
    int array[ARRAY_SIZE];
    int result[ARRAY_SIZE];
    int chunk_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    chunk_size = ARRAY_SIZE / NUM_PROCESSES;

    // Calculate the start and end indices for this process
    start = rank * chunk_size;
    end = start + chunk_size - 1;

    // Adjust the end index for the last process
    if (rank == NUM_PROCESSES - 1) 
    {
        end = ARRAY_SIZE - 1;
    }

    // Initialize the array with values
    for (i = 0; i < ARRAY_SIZE; i++) 
    {
        array[i] = i + 1;
    }

    // Perform the matrix addition for the assigned portion
    for (i = start; i <= end; i++) 
    {
        result[i] = array[i] + array[i];
    }
    MPI_Allgather(MPI_IN_PLACE, 0, MPI_DATATYPE_NULL, result, chunk_size, MPI_INT, MPI_COMM_WORLD);
    if (rank == 0) 
    {
        printf("Matrix Addition Result:\n");
        for (i = 0; i < ARRAY_SIZE; i++) 
        {
            printf("%d ", result[i]);
        }
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}
