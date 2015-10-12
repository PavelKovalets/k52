#ifndef K52_HELPERS_H
#define K52_HELPERS_H

#include <complex>
#include <vector>

namespace k52
{
namespace common
{

class Helpers
{
public:
    static std::vector <std::complex< double> > Conjugate(const std::vector <std::complex< double> > &sequence);
};

}/* namespace common */
}/* namespace k52 */

#endif //K52_HELPERS_H
