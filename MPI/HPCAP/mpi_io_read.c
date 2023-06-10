#include <stdio.h>
#include<mpi.h>
int main(int argc, char *argv[])
{
    int nints, size, myid, count;
    MPI_Status status;
    MPI_File fh;
    MPI_Offset offset, filesize;
    int max = 0, global_max;
    int buf[1000];
    
    MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
    MPI_File_open(MPI_COMM_WORLD, "testfile", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
    MPI_File_get_size(fh,&filesize);
    nints = filesize / (size*sizeof(int));
    offset = myid*nints*sizeof(int);
    MPI_File_read_at(fh, offset, buf, nints, MPI_INT, &status);
    MPI_Get_count(&status, MPI_INT, &count);
    printf("process %d read %d ints\n", myid, count);
    fflush(0);
    MPI_File_close(&fh);
    
    MPI_Barrier(MPI_COMM_WORLD);
    
    for(int i = 0;i<nints;i++)
    {
        printf("%d \t", buf[i]);    
    }
    
    MPI_Finalize();
}
