#include <stdio.h>
#include <omp.h>

#define SIZE 10

void matrix_multiply(int A[][SIZE], int B[][SIZE], int C[][SIZE])
{
    int i, j, k;

    #pragma omp parallel for private(i, j, k) shared(A, B, C)
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            C[i][j] = 0;
            for (k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main()
{
    int A[SIZE][SIZE];
    int B[SIZE][SIZE];
    int C[SIZE][SIZE];
    int i, j;

    // Initialize matrices A and B
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }

    // Perform matrix multiplication
    matrix_multiply(A, B, C);

    // Print the result matrix C
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}

