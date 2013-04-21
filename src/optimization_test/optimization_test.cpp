#include <iostream>

#include <k52/optimization/bounded_nelder_mead.h>

using namespace std;

int main()
{
    cout<<"Hello from optimization tests"<<endl;
    double l = 10;
    double precision = 1e-9;
    double lower_bound = -10000;
    double upper_bound = 10000;
    k52::optimization::BoundedNelderMead bounded_nelder_mead(l, precision, lower_bound, upper_bound);
    k52::optimization::IOptimizer* optimizer = &bounded_nelder_mead;
    return 0;
}
