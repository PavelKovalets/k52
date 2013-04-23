#include "random.h"

#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <cmath>

namespace k52
{
namespace optimization
{

Random& Random::Instance()
{
    static Random self;
    return self;
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

bool Random::GetRandomBool()
{
    int bit = GetNextBitFromBoolBase();
    return bit == 0;
}

void Random::SetRandomBoolVector(std::vector<bool>* array)
{
    for(size_t i = 0; i < array->size(); i++)
    {
        (*array)[i] = GetRandomBool();
    }
}

int Random::GetUniformlyDistributedDiscreteRandomQuantity(int min_value, int max_value)
{
    return rand() % (max_value-min_value+1) + min_value;
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

    for(int i=0; i<sizeof(int) * 8; i++)
    {
        max_bool_base_value *= 2;
        if(max_bool_base_value > RAND_MAX)
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

}/* namespace optimization */
}/* namespace k52 */

