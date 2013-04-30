#ifndef IDISCRETEPARAMETERS_H_
#define IDISCRETEPARAMETERS_H_

#include <k52/optimization/i_convertable_to_chromosome.h>
#include <k52/optimization/params/i_parameters.h>

namespace k52
{
namespace optimization
{

class IDiscreteParameters: public IParameters, public IConvertableToChromosome
{
public:
    typedef boost::shared_ptr<IDiscreteParameters> shared_ptr;

    virtual ~IDiscreteParameters() {}

    virtual IDiscreteParameters* Clone() const = 0;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* IDISCRETEPARAMETERS_H_ */
