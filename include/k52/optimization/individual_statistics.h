#ifndef INDIVIDUALSTATISTICS_H_
#define INDIVIDUALSTATISTICS_H_

namespace k52
{
namespace optimize
{

/**
@class IndividualStatistics
Represents statistics about single individual
*/
class IndividualStatistics
{
public:
    static bool Less (IndividualStatistics const& left_arg, IndividualStatistics const& right_arg)
    {
        return left_arg.times_chosen_for_crossover < right_arg.times_chosen_for_crossover;
    }

    static bool Greater (IndividualStatistics const& left_arg, IndividualStatistics const& right_arg)
    {
        return left_arg.times_chosen_for_crossover > right_arg.times_chosen_for_crossover;
    }

    double fitness;
    int times_chosen_for_crossover;
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* INDIVIDUALSTATISTICS_H_ */
