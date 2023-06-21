#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#define ARRAY_SIZE 400
int main()
{
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_context context = NULL;
    cl_command_queue command_queue = NULL;
    cl_program program = NULL;
    cl_kernel kernel = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret;
    double a[ARRAY_SIZE], b[ARRAY_SIZE], c[ARRAY_SIZE], alpha;
    alpha = 0.001;
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        a[i] = i;
        b[i] = i;
        c[i] = 0;
    }

    // Get platform and device info
    ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);

    // Create context and command queue
    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
    command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

    // Create buffer objects
    cl_mem a_buf = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(double) * ARRAY_SIZE, NULL, &ret);
    cl_mem b_buf = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(double) * ARRAY_SIZE, NULL, &ret);
    cl_mem c_buf = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(double) * ARRAY_SIZE, NULL, &ret);

    // Copy input data to buffer objects
    ret = clEnqueueWriteBuffer(command_queue, a_buf, CL_TRUE, 0, sizeof(double) * ARRAY_SIZE, a, 0, NULL, NULL);
    ret = clEnqueueWriteBuffer(command_queue, b_buf, CL_TRUE, 0, sizeof(double) * ARRAY_SIZE, b, 0, NULL, NULL);

    // Load kernel source code from file
    const char* kernel_str =
        "__kernel void vector_add(__global const double* a, __global const double* b, __global double* c, double alpha)\n"
        "{\n"
        "    int i = get_global_id(0);\n"
        "    c[i] = a[i] + alpha * b[i];\n"
        "}\n";

    // Create program object from kernel source code
    program = clCreateProgramWithSource(context, 1, &kernel_str, NULL, &ret);

    // Build program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    // Create kernel object
    kernel = clCreateKernel(program, "vector_add", &ret);

    // Set kernel arguments
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&a_buf);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&b_buf);
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&c_buf);
    ret = clSetKernelArg(kernel, 3, sizeof(double), (void*)&alpha);

    // Execute kernel
    size_t global_work_size = ARRAY_SIZE;
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);

    // Copy output data back to host
    ret = clEnqueueReadBuffer(command_queue, c_buf, CL_TRUE, 0, sizeof(double) * ARRAY_SIZE, c, 0, NULL, NULL);

    // Print output
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("\t%lf", c[i]);
    }
    printf("\n");

    // Release resources
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(a_buf);
    ret = clReleaseMemObject(b_buf);
    ret = clReleaseMemObject(c_buf);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    return 0;
}