#include <k52/common/random.h>

#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <cmath>
#include <stdexcept>

namespace k52
{
namespace common
{

Random& Random::Instance()
{
    static Random self;
    return self;
}

void Random::ValidateProbability(double probability)
{
    if ( probability < 0 || probability > 1 )
    {
        throw std::invalid_argument("Invalid probability value");
    }
}

double Random::GetBaseRandomQuantity()
{
    return ((double) rand() / RAND_MAX);
}

double Random::GetContinuousRandomQuantity(double min_value, double max_value)
{
    double base = GetBaseRandomQuantity();
    return base * (max_value - min_value) + min_value;
}

std::vector<double> Random::GenerateRandomVector(size_t vector_size, double min_value, double max_value)
{
    std::vector<double> random_point(vector_size);
    for (size_t i = 0; i<vector_size; i++)
    {
        random_point[i] = this->GetContinuousRandomQuantity(min_value, max_value);
    }
    return random_point;
}

bool Random::GetRandomBool()
{
    int bit = GetNextBitFromBoolBase();
    return bit == 0;
}

int Random::GetUniformlyDistributedDiscreteRandomQuantity(int min_value, int max_value)
{
    return rand() % (max_value-min_value+1) + min_value;
}

bool Random::CheckEventOutcome(double event_probability)
{
    ValidateProbability(event_probability);

    return GetBaseRandomQuantity() <= event_probability;
}

Random::Random()
{
    //Seed random
    srand((unsigned)(time(NULL)));
    //srand(1);
    bool_base_ = rand();
    next_bit_in_bool_base_ = 0;

    max_bit_in_bool_base_ = 0;
    int max_bool_base_value = 1;

    for (std::size_t i = 0; i < sizeof(int) * 8; i++)
    {
        max_bool_base_value *= 2;
        if (max_bool_base_value > RAND_MAX)
        {
            break;
        }
        max_bit_in_bool_base_ ++;
    }
}

int Random::GetNextBitFromBoolBase()
{
    if( next_bit_in_bool_base_ >  max_bit_in_bool_base_)
    {
        next_bit_in_bool_base_ = 0;
        bool_base_ = rand();
    }

    int bitmask = 0x1;
    bitmask = bitmask << next_bit_in_bool_base_;
    next_bit_in_bool_base_ ++;
    return bool_base_ & bitmask;
}

}/* namespace common */
}/* namespace k52 */

