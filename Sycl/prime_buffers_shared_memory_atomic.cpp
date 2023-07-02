#include <CL/sycl.hpp>
constexpr int N=10240;
constexpr int M=256;
using namespace sycl;
int main() {
	std::vector<int> a(N);
	int total_primes = 1;
	for(int i = 0;i<N;i++)
	{
	 a[i]=0;
	}
	{
	  buffer flag_buf(a);
	  queue q;
	  
	  q.submit([&](handler& h) {
	    accessor flag_global(flag_buf, h, write_only);
	    h.parallel_for(nd_range<1>{N, M}, [=](nd_item<1> item){
		 
		    int myid = item.get_global_id(0);	
	      
	        int i,j,flag;
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
	            flag_global[myid] = flag;
            }		 
	    });
	  }).wait();
	  
	  q.submit([&](handler& h) {
	    accessor flag(flag_buf, h, read_write);
	    local_accessor<int> flag_local(M, h);
	    h.parallel_for(nd_range<1>{N, M}, [=](nd_item<1> item){
		 
		    int myid = item.get_global_id(0);	
	        int local_id = item.get_local_id(0);
	        
	        int range = M/2;
	        flag_local[local_id] = 0;
            if(myid<N)
            {
                flag_local[local_id] = flag[myid];
                group_barrier(item.get_group());
                while(range>0)
                {
                    if(local_id < range)
                    {
                        flag_local[local_id] += flag_local[local_id + range];
                    }
                    range = range /2;
                    group_barrier(item.get_group()); 
                }
                if(local_id == 0)
                {
                    auto sum_atomic = atomic_ref<int, memory_order::relaxed, memory_scope::device, access::address_space::global_space>(flag[0]);
                    sum_atomic += flag_local[local_id]; 
                }
            }	 
	    });
	  }).wait();
	}
	
	 total_primes += a[0];
    
     std::cout << " Total number of primes = " << total_primes << std::endl;  
}
