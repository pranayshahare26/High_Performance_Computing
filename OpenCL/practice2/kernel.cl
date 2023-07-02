__kernel void vector_add(__global double* a, __global double* b, __global double* c, const double alpha, const int size)
{
    int i = get_global_id(0);
    if(i < ARRAY_SIZE)
    {
        c[i] = a[i] + alpha * b[i];
    }
}
