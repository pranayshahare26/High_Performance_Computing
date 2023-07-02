#include <CL/sycl.hpp>
#include <iostream>
#include <cmath>
#define N 10000
using namespace sycl;
using namespace std;
int main() {
    double area, pi;
    double dx, y, x;
    dx = 1.0 / N;
    x = 0.0;
    area = 0.0;
    queue q;
    buffer<double> area_buf(&area, 1);
    buffer<double> dx_buf(&dx, 1);
    buffer<double> x_buf(&x, 1);
    buffer<double> y_buf(&y, 1);
    q.submit([&](handler& h) {
        auto area_acc = area_buf.get_access<access::mode::write>(h);
        auto dx_acc = dx_buf.get_access<access::mode::read>(h);
        auto x_acc = x_buf.get_access<access::mode::read_write>(h);
        auto y_acc = y_buf.get_access<access::mode::read_write>(h);
        h.parallel_for<class pi_calc>(range<1>(N), nd_range<1>(range<1>(N), range<1>(64)), [=](nd_item<1> item) 
        {
            int i = item.get_global_id(0);
            x_acc[i] = i * dx_acc[0];
            y_acc[i] = sqrt(1 - x_acc[i] * x_acc[i]);
            item.barrier(access::fence_space::local_space);
            for (int stride = item.get_local_range()[0] / 2; stride > 0; stride /= 2) 
            {
                if (item.get_local_id()[0] < stride) 
                {
                    y_acc[i] += y_acc[i + stride];
                }
                item.barrier(access::fence_space::local_space);
            }
            if (item.get_local_id()[0] == 0) 
            {
                area_acc[0] += y_acc[i] * dx_acc[0];
            }
        });
    });
    pi = 4.0 * area;
    cout << "\nValue of pi is = " << pi << endl;
    return 0;
}