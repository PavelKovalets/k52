#ifndef CONSTCHROMOSOMESIZEPAREMETERS_H_
#define CONSTCHROMOSOMESIZEPAREMETERS_H_

#include <k52/optimization/params/discrete_parameters.h>

namespace k52
{
namespace optimize
{

/**
@class ConstChromosomeSizeParemeters
Represents paremeters, witch total chromosome size
cannot be changed during conversion from chromose.
Adds method to perform check for this condition.
*/
class ConstChromosomeSizeParemeters: public DiscreteParameters
{
public:
    typedef boost::shared_ptr<ConstChromosomeSizeParemeters> shared_ptr;

    ConstChromosomeSizeParemeters();

    size_t GetChromosomeSize() const;

    void SetChromosome(std::vector<bool>::iterator from, std::vector<bool>::iterator to) const = 0;

    void SetFromChromosome(std::vector<bool>::const_iterator from, std::vector<bool>::const_iterator to) = 0;

    virtual bool CheckConstraints() const = 0;

    virtual ConstChromosomeSizeParemeters* Clone() const = 0;

protected:

    ///Sets chromosome size that will remain during execution.
    ///Usually must be called on this parameters initialization.
    ///ATTENTION! Must be called once. Otherwize exception will be thrown.
    void SetConstChromosomeSize(size_t chromosome_size);

    ///Checks for chromosome size to remain const since it was set.
    ///Usually must be call on every usage of SetFromChromosome
    /// or other chromosome changing method.
    ///If chromosome_size was changed or was not set - throws an exception.
    void CheckForConstChromosomeSize(size_t chromosome_size) const;

private:
    void CheckIfChromosomeWasSet() const;

    bool was_chromosome_size_set_;
    size_t chromosome_size_;
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* CONSTCHROMOSOMESIZEPAREMETERS_H_ */
