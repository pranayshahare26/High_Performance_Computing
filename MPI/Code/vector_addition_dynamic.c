#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define ARRSIZE 20

main(int argc, char **argv)
{
	int myid, size;
	int i;
	int *A, *B, *C;
	int *A_sub, *B_sub, *C_sub;	
	int elements_per_process;	
	
	//Initialize MPI environment 
	MPI_Init(&argc,&argv);
	
	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	//Get my unique identification among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	//Exit the code if the number of processes is not equal to 4
	if(size!=4)
	{
		printf("\nNumber of processes should be 4! Exiting now!\n");
		MPI_Finalize();
		return;
	}
	
	elements_per_process = ARRSIZE/size;
	
	//If root allocate and initialize the arrays
	if(myid==0)
	{
		printf("\nElements per process = %d",elements_per_process);
		
		A = (int *)malloc(ARRSIZE*sizeof(int));
		B = (int *)malloc(ARRSIZE*sizeof(int));
		C = (int *)malloc(ARRSIZE*sizeof(int));
		
		//Initialize data to some value
		for(i=0;i<ARRSIZE;i++)
		{
			A[i] = i;
			B[i] = i;			
		}
		
		//print the data
		printf("\nInitial data: \n");
		for(i=0;i<ARRSIZE;i++)
		{
			printf("\t%d \t %d\n", A[i], B[i]);			
		}
	}	
	
	//Allocate memory for temorary arrays
	A_sub = (int *)malloc(elements_per_process*sizeof(int));
	B_sub = (int *)malloc(elements_per_process*sizeof(int));
	C_sub = (int *)malloc(elements_per_process*sizeof(int));
	
	//Distribute / Scatter the data from root = 0
	MPI_Scatter(A, elements_per_process, MPI_INT, A_sub, elements_per_process, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(B, elements_per_process, MPI_INT, B_sub, elements_per_process, MPI_INT, 0, MPI_COMM_WORLD);
	
	//Every process adds sub arrays
	for(i=0;i<elements_per_process;i++)
	{
		C_sub[i] = A_sub[i] + B_sub[i];
	}
	
	//Gather the data 
	MPI_Gather(C_sub, elements_per_process, MPI_INT, C, elements_per_process, MPI_INT, 0, MPI_COMM_WORLD);
	
	//If root
	if(myid==0)
	{
		//print the data
		printf("\nVector addition output: \n");
		for(i=0;i<ARRSIZE;i++)
		{
			printf("\t%d\n", C[i]);			
		}
		printf("\nProgram exit!\n");
	
		//Free arrays
		free(A); 
		free(B);
		free(C);
	}
		
	//Free temporary allocated memory
	free(A_sub);
	free(B_sub);
	free(C_sub);
	
	//End MPI environment        
	MPI_Finalize();
}
