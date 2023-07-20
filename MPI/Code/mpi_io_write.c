#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int nints, size, myid, count;
    MPI_Status status;
    MPI_File fh;
    MPI_Offset offset;
    int max = 0, global_max;
    int buf[1000];
    
    for(int i =0;i<1000;i++)
    {
        buf[i] = rand()%1000;
    }
    
    MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
    MPI_File_open(MPI_COMM_WORLD, "test_input.dat", MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);
    if (myid == 0)
        MPI_File_write(fh, buf, 1000, MPI_INT, MPI_STATUS_IGNORE);
        printf("\n The global_max = %d \n", global_max);
    MPI_File_close(&fh);
    MPI_Finalize();
}