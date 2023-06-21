__kernel void prime_calc(__global int *sum, int N)
{
        int myid = get_global_id(0);
        int i,j, flag;
        flag = 1;
        i = myid;
        if((myid<N) && (myid>2))
        {
                for(j=2;j<i;j++)
            {
                    if((i%j) == 0)
                    {
                            flag = 0;
                            break;
                    }
            }
            sum[myid] = flag;
    }
}