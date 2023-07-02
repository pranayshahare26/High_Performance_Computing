_kernel void vecAdd(_global double* A, __global double* B, __global double* C, double alpha)
{
    int gid = get_global_id(0);
    alpha = 0.001;

    C[gid] = A[gid] + alpha*B[gid];
}
