#include <stdio.h>
#include<mpi.h>
int main(int argc, char *argv[])
{
    int nints, size, myid, count;
    MPI_Status status;
    MPI_File fh;
    MPI_Offset offset;
    int max = 0, global_max;
    int buf[1000];
    
    MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
    MPI_File_open(MPI_COMM_WORLD, "test_input.dat", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
    nints = 1000 / (size);
    offset = myid*nints*sizeof(int);
    MPI_File_read_at(fh, offset, buf, nints, MPI_INT, &status);
    MPI_Get_count(&status, MPI_INT, &count);
    printf("process %d read %d ints\n", myid, count);
    MPI_File_close(&fh);
    
    for(int i = 0;i<nints;i++)
    {
        if(max < buf[i])
        {
            max = buf[i];
        }
    }
    
    MPI_Reduce(&max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    if(myid==0)
    {
        printf("\n The global_max = %d \n", global_max);
    }
    MPI_Finalize();
}
