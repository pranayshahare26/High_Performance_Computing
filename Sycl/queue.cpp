#include <CL/sycl.hpp>
constexpr int N=16;

int main() {
  sycl::queue q(gpu_selector_v);
  //sycl::queue q(cpu_selector_v);
  //sycl::queue q(accelerator_selector_v);
  //sycl::queue q(default_selector_v);
  //sycl::queue q;
  
  sycl::device my_device = q.get_device();
  std::cout << "Device: " << my_device.get_info<sycl::info::device::name>() << std::endl;
  
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
