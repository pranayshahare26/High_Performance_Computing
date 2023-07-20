#include"stdio.h"
#include"mpi.h"

int main(int argc, char **argv)
{
	int myid, size;
	int data_arr[2];
	MPI_Status status;

	//Initialize MPI environment
	MPI_Init(&argc, &argv);

	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//Get my unique identification among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	if(myid == 0)
	{
		data_arr[0] = 205;
		data_arr[1] = 408;

		//Print data to be sent
		printf("myid: %d\t data_arr[0] = %d\n", myid, data_arr[0]);
		printf("myid: %d\t data_arr[1] = %d\n", myid, data_arr[1]);

		//Send data
		MPI_Send(data_arr, 2, MPI_INT, 1, 0, MPI_COMM_WORLD);
		printf("Data sent\n");
	}
	if(myid == 1)
	{
		data_arr[0] = 10;
		data_arr[1] = 20;

		MPI_Recv(data_arr, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		printf("Data received\n");

		//Print received sent
		printf("myid: %d\t data_arr[0] = %d\n", myid, data_arr[0]);
		printf("myid: %d\t data_arr[1] = %d\n", myid, data_arr[1]);

		printf("Program exit!\n");
	}


	//End MPI Environment
	MPI_Finalize();
}
