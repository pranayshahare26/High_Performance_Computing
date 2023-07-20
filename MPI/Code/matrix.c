#include <stdio.h>
#include <mpi.h>
#define ROWS 3
#define COLS 3
int main(int argc, char *argv[]) 
{
    int rank, size;
    int matrix1[ROWS][COLS] = {{1,2,3}, {4,5,6}, {7,8,9}};
    int matrix2[ROWS][COLS] = {{9,8,7}, {6,5,4}, {3,2,1}};
    int result[ROWS][COLS];
    int i, j;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    // Distribute matrix1 and matrix2 to all processes
    MPI_Bcast(matrix1, ROWS * COLS, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(matrix2, ROWS * COLS, MPI_INT, 0, MPI_COMM_WORLD);
    // Compute local result by adding local rows of matrix1 and matrix2
    for (i = rank; i < ROWS; i += size) 
    {
        for (j = 0; j < COLS; j++) 
        {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    // Gather local results to result matrix in process 0
    MPI_Gather(result, ROWS * COLS / size, MPI_INT, result, ROWS * COLS / size, MPI_INT, 0, MPI_COMM_WORLD);
    // Print result matrix in process 0
    if (rank == 0) 
    {
        printf("Result matrix:\n");
        for (i = 0; i < ROWS; i++) 
        {
            for (j = 0; j < COLS; j++) 
            {
                printf("%d ", result[i][j]);
            }
            printf("\n");
        }
    }
    MPI_Finalize();
    return 0;
}