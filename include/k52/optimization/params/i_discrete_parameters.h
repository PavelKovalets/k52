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

    /// !Not the core functionality, so could be not implemented (throw exception).
    /// Checks if the meta-parameters of parameters match (e.g. min or max values,
    /// basically all members of the class except of actual parameters values).
    /// Exact equality is needed, so no rounding should be applied to float point values.
    /// That results in same chromosome representations - chromosome size and the bits 
    /// on the exact chromosome position have same role (represents same feature in parameter).
    /// @param parameters - to check meta-parameters of. MUST have same type as current (this) parameters,
    /// should be checked before this method is called, otherwize validity is not garanteed.
    /// @return "true" if parameters have same meta-parameters, otherwize "false".
    virtual bool HasSameMetaParameters(const IDiscreteParameters* parameters) const = 0;

private:
    DISALLOW_COPY_AND_ASSIGN(IDiscreteParameters);
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* IDISCRETEPARAMETERS_H_ */
