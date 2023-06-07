#include"stdio.h"
#include"mpi.h"

int main(int argc, char **argv)
{
	int myid, size;
	int i,j;
	int values[16] = {12,9,27,39,93,45,14,78,23,86,56,43,94,67,77,88}; 
	int max, val[2], recv_val[2];
	 
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	val[0] = values[myid];
	val[1] = myid;
	for(i=size;i>0;i=i/2)
	{
	    j = i/2;
	    if(myid < i)
	    {
	        if(myid<j)
	        {
	            MPI_Recv(recv_val, 2, MPI_INT, myid+j, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	            if(val[0] < recv_val[0])
	            {
	                val[0] = recv_val[0];
	                val[1] = recv_val[1];
	            }
	        }
	        else
	        {
	            MPI_Send(val, 2, MPI_INT, myid-j, 0, MPI_COMM_WORLD);
	        }
	    }
	}
	MPI_Finalize();
	//If root
	if(myid==0)
	{
	    
	    printf("\n Max Value = %d and myid of max value = %d ",val[0], val[1]);
	}
}
