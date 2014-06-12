#ifndef RANDOM_H_
#define RANDOM_H_

#include <vector>
#include <k52/common/disallow_copy_and_assign.h>

namespace k52
{
namespace optimization
{

/**
@class Random
Provides methods to generate random quantities
*/
class Random
{
public:
    /// Implementation of singleton pattern to avoid multiple seed
    /// @return the only instance of Random class
    static Random& Instance();

    ///Generates base random quantity - uniformly distributed on interval [0, 1]
    ///@return base random quantity
    double GetBaseRandomQuantity();

    ///Generates continuous random quantity - uniformly distributed on interval [min_value, max_value]
    ///@param min_value - interval lower bound
    ///@param max_value - interval upper bound 
    ///@return continuous random quantity between min_value and max_value
    double GetContinuousRandomQuantity(double min_value, double max_value);

    ///@param vector_size - size of vector to be generated
    ///@param min_value - interval lower bound
    ///@param max_value - interval upper bound 
    ///@return vector of continuous random quantities
    std::vector<double> GenerateRandomVector(std::size_t vector_size, double min_value, double max_value);

    ///Generates uniformly distributed boolean - 0.5 to true, 0.5 to false
    ///@return random boolean
    bool GetRandomBool();

    ///Generates uniformly distributed discrete random quantity within [min_value, max_value] interval
    ///@param min_value - interval lower bound
    ///@param max_value - interval upper bound
    ///@return random integer between min_value and max_value
    int GetUniformlyDistributedDiscreteRandomQuantity(int min_value, int max_value);

private:
    Random();
    int GetNextBitFromBoolBase();

    int bool_base_;
    int next_bit_in_bool_base_;
    int max_bit_in_bool_base_;

    DISALLOW_COPY_AND_ASSIGN(Random);
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* RANDOM_H_ */
