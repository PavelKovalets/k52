#include "simple_parameters_processor.h"

#include <stdexcept>

namespace k52
{
namespace optimization
{

SimpleParametersProcessor::SimpleParametersProcessor()
    :function_counter_(-1)
{
}

IParameters::shared_ptr SimpleParametersProcessor::ProcessParameters(
    const IObjectiveFunction &function_to_optimize,
    const std::vector< IParameters::shared_ptr >& parameters,
    bool maximize)
{
    if(parameters.size() < 1)
    {
        throw std::invalid_argument("parameters should contain at least one element in vector");
    }
    std::vector<const IParameters*> parameters_to_count = ExtractPointers(parameters);
    std::vector<double> values = function_counter_.CountObjectiveFunctionValues(
                parameters_to_count, function_to_optimize);
    size_t index = 0;
    double value = values[index];

    for(size_t i=1; i<values.size(); i++)
    {
        bool condition = values[i] > value;
        condition = maximize ? condition : (!condition);

        if(condition)
        {
            index = i;
            value = values[i];
        }
    }

    return parameters[index];
}

std::vector<const IParameters*> SimpleParametersProcessor::ExtractPointers(
        const std::vector< IParameters::shared_ptr >& parameters)
{
    std::vector<const IParameters*> pointers(parameters.size());
    for(size_t i=0; i<parameters.size(); i++)
    {
        pointers[i] = parameters[i].get();
    }
    return pointers;
}

}/* namespace optimization */
}/* namespace k52 */
