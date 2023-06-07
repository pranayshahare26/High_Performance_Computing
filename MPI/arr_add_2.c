#include"stdio.h"
#include"mpi.h"

int main(int argc, char **argv){
	int myid, size;
	int a[10], b[10], c[10];
	int start, end, total_work_per_rank;

	//Initialize MPI environment
	MPI_Init(&argc, &argv);

	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//Get my unique identification among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	printf("%d\n", myid);
	for(int i=0; i<10; i++){
		a[i] = i + 1;
		b[i] = i + 1;
	}

	total_work_per_rank = 10 / size;
	start = myid*total_work_per_rank;
	end = start + total_work_per_rank;
	
	for(int i=start; i<end; i++){
		c[i] = a[i] + b[i];
	}

	for(int i=0; i<10; i++){
		printf("a[%d]=%d, b[%d]=%d, c[%d]=%d\n", i, a[i], i, b[i], i, c[i]);
	}

	//End MPI Environment
	MPI_Finalize();
}
