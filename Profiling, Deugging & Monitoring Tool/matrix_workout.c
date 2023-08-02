#include <stdio.h>
#include <math.h>
void do_add(int m, int n, double* A, double* B) 
{
	for (int i=0; i<m; i++) 
	{
		for (int j=0;j<n; j++) 
		{
			int idx = i*m + j;
			B[idx] += A[idx];
		}
	}
}
void do_mul(int m, int n, double* A, double* B) 
{
	for (int i=0; i<m; i++) 
	{
		for (int j=0;j<n; j++) 
		{
			int idx = i*m + j;
			B[idx] *= A[idx];
		}
	}
}
void do_div(int m, int n, double* A, double* B) 
{
	for (int i=0; i<m; i++) 
	{
		for (int j=0;j<n; j++) 
		{
			int idx = i*m + j;
			B[idx] /= A[idx];
		}
	}
}
void do_sqrt(int m, int n, double* A, double* B) 
{
	for (int i=0; i<m; i++) 
	{
		for (int j=0;j<n; j++) 
		{
			int idx = i*m + j;
			B[idx] += sqrt(A[idx]);
		}
	}
}
void do_pow(int m, int n, double* A, double* B) 
{
	for (int i=0; i<m; i++) 
	{
		for (int j=0;j<n; j++) 
		{
			int idx = i*m + j;
			B[idx] += pow(A[idx],0.17);
		}
	}
	do_add(m, n, A, B);
	do_add(m, n, A, B);
	do_div(m, n, A, B);
}
int main() 
{
	const int m = 1000, n = 1000, iter = 1000;
	double A[m*n], B[m*n];
	for (int i=0; i<m*n; i++) B[i] = 0.0;
	for (int i=0; i<m*n; i++) A[i] = 1.1;
	for (int i=0; i<iter; i++) 
	{
		do_add(m, n, A, B);
		do_mul(m, n, A, B);
		do_div(m, n, A, B);
		do_sqrt(m, n, A, B);
		do_pow(m, n, A, B);
	}
	printf("Done!\n");
}