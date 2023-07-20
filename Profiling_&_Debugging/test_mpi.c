#include<stdio.h>
#include<mpi.h>

void do_something(int rank)
{
	long long sum = 0;
	for(long long i=0; i<1000 * ((rank%3) + 1); i++)
		for(long long j=0; j<1000; j++)
			sum += i + j * rank;
}
int main(int argc, char *argv[])
{
	int rank, size, hostname_len;
	char hostname[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Get_processor_name(hostname, &hostname_len);

	printf("Hello from process %d of %d on host %s\n", rank, size, hostname);
	do_something(rank);
	MPI_Finalize();
	return 0;
}