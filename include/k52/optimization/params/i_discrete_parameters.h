#ifndef IDISCRETEPARAMETERS_H_
#define IDISCRETEPARAMETERS_H_

#include <k52/common/disallow_copy_and_assign.h>
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

    ///Default counstructor should be explicitelly defined if DISALLOW_COPY_AND_ASSIGN used
    IDiscreteParameters() {}

    virtual ~IDiscreteParameters() {}

    virtual IDiscreteParameters* Clone() const = 0;

private:
    DISALLOW_COPY_AND_ASSIGN(IDiscreteParameters);
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* IDISCRETEPARAMETERS_H_ */
