#include<iostream> 
#include<cmath> 
#define N 10000

using namespace std; 
 
int main() 
{ 
    int i, j; 
    double area, pi;
    double dx, y, x;
    
    dx = 1.0/N; 
    x = 0.0; 
    area = 0.0; 

    for(i=0;i<N;i++)
    {
        x = i*dx;
        y = sqrt(1-x*x);
        area += y*dx;
    }
    pi = 4.0*area;
    cout << "\nValue of pi is = " << pi << endl; 
    return 0;
}