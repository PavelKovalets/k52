/*
 * DiscreteParametersLocalStorage.h
 *
 *  Created on: May 20, 2012
 *      Author: feanor
 */

#ifndef DISCRETEPARAMETERSLOCALSTORAGE_H_
#define DISCRETEPARAMETERSLOCALSTORAGE_H_

#include <optimize/ParametersLocalStorage.h>
#include <optimize/params/IDiscreteParameters.h>

class DiscreteParametersLocalStorage: public IConvertableToChromosome, public ParametersLocalStorage
{
public:
	DiscreteParametersLocalStorage(const IDiscreteParameters* const parameters);

	DiscreteParametersLocalStorage(const DiscreteParametersLocalStorage& a);

	DiscreteParametersLocalStorage();

	void setChromosome(vector<bool>::iterator from, vector<bool>::iterator to) const;

	void setFromChromosome(vector<bool>::const_iterator from, vector<bool>::const_iterator to);

	size_t getChromosomeSize() const;

	virtual const IDiscreteParameters* getLocalParameters() const;

protected:
	virtual IDiscreteParameters* getCloneableObjectAsParameters();
};

#endif /* DISCRETEPARAMETERSLOCALSTORAGE_H_ */
