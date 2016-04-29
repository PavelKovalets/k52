#include <k52/optimization/params/double_parameters_array.h>

#include <stdexcept>

namespace k52
{
namespace optimization
{

DoubleParametersArray::DoubleParametersArray(double min_value,
                                             double max_value,
                                             double desired_precision,
                                             size_t number_of_parameters)
    : sample_parameter_ (new DoubleParameter(min_value, min_value, max_value, desired_precision)),
      values_(number_of_parameters)
{
    SetConstChromosomeSize(CountTotalChromosomeSize());
}

DoubleParametersArray* DoubleParametersArray::Clone() const
{
    DoubleParametersArray* clone = new DoubleParametersArray();
    clone->values_ = values_;

    clone->sample_parameter_ = sample_parameter_ != NULL ?
        DoubleParameter::shared_ptr( sample_parameter_->Clone() ) : 
        DoubleParameter::shared_ptr();

    clone->SetConstChromosomeSize(CountTotalChromosomeSize());

    return clone;
}

bool DoubleParametersArray::HasSameMetaParameters(const IDiscreteParameters* parameters) const
{
    const DoubleParametersArray* parameters_array = dynamic_cast<const DoubleParametersArray*>(parameters);
    if (!parameters_array)
    {
        throw std::runtime_error("Unexpected object type to check for meta parameters");
    }
    return values_.size() == parameters_array->get_number_of_parameters() &&
        sample_parameter_->HasSameMetaParameters(parameters_array->sample_parameter_.get());
}

bool DoubleParametersArray::CheckConstraints() const
{
    for(size_t i=0; i<values_.size(); i++)
    {
        sample_parameter_->SetValue(values_[i]);
        if(!sample_parameter_->CheckConstraints())
        {
            return false;
        }
    }
    return true;
}

void DoubleParametersArray::SetChromosome(ChromosomeType::iterator from, ChromosomeType::iterator to) const
{
    size_t chromosome_size = to - from;

    this->CheckForConstChromosomeSize(chromosome_size);

    ChromosomeType::iterator current_from = from;
    size_t parameter_chromosome_size = sample_parameter_->GetChromosomeSize();

    for(size_t i = 0; i < values_.size(); i++)
    {
        ChromosomeType::iterator current_to = current_from + parameter_chromosome_size;

        sample_parameter_->SetValue(values_[i]);
        sample_parameter_->SetChromosome(current_from, current_to);

        current_from = current_to;
    }
}

void DoubleParametersArray::SetFromChromosome(ChromosomeType::const_iterator from, ChromosomeType::const_iterator to)
{
    size_t chromosome_size = to - from;

    this->CheckForConstChromosomeSize(chromosome_size);

    ChromosomeType::const_iterator current_from = from;
    size_t parameter_chromosome_size = sample_parameter_->GetChromosomeSize();

    for(size_t i = 0; i < values_.size(); i++)
    {
        ChromosomeType::const_iterator current_to = current_from + parameter_chromosome_size;

        sample_parameter_->SetFromChromosome(current_from, current_to);
        values_[i] = sample_parameter_->GetValue();

        current_from = current_to;
    }
}

void DoubleParametersArray::SetValues(const std::vector<double>& values)
{
    if (values.size() != values_.size())
    {
        throw std::invalid_argument("Values has incorrect size.");
    }

    values_ = values;

    if (!CheckConstraints())
    {
        throw std::invalid_argument("One of the values does not satisfy constraints.");
    }
}

std::vector<double> DoubleParametersArray::get_values() const
{
    return values_;
}

double DoubleParametersArray::get_max_value() const
{
    return sample_parameter_->get_max_value();
}

double DoubleParametersArray::get_min_value() const
{
    return sample_parameter_->get_min_value();
}

size_t DoubleParametersArray::get_number_of_parameters() const
{
    return values_.size();
}

double DoubleParametersArray::get_actual_precision() const
{
    return sample_parameter_->get_actual_precision();
}

DoubleParametersArray::DoubleParametersArray() {}

size_t DoubleParametersArray::CountTotalChromosomeSize() const
{
    return sample_parameter_->GetChromosomeSize() * values_.size();
}

}/* namespace optimization */
}/* namespace k52 */
