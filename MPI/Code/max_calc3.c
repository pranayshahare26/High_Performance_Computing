#include"stdio.h"
#include"mpi.h"

int main(int argc, char **argv)
{
	int myid, size;
	int i,j;
	int values[16] = {12,9,27,39,93,45,14,78,23,86,56,43,94,67,77,88}; 
	int max, val, recv_val;
	MPI_Status status;
	 
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	val = values[myid];
	for(i=size;i>0;i=i/2)
	{
	    j = i/2;
	    if(myid < i)
	    {
	        if(myid<j)
	        {
	            MPI_Recv(&recv_val,1, MPI_INT, myid+j, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	            if(val < recv_val)
	            {
	                val = recv_val;
	            }
	        }
	        else
	        {
	            MPI_Send(&val, 1, MPI_INT, myid-j, 0, MPI_COMM_WORLD);
	        }
	    }
	}
	if(myid==0)
	{
	    for(i=1;i<size;i++)
	    {
	        MPI_Send(&val, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
	    }
	    MPI_Recv(&recv_val,1, MPI_INT, MPI_ANY_SOURCE, 10, MPI_COMM_WORLD, &status);
	    printf("\n Max Value = %d and is available with myid = %d\n",val,status.MPI_SOURCE);
	}
	else
	{
	    MPI_Recv(&recv_val,1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	    if(recv_val == values[myid])
	    {
	        MPI_Send(&myid, 1, MPI_INT, 0, 10, MPI_COMM_WORLD);
	    }        
	}
	MPI_Finalize();
}
