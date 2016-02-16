#ifndef INTPARAMETER_H_
#define INTPARAMETER_H_

#include <k52/optimization/params/const_chromosome_size_paremeters.h>

namespace k52
{
namespace optimization
{

/**
@class IntParameter
Represents simple integer parameter with upper and lower bound.
*/
class IntParameter: public ConstChromosomeSizeParemeters
{
public:
    typedef boost::shared_ptr<IntParameter> shared_ptr;

    ///Creates an instance of IntParameter and assigns its value to min_value
    ///@param min_value - minimum allowed value of IntParameter, it's lower bound constraint
    ///@param max_value - maximum allowed value of IntParameter, it's upper bound constraint
    IntParameter(int min_value, int max_value);

    ///Creates an instance of IntParameter
    ///@param value - value of IntParameter to be set initially
    ///@param min_value - minimum allowed value of IntParameter, it's lower bound constraint
    ///@param max_value - maximum allowed value of IntParameter, it's upper bound constraint
    IntParameter(int value, int min_value, int max_value);

    ///@return current value of IntParameter
    int get_value() const;
    void set_value(int value);

    ///@return maximum allowed value of IntParameter
    int get_max_value() const;

    ///@return minimum allowed value of IntParameter
    int get_min_value() const;

    IntParameter* Clone() const;

    bool HasSameMetaParameters(const IDiscreteParameters* parameters) const;

    bool CheckConstraints() const;

    void SetChromosome(ChromosomeType::iterator from, ChromosomeType::iterator to) const;

    void SetFromChromosome(ChromosomeType::const_iterator from, ChromosomeType::const_iterator to);

protected:
    void Initialize(int value, int min_value, int max_value);

private:
    static size_t CountChromosomeSize(int min_value, int max_value);
    static int GetIntFromChromosome(ChromosomeType::const_iterator from, ChromosomeType::const_iterator to);
    static void SetChromosomeFromInt(ChromosomeType::iterator from, ChromosomeType::iterator to, int value);

    int value_;
    int min_value_;
    int max_value_;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* INTPARAMETER_H_ */
