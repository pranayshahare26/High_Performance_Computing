#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<mpi.h>

#define VECTORSIZE 20000

int main(int argc, char **argv)
{
	int myid, size;
	int i, j, sum;
	int *A, *B, *C;		
	int *A_local, *C_local;
	double exe_time;
	struct timeval stop_time, start_time;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	if(myid == 0)
	{
	    //Allocate and initialize the arrays
	    A = (int *)malloc(VECTORSIZE*VECTORSIZE*sizeof(int));
	    B = (int *)malloc(VECTORSIZE*sizeof(int));
	    C = (int *)malloc(VECTORSIZE*sizeof(int));
	    
	    A_local = (int *)malloc(VECTORSIZE*VECTORSIZE/size*sizeof(int));
	    C_local = (int *)malloc(VECTORSIZE/size*sizeof(int));
	    //Initialize data to some value
	    for(i=0;i<VECTORSIZE;i++)
	    {
		    for(j=0;j<VECTORSIZE;j++)
		    {
			    A[i*VECTORSIZE+j] = 1;	
		    }
		    B[i] = 1;
	    }
	}
	else
	{
	    //Allocate and initialize the arrays
	    A_local = (int *)malloc(VECTORSIZE*VECTORSIZE/size*sizeof(int));
	    B = (int *)malloc(VECTORSIZE*sizeof(int));
	    C_local = (int *)malloc(VECTORSIZE/size*sizeof(int));
	}
	if(myid == 0)
	{
	    //print the data
	    /*printf("\nInitial data: \n");
	    printf("\nMatrix: \n");
	    for(i=0;i<VECTORSIZE;i++)
	    {
		    for(j=0;j<VECTORSIZE;j++)
		    {
			    printf("\t%d ", A[i*VECTORSIZE+j]);	
		    }
		    printf("\n");
	    }
	    printf("\nVector: \n");
	    for(i=0;i<VECTORSIZE;i++)
	    {
		    printf("\t%d", B[i]);
	    }*/
	    gettimeofday(&start_time, NULL);
	}
	
	MPI_Scatter(A, VECTORSIZE*VECTORSIZE/size, MPI_INT, A_local, VECTORSIZE*VECTORSIZE/size, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(B, VECTORSIZE, MPI_INT, 0, MPI_COMM_WORLD);
	
	for(i=0;i<VECTORSIZE/size;i++)
	{
		sum = 0;
		for(j=0;j<VECTORSIZE;j++)
		{
			sum = sum + A_local[i*VECTORSIZE+j]*B[j];	
		}
		C_local[i] =  sum;
	}
	
	MPI_Gather(C_local, VECTORSIZE/size, MPI_INT, C, VECTORSIZE/size, MPI_INT, 0, MPI_COMM_WORLD);
	
	MPI_Finalize();
	
	if(myid == 0)
	{
	    gettimeofday(&stop_time, NULL);	
	    exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));
	    
	    //print the data
	    /*printf("\nVector addition output: \n");
	    for(i=0;i<VECTORSIZE;i++)
	    {
		    printf("\t%d", C[i]);	
	    }*/
	    printf("\n Execution time is = %lf seconds\n", exe_time);
	    printf("\nProgram exit!\n");
	
	    //Free arrays
	    free(A); 
	    free(B);
	    free(C);
	    free(A_local);
	    free(C_local);
	}
	else
	{
	    //Free arrays
	    free(A_local); 
	    free(B);
	    free(C_local);
	}
}
