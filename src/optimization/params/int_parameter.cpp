#include <k52/common/random.h>
#include <k52/optimization/params/int_parameter.h>

#include <stdexcept>

namespace k52
{
namespace optimization
{

IntParameter::IntParameter(int min_value, int max_value)
{
    Initialize(min_value, min_value, max_value);
}

IntParameter::IntParameter(int value, int min_value, int max_value)
{
    Initialize(value, min_value, max_value);
}

int IntParameter::get_value() const
{
    return value_;
}

void IntParameter::set_value(int value)
{
    value_ = value;
}

int IntParameter::get_max_value() const
{
    return max_value_;
}

int IntParameter::get_min_value() const
{
    return min_value_;
}

IntParameter* IntParameter::Clone() const
{
    IntParameter* clone = new IntParameter(value_, min_value_, max_value_);
    return clone;
}

bool IntParameter::HasSameMetaParameters(const IDiscreteParameters* parameters) const
{
    const IntParameter* int_parameter = dynamic_cast<const IntParameter*>(parameters);
    if (!int_parameter)
    {
        throw std::runtime_error("Unexpected object type to check for meta parameters");
    }
    return max_value_ == int_parameter->max_value_ &&
        min_value_ == int_parameter->min_value_;
}

bool IntParameter::CheckConstraints() const
{
    return (value_ <= max_value_) && (value_ >= min_value_);
}

void IntParameter::SetChromosome(ChromosomeType::iterator from, ChromosomeType::iterator to) const
{
    size_t chromosome_size = to - from;
    this->CheckForConstChromosomeSize(chromosome_size);

    IntParameter::SetChromosomeFromInt(from, to, value_ - min_value_);
}

void IntParameter::SetFromChromosome(ChromosomeType::const_iterator from, ChromosomeType::const_iterator to)
{
    size_t chromosome_size = to - from;
    this->CheckForConstChromosomeSize(chromosome_size);

    value_ = IntParameter::GetIntFromChromosome(from, to) + min_value_;
}

void IntParameter::Initialize(int value, int min_value, int max_value)
{
    SetConstChromosomeSize( CountChromosomeSize(min_value, max_value) );

    value_ = value;
    min_value_ = min_value;
    max_value_ = max_value;
}

size_t IntParameter::CountChromosomeSize(int min_value, int max_value)
{
    int x = 1;
    int target = max_value - min_value;
    size_t power = 0;
    while(target>x)
    {
        x*=2;
        power++;
    }
    return power;
}

int IntParameter::GetIntFromChromosome(ChromosomeType::const_iterator from, ChromosomeType::const_iterator to)
{
    unsigned int result = 0;

    size_t bit_number = 0;

    for (ChromosomeType::const_iterator it = from; it != to; ++it)
    {
        if (*it)
        {
            result |= (1 << bit_number);
        }
        else
        {
            result &= ~(1 << bit_number);
        }

        bit_number++;
    }

    return ((int)result);
}

void IntParameter::SetChromosomeFromInt(ChromosomeType::iterator from, ChromosomeType::iterator to, int value)
{
    size_t bit_number = 0;

    for (ChromosomeType::iterator it = from; it != to; ++it)
    {
        if ((value >> bit_number) & 1)
        {
            (*it) = true;
        }
        else
        {
            (*it) = false;
        }

        bit_number++;
    }
}

}/* namespace optimization */
}/* namespace k52 */
