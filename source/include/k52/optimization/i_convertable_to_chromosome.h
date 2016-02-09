#ifndef ICONVERTABLETOCHROMOSOME_H_
#define ICONVERTABLETOCHROMOSOME_H_

#include <k52/optimization/chromosome.h>

namespace k52
{
namespace optimization
{

/**
@class IConvertableToChromosome
Allows convertation of derived instance to Chromosome and back.
In simplest case - binary form of object is provided as Chromosome.
*/
class IConvertableToChromosome
{
public:
    ///Virtual destructor for correct deallocation of resources in derived classes
    virtual ~IConvertableToChromosome() {}

    ///Sets external Chromosome from current object
    ///@param from - iterator, pointing to the first element of chromosome to be set
    ///@param to - iterator, pointing to the element next to last that must be set
    virtual void SetChromosome(ChromosomeType::iterator from, ChromosomeType::iterator to) const = 0;

    ///Sets current object according to it's representation from external Chromosome
    ///@param from - iterator, pointing to the first element of chromosome
    ///@param to - iterator, pointing to the element next to last that must be used
    virtual void SetFromChromosome(ChromosomeType::const_iterator from, ChromosomeType::const_iterator to) = 0;

    ///@return reuqired size of chromosome.
    ///ATTENTION! Value returned by this function must be constant during execution.
    virtual std::size_t GetChromosomeSize() const = 0;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* ICONVERTABLETOCHROMOSOME_H_ */
