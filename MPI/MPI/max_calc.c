#include"stdio.h"
#include"mpi.h"

int main(int argc, char **argv)
{
	int myid, size;
	int values[10] = {12,9,27,39,93,45,14,78,23,86}; 
	int max, val, i;
	 
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	//If root
	if(myid==0)
	{
	    max = values[myid];
	    for(i=1;i<size;i++)
	    {
		    MPI_Recv(&val, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		    if(val > max)
		    {
		        max = val;
		    }
	    }
	    printf("\n Max Value = %d ",max);
	}
	else
	{
	    val = values[myid];
		MPI_Send(&val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
}
