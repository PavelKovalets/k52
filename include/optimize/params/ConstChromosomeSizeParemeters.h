/*
 * ConstChromosomeSizeParemeters.h
 *
 *  Created on: Apr 14, 2012
 *      Author: feanor
 */

#ifndef CONSTCHROMOSOMESIZEPAREMETERS_H_
#define CONSTCHROMOSOMESIZEPAREMETERS_H_

#include "DiscreteParameters.h"

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
	///@param chromosomeSize
	void setConstChromosomeSize(size_t chromosomeSize);

	///Checks for chromosome size to remain const since it was set.
	///Usually must be call on every usage of setFromChromosome method.
	///If chromosomeSize was changed or was not set throws an exception.
	void checkForConstChromosomeSize(size_t chromosomeSize) const;

private:

	void checkIfChromosomeWasSet() const;
	bool _wasChromosomeSizeSet;
	size_t _chromosomeSize;
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* CONSTCHROMOSOMESIZEPAREMETERS_H_ */
