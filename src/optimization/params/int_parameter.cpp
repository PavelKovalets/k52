#include <k52/optimization/params/int_parameter.h>

#include "../random.h"

using ::std::vector;

namespace k52
{
namespace optimization
{

IntParameter::IntParameter(int value, int min_value, int max_value)
{
    SetConstChromosomeSize( CountVectorSize(min_value, max_value) );

    value_ = value;
    min_value_ = min_value;
    max_value_ = max_value;
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

bool IntParameter::CheckConstraints() const
{
    return (value_ <= max_value_) && (value_ >= min_value_);
}

void IntParameter::SetChromosome(vector<bool>::iterator from, vector<bool>::iterator to) const
{
    size_t chromosome_size = to - from;
    this->CheckForConstChromosomeSize(chromosome_size);

    IntParameter::SetBoolVectorFromInt(from, to, value_ - min_value_);
}

void IntParameter::SetFromChromosome(vector<bool>::const_iterator from, vector<bool>::const_iterator to)
{
    size_t chromosome_size = to - from;
    this->CheckForConstChromosomeSize(chromosome_size);

    value_ = IntParameter::GetIntFromBoolVector(from, to) + min_value_;
}

size_t IntParameter::CountVectorSize(int min_value, int max_value)
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

int IntParameter::GetIntFromBoolVector(vector<bool>::const_iterator from, vector<bool>::const_iterator to)
{
    unsigned int result = 0;

    size_t bit_number = 0;

    for (vector<bool>::const_iterator it = from; it != to; it++)
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

void IntParameter::SetBoolVectorFromInt(vector<bool>::iterator from, vector<bool>::iterator to, int value)
{
    size_t bit_number = 0;

    for (vector<bool>::iterator it = from; it != to; it++)
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
