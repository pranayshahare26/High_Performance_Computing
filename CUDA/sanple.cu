#include <cuda.h>
#include <stdio.h>
// __global__ void matrixAddition(float* A, const float* B, const float* C, int size) 
// {
//     int idx = blockIdx.x * blockDim.x + threadIdx.x;
//     int idy = blockIdx.y * blockDim.y + threadIdx.y;
//     if (idx < size && idy < size) 
//     {
//         int index = idy * size + idx;
//         A[index] = B[index] + C[index];
//     }
// }
// // Kernel-Each thread produces one output matrix element
// __global__ void matrixAddition(float* A, const float* B, const float* C, int size) 
// {
//     int idx = blockIdx.x * blockDim.x + threadIdx.x;
//     int idy = blockIdx.y * blockDim.y + threadIdx.y;
//     if (idx < size && idy < size) 
//     {
//         int index = idy * size + idx;
//         A[index] = B[index] + C[index];
//     }
// }

// // Kernal-Each thread produces one output matrix row
// __global__ void matrixAddition(float* A, const float* B, const float* C, int size) 
// {
//     int idy = blockIdx.y * blockDim.y + threadIdx.y;
//     if (idy < size) 
//     {
//         for (int idx = 0; idx < size; idx++) 
//         {
//             int index = idy * size + idx;
//             A[index] = B[index] + C[index];
//         }
//     }
// }

// Kernel-Each thread produces one output matrix column
__global__ void matrixAddition(float* A, const float* B, const float* C, int size) 
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < size) 
    {
        for (int idy = 0; idy < size; idy++) 
        {
            int index = idy * size + idx;
            A[index] = B[index] + C[index];
        }
    }
}

void matrixAdditionHost(float* A, const float* B, const float* C, int size) 
{
    float* d_A, *d_B, *d_C;
    int matrixSize = size * size * sizeof(float);
    cudaMalloc((void**)&d_A, matrixSize);
    cudaMalloc((void**)&d_B, matrixSize);
    cudaMalloc((void**)&d_C, matrixSize);
    cudaMemcpy(d_B, B, matrixSize, cudaMemcpyHostToDevice);
    cudaMemcpy(d_C, C, matrixSize, cudaMemcpyHostToDevice);
    dim3 blockSize(16, 16);
    dim3 gridSize((size + blockSize.x - 1) / blockSize.x, (size + blockSize.y - 1) / blockSize.y);
    matrixAddition<<<gridSize, blockSize>>>(d_A, d_B, d_C, size);
    cudaMemcpy(A, d_A, matrixSize, cudaMemcpyDeviceToHost);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
}
int main() 
{
    int size = 4;
    float* A = new float[size * size];
    float* B = new float[size * size];
    float* C = new float[size * size];
     // Initialize B and C matrices
     matrixAdditionHost(A, B, C, size);
     // Print the resulting matrix A
    delete[] A;
    delete[] B;
    delete[] C;
    return 0;
}