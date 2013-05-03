#ifndef SIMPLEPARAMETERSPROCESSOR_H_
#define SIMPLEPARAMETERSPROCESSOR_H_

#include <k52/common/disallow_copy_and_assign.h>

#include "i_parameters_processor.h"
#include "objective_function_counter.h"

namespace k52
{
namespace optimization
{

class SimpleParametersProcessor : public IParametersProcessor
{
public:
    typedef boost::shared_ptr<SimpleParametersProcessor> shared_ptr;

    SimpleParametersProcessor();

    virtual IContinuousParameters::shared_ptr ProcessParameters(const IObjectiveFunction &function_to_optimize,
                                      const std::vector< IContinuousParameters::shared_ptr >& parameters,
                                      bool maximize);

private:
    std::vector<const IParameters*> ExtractPointers(
            const std::vector< IContinuousParameters::shared_ptr >& parameters);

    ObjectiveFunctionCounter function_counter_;

    DISALLOW_COPY_AND_ASSIGN(SimpleParametersProcessor);
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* SIMPLEPARAMETERSPROCESSOR_H_ */
