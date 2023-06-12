#include<stdio.h>
#include<omp.h>
#include <unistd.h>
int main()
{   
    double a,x[100],y[100];
    double t = 0.0;
    double tb, te;
    int num_devices = omp_get_num_devices();
    printf("Number of avaible devices %d\n",num_devices);
    tb = omp_get_wtime();
	#pragma omp target map(to:x[0:100]) map(tofrom:y[0:100]){
	if(omp_is_initial_device()) {
	  printf("Running on host\n");
	}else { 
	for(int i = 0; i < 100; i++)
	{
        y[i] = a * x[i] + y[i];
        sleep(2);
	}
	}
    te = omp_get_wtime();
    t = te - tb;
    printf("Time of kernal: %lf\n",t);

}
