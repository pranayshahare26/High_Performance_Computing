#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#define VECTORSIZE 10000
void matrix_vec_mul(int *A, int *B, int *C)
{
    int i, j, sum;
    for(i=0;i<VECTORSIZE;i++)
    {
        sum = 0;
        for(j=0;j<VECTORSIZE;j++)
        {
            sum = sum + A[i*VECTORSIZE+j]*B[j];    
        }
        C[i] =  sum;
    }
}
int main(int argc, char **argv)
{
    int i, j;
    int *A, *B, *C;     
    double exe_time;
    struct timeval stop_time, start_time;
     //Allocate and initialize the arrays
    A = (int *)malloc(VECTORSIZE*VECTORSIZE*sizeof(int));
    B = (int *)malloc(VECTORSIZE*sizeof(int));
    C = (int *)malloc(VECTORSIZE*sizeof(int));
     //Initialize data to some value
    for(i=0;i<VECTORSIZE;i++)
    {
        for(j=0;j<VECTORSIZE;j++)
        {
            A[i*VECTORSIZE+j] = 1;    
        }
        B[i] = 1;
    }
     //print the data
    /*printf("\nInitial data: \n");
    for(i=0;i<VECTORSIZE;i++)
    {
        for(j=0;j<VECTORSIZE;j++)
        {
            printf("\t%d ", A[i*VECTORSIZE+j]);    
        }
        printf("\n");
    }
    printf("\n");
    for(i=0;i<VECTORSIZE;i++)
    {
        printf("\t%d", B[i]);
    }*/    
    gettimeofday(&start_time, NULL);
    matrix_vec_mul(A, B, C);
    gettimeofday(&stop_time, NULL);    
    exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));
     //print the data
    /*printf("\n Matrix-Vector Multiplication output: \n");
    for(i=0;i<VECTORSIZE;i++)
    {
        printf("\t%d", C[i]);    
    }*/
    printf("\nExecution time is = %lf seconds\n", exe_time);
    printf("\nProgram exit!\n");
     //Free arrays
    free(A); 
    free(B);
    free(C);
}

/*

The following code performs matrix-vector multiplication. It defines a function  `matrix_vec_mul`  that takes three integer arrays  `A` ,  `B` , and  `C`  as input. The function multiplies matrix  `A`  with vector  `B`  and stores the result in vector  `C` . 
 The main function starts by declaring variables and allocating memory for arrays  `A` ,  `B` , and  `C` . It then initializes the data in arrays  `A`  and  `B`  with the value 1. 
 Next, the code measures the execution time of the  `matrix_vec_mul`  function using the  `gettimeofday`  function. It calls the  `matrix_vec_mul`  function and passes the arrays  `A` ,  `B` , and  `C`  as arguments. After the function completes, it measures the stop time and calculates the execution time. 
 Finally, the code prints the execution time and frees the allocated memory for arrays  `A` ,  `B` , and  `C` .
 Step-wise explanation of the code:
1. The code includes necessary header files:  `stdio.h` ,  `stdlib.h` , and  `sys/time.h` .
2. It defines a constant  `VECTORSIZE`  as 10000.
3. It defines the function  `matrix_vec_mul`  that takes three integer arrays  `A` ,  `B` , and  `C`  as input.
4. Inside the  `matrix_vec_mul`  function, it initializes variables  `i` ,  `j` , and  `sum` .
5. It uses nested loops to perform matrix-vector multiplication. The outer loop iterates over each row of matrix  `A` , and the inner loop iterates over each element of vector  `B` .
6. Inside the inner loop, it multiplies each element of matrix  `A`  with the corresponding element of vector  `B`  and adds it to the  `sum`  variable.
7. After the inner loop completes, it assigns the value of  `sum`  to the corresponding element of vector  `C` .
8. The main function starts by declaring variables  `i` ,  `j` , and  `sum` .
9. It declares three integer pointers  `A` ,  `B` , and  `C` .
10. It declares variables  `exe_time` ,  `start_time` , and  `stop_time`  of types  `double`  and  `struct timeval` .
11. It allocates memory for arrays  `A` ,  `B` , and  `C`  using the  `malloc`  function.
12. It initializes the data in arrays  `A`  and  `B`  with the value 1 using nested loops.
13. It measures the start time using the  `gettimeofday`  function.
14. It calls the  `matrix_vec_mul`  function and passes arrays  `A` ,  `B` , and  `C`  as arguments.
15. It measures the stop time using the  `gettimeofday`  function.
16. It calculates the execution time by subtracting the start time from the stop time and stores it in the  `exe_time`  variable.
17. It prints the execution time.
18. It frees the allocated memory for arrays  `A` ,  `B` , and  `C`  using the  `free`  function.

*/