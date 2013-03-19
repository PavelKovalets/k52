/*
 * CompositeDiscreteParameters.h
 *
 *  Created on: Apr 22, 2012
 *      Author: feanor
 */

#ifndef COMPOSITEDISCRETEPARAMETERS_H_
#define COMPOSITEDISCRETEPARAMETERS_H_

#include "ConstChromosomeSizeParemeters.h"
#include <optimize/InitializationChecker.h>
#include <vector>

namespace k52
{
namespace optimize
{

class DiscreteParametersLocalStorage;

class CompositeDiscreteParameters: public ConstChromosomeSizeParemeters
{
public:
	typedef boost::shared_ptr<CompositeDiscreteParameters> shared_ptr;

	void initialize(std::vector<IDiscreteParameters::shared_ptr> parameters);

	size_t getNumberOfParameters() const;

	const IDiscreteParameters::shared_ptr getParameter(size_t index) const;

	CompositeDiscreteParameters* Clone() const;

	bool checkConstraints() const;

	void SetChromosome(std::vector<bool>::iterator from, std::vector<bool>::iterator to) const;

	void SetFromChromosome(std::vector<bool>::const_iterator from, std::vector<bool>::const_iterator to);

private:
	size_t countTotalChromosomeSize() const;

	std::vector<IDiscreteParameters::shared_ptr> _parametersSet;

	InitializationChecker _initializationChecker;
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* COMPOSITEDISCRETEPARAMETERS_H_ */
