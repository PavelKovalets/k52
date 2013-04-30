#include <k52/optimization/params/double_parameter.h>

#include <math.h>
#include <stdexcept>

#include "../random.h"

namespace k52
{
namespace optimization
{

DoubleParameter::DoubleParameter()
{
    base_int_parameter_ = IntParameter::shared_ptr();
}

DoubleParameter::DoubleParameter(double desired_value, double min_value, double max_value, double desired_precision)
{
    if(max_value <= min_value)
    {
        throw std::invalid_argument("maxValue <= minValue");
    }

    max_value_ = max_value;
    min_value_ = min_value;

    if(!CheckBounds(desired_value))
    {
        throw std::invalid_argument("desired_value does not lie whithin [min_value;max_value] interval.");
    }

    int best_max_int = CountBestMaxInt( GetMaxInt(min_value, max_value, desired_precision) );
    int min_int = 0;

    precision_ = (max_value - min_value) / best_max_int;
    base_int_parameter_ = IntParameter::shared_ptr(new IntParameter(min_int, best_max_int));

    SetValue(desired_value);

    this->SetConstChromosomeSize(base_int_parameter_->GetChromosomeSize());
}

DoubleParameter::DoubleParameter(const DoubleParameter& a)
{
    base_int_parameter_ = IntParameter::shared_ptr();
    *this = a;
}

DoubleParameter& DoubleParameter::operator=(const DoubleParameter & a)
{
    if (this != &a) // protect against invalid self-assignment
    {
        this->ConstChromosomeSizeParemeters::operator =(a);
        max_value_ = a.max_value_;
        min_value_ = a.min_value_;
        precision_ = a.precision_;

        if(a.base_int_parameter_ != NULL)
        {
            base_int_parameter_ = IntParameter::shared_ptr(a.base_int_parameter_->Clone());
        }
        else
        {
            base_int_parameter_ = IntParameter::shared_ptr();
        }
    }
    // by convention, always return *this
    return *this;
}

DoubleParameter *DoubleParameter::Clone() const
{
    DoubleParameter* clone = new DoubleParameter(*this);
    return clone;
}

bool DoubleParameter::CheckConstraints() const
{
    return CheckBounds(GetValue());
}

void DoubleParameter::SetChromosome(std::vector<bool>::iterator from, std::vector<bool>::iterator to) const
{
    base_int_parameter_->SetChromosome(from, to);
}

void DoubleParameter::SetFromChromosome(std::vector<bool>::const_iterator from, std::vector<bool>::const_iterator to)
{
    base_int_parameter_->SetFromChromosome(from, to);
}

double DoubleParameter::GetValue() const
{
    return  base_int_parameter_->get_value() * precision_ + min_value_;
}

void DoubleParameter::SetValue(double value)
{
    int int_value = ((value - min_value_)/precision_);
    base_int_parameter_->set_value(int_value);
}

double DoubleParameter::get_max_value() const
{
    return max_value_;
}

double DoubleParameter::get_min_value() const
{
    return min_value_;
}

double DoubleParameter::get_actual_precision() const
{
    return precision_;
}

int DoubleParameter::GetMaxInt(double min_value, double max_value, double precision)
{
    int max_int = ceil((max_value - min_value)/precision);
    if(max_int < 1)
    {
        throw std::invalid_argument("minValue maxValue or precision were set incorrect");
    }
    return max_int;
}

int DoubleParameter::CountBestMaxInt(int initial_max_int)
{
    int best_max_int = 1;

    while(initial_max_int>best_max_int)
    {
        best_max_int *= 2;
    }

    return best_max_int;
}

bool DoubleParameter::CheckBounds(double value) const
{
    return value >= min_value_ && value <= max_value_;
}

}/* namespace optimization */
}/* namespace k52 */
