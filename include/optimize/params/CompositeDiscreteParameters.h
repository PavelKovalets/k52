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
#include <optimize/DiscreteParametersLocalStorage.h>
#include <vector>

class DiscreteParametersLocalStorage;

class CompositeDiscreteParameters: public ConstChromosomeSizeParemeters
{
public:
	void initialize(vector<const IDiscreteParameters*> parameters);

	size_t getNumberOfParameters() const;

	const IDiscreteParameters* getParameter(size_t index) const;

	CompositeDiscreteParameters* clone() const;

	bool checkConstraints() const;

	void setChromosome(vector<bool>::iterator from, vector<bool>::iterator to) const;

	void setFromChromosome(vector<bool>::const_iterator from, vector<bool>::const_iterator to);

private:
	size_t countTotalChromosomeSize() const;

	vector<DiscreteParametersLocalStorage> _parametersSet;

	InitializationChecker _initializationChecker;
};

#endif /* COMPOSITEDISCRETEPARAMETERS_H_ */
