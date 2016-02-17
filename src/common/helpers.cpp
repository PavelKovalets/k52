#include <k52/common/helpers.h>
#include <iostream>

using ::std::complex;
using ::std::vector;
using ::std::cout;
using ::std::endl;

namespace k52
{
namespace common
{

vector< complex< double > > Helpers::Conjugate(
        const vector< complex< double > > &sequence)
{
    vector< complex < double> > conjugate(sequence.size());

    for (std::size_t i = 0; i < sequence.size(); ++i)
    {
        conjugate[i] = std::conj(sequence[i]);
    }

    return conjugate;
}

void Helpers::PrintVector(const std::vector<double>& values)
{
    cout.precision(15);

    cout << "[ ";
    for(size_t i = 0; i < values.size(); i++)
    {
        cout << values[i];
        if(i != values.size() - 1)
        {
            cout << "; ";
        }
    }
    cout << " ]" << endl;
}

}/* namespace common */
}/* namespace k52 */

