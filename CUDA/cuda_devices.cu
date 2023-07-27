#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

int main() 
{
	int deviceCount;
	cudaGetDeviceCount(&deviceCount);
	if (deviceCount == 0)
	{
	    printf("There is no device supporting CUDA\n");
	}
	int dev;
	for (dev = 0; dev < deviceCount; ++dev) 
	{
	    cudaDeviceProp deviceProp;
	    cudaGetDeviceProperties(&deviceProp, dev);
	    if (dev == 0) 
	    {
		    if (deviceProp.major < 1)
	        {	
				    printf("There is no device supporting CUDA.\n");
		    }
		    else if (deviceCount == 1)
		    {
		        printf("There is 1 device supporting CUDA\n");
		    }
		    else
	        {
				    printf("There are %d devices supporting CUDA\n", deviceCount);
		    }
	    }
	    printf("\nDevice %d: \"%s\"\n", dev, deviceProp.name);
	    printf("Major revision number:                         %d\n", deviceProp.major);
	    printf("Minor revision number:                         %d\n", deviceProp.minor);
	    printf("Total amount of global memory:                 %ld bytes\n", deviceProp.totalGlobalMem);
	    printf("Total amount of constant memory:               %ld bytes\n", deviceProp.totalConstMem); 
	    printf("Total amount of shared memory per block:       %ld bytes\n", deviceProp.sharedMemPerBlock);
	    printf("Total number of registers available per block: %d\n", deviceProp.regsPerBlock);
	    printf("Warp size:                                     %d\n", deviceProp.warpSize);
		printf("Multiprocessor count:                          %d\n",deviceProp.multiProcessorCount );
	    printf("Maximum number of threads per block:           %d\n", deviceProp.maxThreadsPerBlock);
	    printf("Maximum sizes of each dimension of a block:    %d x %d x %d\n", deviceProp.maxThreadsDim[0],deviceProp.maxThreadsDim[1], deviceProp.maxThreadsDim[2]);
	    printf("Maximum sizes of each dimension of a grid:     %d x %d x %d\n", deviceProp.maxGridSize[0], deviceProp.maxGridSize[1],  deviceProp.maxGridSize[2]);
	    printf("Maximum memory pitch:                          %ld bytes\n", deviceProp.memPitch);
	    printf("Texture alignment:                             %ld bytes\n", deviceProp.textureAlignment);
	    printf("Clock rate:                                    %d kilohertz\n", deviceProp.clockRate);
	} 
}

/*

This code is used to retrieve information about the CUDA-enabled devices available on the system. 
It first calls the function  `cudaGetDeviceCount`  to get the number of CUDA devices available.
If the number of devices is 0, it prints a message indicating that there are no devices supporting CUDA. 
Next, it enters a loop to iterate over each device. Inside the loop, it calls  `cudaGetDeviceProperties`  to retrieve the properties of each device.
It then prints various information about each device, such as the device name, major and minor revision numbers, total global memory, total constant memory, shared memory per block, number of registers per block, warp size, multiprocessor count, maximum number of threads per block, maximum sizes of each dimension of a block and grid, maximum memory pitch, texture alignment, and clock rate.
The loop continues until all devices have been processed, and the program exits.

*/