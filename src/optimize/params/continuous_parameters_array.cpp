#include <optimize/params/continuous_parameters_array.h>

#include <stdexcept>

namespace k52
{
namespace optimize
{

ContinuousParametersArray::ContinuousParametersArray(size_t number_of_parameters)
    : values_(number_of_parameters)
{
}

void ContinuousParametersArray::SetValues(const std::vector<double>& values)
{
    if(values.size() != values_.size())
    {
        throw std::invalid_argument("values has incorrect size");
    }

    for(size_t i=0; i<values_.size(); i++)
    {
        values_[i] = values[i];
    }
}

std::vector<double> ContinuousParametersArray::GetValues() const
{
    return values_;
}

ContinuousParametersArray *ContinuousParametersArray::Clone() const
{
    ContinuousParametersArray* clone = new ContinuousParametersArray(values_.size());
    clone->values_ = values_;
    return clone;
}

bool ContinuousParametersArray::CheckConstraints() const
{
    return true;
}

}/* namespace optimize */
}/* namespace k52 */
