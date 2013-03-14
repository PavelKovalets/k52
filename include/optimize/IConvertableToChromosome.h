/*
 * IConvertableToChromosome.h
 *
 *  Created on: Mar 4, 2012
 *      Author: feanor
 */

#ifndef ICONVERTABLETOCHROMOSOME_H_
#define ICONVERTABLETOCHROMOSOME_H_

#include <vector>

using ::std::vector;
using ::std::size_t;

namespace k52
{
namespace optimize
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
	///@param chromosomeSize - size of chromosome reprosented by from and to iterators
	virtual void setChromosome(vector<bool>::iterator from, vector<bool>::iterator to) const = 0;

	///Sets current object according to it's representation from external Chromosome
	///@param from - iterator, pointing to the first element of chromosome
	///@param to - iterator, pointing to the element next to last that must be used
	///@param chromosomeSize - size of chromosome reprosented by from and to iterators
	virtual void setFromChromosome(vector<bool>::const_iterator from, vector<bool>::const_iterator to) = 0;

	///@return reuqired size of chromosome.
	///ATTENTION! Value returned by this function must be constant during execution.
	virtual size_t getChromosomeSize() const = 0;
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* ICONVERTABLETOCHROMOSOME_H_ */
