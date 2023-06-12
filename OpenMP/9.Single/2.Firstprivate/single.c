#include<stdio.h>
#include <omp.h>
#define N     5
int main () {
int i = 1;
float a[N], b[N], c[N], d[N];
/* Some initializations */
for (i=0; i < N; i++) {
  a[i] = i * 1.5;
  b[i] = i + 22.35;
  }
  /* Fork a team of threads with each thread having a private i variable and shared varable a,b,c,d */
#pragma omp parallel shared(a,b,c,d) firstprivate(i)
  {
  #pragma omp single
  
    {
    for (i=0; i < N; i++){
      c[i] = a[i] + b[i];
      printf("1st loop # Working thread : %d # %f + %f = %f\n",omp_get_thread_num(),a[i],b[i],c[i]);	
     }
    for (i=0; i < N; i++){
      d[i] = a[i] * b[i];
      printf("2nd loop # Working thread : %d # %f * %f = %f\n",omp_get_thread_num(),a[i],b[i],d[i]);
    }
    }  
    /* end of sections */
  }  /* end of parallel section */
 return 0;
}