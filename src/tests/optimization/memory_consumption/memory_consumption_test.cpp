#include <iostream>
#include <math.h>
#include <ctime>
#include <limits>
#include <stdlib.h>

#include <k52/optimization/params/double_parameters_array.h>
#include <k52/optimization/params/continuous_parameters_array.h>

using namespace std;
using namespace k52::optimization;

const double GlobalPrecision = 0.001;
const int GlobalNumberOfParameters = 4096;
const double GlobalMinValue = -1;
const double GlobalMaxValue = 1;
const int GlobalPopulationSize = 1000;

int main()
{
    time_t begin, end;
    time(&begin);
    cout<<"Begin"<<endl;

    k52::optimization::DoubleParametersArray parameters(GlobalMinValue, GlobalMaxValue, GlobalPrecision, GlobalNumberOfParameters);
    cout<<"Chromosome size: "<<parameters.GetChromosomeSize()<<endl;

    vector<k52::optimization::DoubleParametersArray*> test(GlobalPopulationSize);

    for (int i =0 ; i< GlobalPopulationSize; i++)
    {
        test[i] = parameters.Clone();
    }

    int e = 0;
    cin>>e;

    time(&end);
    cout << "Time elapsed: " << difftime(end, begin) << " seconds "<< endl;
    return 0;
}