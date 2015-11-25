#include <k52/common/helpers.h>

using ::std::complex;
using ::std::vector;

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

}/* namespace common */
}/* namespace k52 */

