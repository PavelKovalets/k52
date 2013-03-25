#include <k52/optimization/params/double_parameters_array.h>

#include <stdexcept>

namespace k52
{
namespace optimize
{

DoubleParametersArray::DoubleParametersArray(double min_value, double max_value, double desired_precision, size_t number_of_parameters)
{
    min_value_ = min_value;
    max_value_ = max_value;

    if(number_of_parameters<=0)
    {
        throw std::logic_error("number_of_parameters<=0!");
    }

    double_parameters_ = CompositeDiscreteParameters::shared_ptr(new CompositeDiscreteParameters());
    IDiscreteParameters::shared_ptr sample_parameter(new DoubleParameter(min_value_, min_value_, max_value_, desired_precision));
    double_parameters_->Initialize(sample_parameter, number_of_parameters);
}

DoubleParametersArray* DoubleParametersArray::Clone() const
{
    DoubleParametersArray* clone = new DoubleParametersArray();
    clone->max_value_ = max_value_;
    clone->min_value_ = min_value_;

    clone->double_parameters_ = double_parameters_ != NULL ?
        CompositeDiscreteParameters::shared_ptr( double_parameters_->Clone() ) : 
        CompositeDiscreteParameters::shared_ptr();

    return clone;
}

bool DoubleParametersArray::CheckConstraints() const
{
    return double_parameters_->CheckConstraints();
}

size_t DoubleParametersArray::GetChromosomeSize() const
{
    return double_parameters_->GetChromosomeSize();
}

void DoubleParametersArray::SetChromosome(std::vector<bool>::iterator from, std::vector<bool>::iterator to) const
{
    double_parameters_->SetChromosome(from, to);
}

void DoubleParametersArray::SetFromChromosome(std::vector<bool>::const_iterator from, std::vector<bool>::const_iterator to)
{
    double_parameters_->SetFromChromosome(from, to);
}

std::vector<double> DoubleParametersArray::GetValues() const
{
    std::vector<double> values(double_parameters_->GetNumberOfParameters());

    for(size_t i=0; i<double_parameters_->GetNumberOfParameters(); i++)
    {
        values[i] = GetDoubleParameter(i)->GetValue();
    }
    return values;
}

double DoubleParametersArray::get_max_value() const
{
    return max_value_;
}

double DoubleParametersArray::get_min_value() const
{
    return min_value_;
}

size_t DoubleParametersArray::get_number_of_parameters() const
{
    return double_parameters_->GetNumberOfParameters();
}

double DoubleParametersArray::get_actual_precision() const
{
    return GetDoubleParameter(0)->get_actual_precision();
}

const DoubleParameter::shared_ptr DoubleParametersArray::GetDoubleParameter(size_t index) const
{
    return boost::dynamic_pointer_cast<DoubleParameter>(double_parameters_->GetParameter(index));
}

DoubleParametersArray::DoubleParametersArray() {}

}/* namespace optimize */
}/* namespace k52 */
