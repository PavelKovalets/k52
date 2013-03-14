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
namespace params
{

class DiscreteParametersLocalStorage;

class CompositeDiscreteParameters: public ConstChromosomeSizeParemeters
{
public:
	typedef boost::shared_ptr<CompositeDiscreteParameters> shared_ptr;

	void initialize(vector<IDiscreteParameters::shared_ptr> parameters);

	size_t getNumberOfParameters() const;

	const IDiscreteParameters::shared_ptr getParameter(size_t index) const;

	CompositeDiscreteParameters* clone() const;

	bool checkConstraints() const;

	void setChromosome(vector<bool>::iterator from, vector<bool>::iterator to) const;

	void setFromChromosome(vector<bool>::const_iterator from, vector<bool>::const_iterator to);

private:
	size_t countTotalChromosomeSize() const;

	vector<IDiscreteParameters::shared_ptr> _parametersSet;

	InitializationChecker _initializationChecker;
};

}/* namespace params */
}/* namespace optimize */
}/* namespace k52 */

#endif /* COMPOSITEDISCRETEPARAMETERS_H_ */
