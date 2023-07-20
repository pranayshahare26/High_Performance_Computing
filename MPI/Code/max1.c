#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#define ARRAY_SIZE 10
int main(int argc, char **argv) 
{
    int myid, size;
    int data_arr[ARRAY_SIZE];
    int arr_size;
    int sum = 0;
    int max_value;
    MPI_Status status;
    MPI_Request request;
     // Initialize MPI environment
    MPI_Init(&argc, &argv);
     // Get total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);
     // Get my unique identification among all processes
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
     // Seed random number generator
    srand(time(NULL) + myid);
     // Generate random array of integers
    for (int i = 0; i < ARRAY_SIZE; i++) 
    {
        data_arr[i] = rand() % 100;
    }
     // Generate random maximum value
    max_value = rand() % 100;
     // Calculate sum of all values in the array that are less than or equal to the maximum value
    int local_sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) 
    {
        if (data_arr[i] <= max_value) 
        {
            local_sum += data_arr[i];
        }
    }
     // Reduce local sums from all processes to get the global sum
    MPI_Reduce(&local_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
     // End MPI environment
    MPI_Finalize();
    if (myid == 0) 
    {
        printf("sum = %d\n", sum);
        printf("data_arr = [ ");
        for (int i = 0; i < ARRAY_SIZE; i++) 
        {
            printf("%d ", data_arr[i]);
        }
        printf("]\n");
        printf("max_value = %d\n", max_value);
    }
     return 0;
}