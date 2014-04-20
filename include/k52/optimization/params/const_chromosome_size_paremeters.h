#ifndef CONSTCHROMOSOMESIZEPAREMETERS_H_
#define CONSTCHROMOSOMESIZEPAREMETERS_H_

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/optimization/params/discrete_parameters.h>

namespace k52
{
namespace optimization
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

    void SetChromosome(ChromosomeType::iterator from, ChromosomeType::iterator to) const = 0;

    void SetFromChromosome(ChromosomeType::const_iterator from, ChromosomeType::const_iterator to) = 0;

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

    void CopyState(const ConstChromosomeSizeParemeters* source);

private:
    void CheckIfChromosomeWasSet() const;

    bool was_chromosome_size_set_;
    size_t chromosome_size_;

    DISALLOW_COPY_AND_ASSIGN(ConstChromosomeSizeParemeters);
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* CONSTCHROMOSOMESIZEPAREMETERS_H_ */
