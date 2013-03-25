#ifndef INTPARAMETER_H_
#define INTPARAMETER_H_

#include <k52/optimization/params/const_chromosome_size_paremeters.h>

namespace k52
{
namespace optimize
{

/**
@class IntParameter
Represents simple integer parameter with upper and lower bound.
*/
class IntParameter: public ConstChromosomeSizeParemeters
{
public:
    typedef boost::shared_ptr<IntParameter> shared_ptr;

    ///Creates an instance of IntParameter
    ///@param value - value of IntParameter to be set initially
    ///@param min_value - minimum allowed value of IntParameter, it's lower bound constraint
    ///@param max_value - maximum allowed value of IntParameter, it's upper bound constraint
    IntParameter(int value, int min_value, int max_value);

    ///@return current value of IntParameter
    int get_value() const;

    ///@return maximum allowed value of IntParameter
    int get_max_value() const;

    ///@return minimum allowed value of IntParameter
    int get_min_value() const;

    IntParameter* Clone() const;

    bool CheckConstraints() const;

    void SetChromosome(std::vector<bool>::iterator from, std::vector<bool>::iterator to) const;

    void SetFromChromosome(std::vector<bool>::const_iterator from, std::vector<bool>::const_iterator to);

private:
    static size_t CountVectorSize(int min_value, int max_value);
    static int GetIntFromBoolVector(std::vector<bool>::const_iterator from, std::vector<bool>::const_iterator to);
    static void SetBoolVectorFromInt(std::vector<bool>::iterator from, std::vector<bool>::iterator to, int value);

    int value_;
    int min_value_;
    int max_value_;
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* INTPARAMETER_H_ */
