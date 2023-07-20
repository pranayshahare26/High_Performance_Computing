#include"stdio.h"
#include"mpi.h"

int main(int argc, char **argv)
{
	int myid, size;
	int a[10], b[10], c[10];
	int start, end;
	int chunk_size = 4;
	//Initialize MPI environment
	MPI_Init(&argc, &argv);
	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	//Get my unique identification among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	for(int i=0; i<10; i++)
	{
		a[i] = i + 1;
		b[i] = i + 1;
	}
	start = myid * chunk_size;
	end = start + chunk_size;
	for(;start<10;)
	{
		for (int j = start; j<end; j++)
		{
			if(j<10)
				c[j] = a[j] + b[j];
		}
		start += chunk_size * size;
		end = start + chunk_size;
	}
	for(int i=0; i<10; i++)
	{
		printf("a[%d]=%d, b[%d]=%d, c[%d]=%d\n", i, a[i], i, b[i], i, c[i]);
	}
	//End MPI Environment
	MPI_Finalize();
}