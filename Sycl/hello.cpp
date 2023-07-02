#include <CL/sycl.hpp>
constexpr int N=16;

int main() {
  sycl::queue q;
  
  int *data = sycl::malloc_shared<int>(N, q);
   
  q.parallel_for(N, [=](auto i) {
      data[i] = i; 
  }).wait();
  
  for (int i=0; i<N; i++) 
  {
    std::cout << data[i] << "\n";
  }
  sycl::free(data, q);
  return 0;
}
