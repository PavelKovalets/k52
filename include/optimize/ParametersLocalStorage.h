/*
 * ParametersLocalStorage.h
 *
 *  Created on: Mar 25, 2012
 *      Author: feanor
 */

#ifndef PARAMETERSLOCALSTORAGE_H_
#define PARAMETERSLOCALSTORAGE_H_

#include <optimize/CloneableObjectLocalStorage.h>
#include <optimize/params/IParameters.h>

class ParametersLocalStorage : public CloneableObjectLocalStorage
{
public:
	ParametersLocalStorage(const IParameters* const parameters);

	ParametersLocalStorage(const ParametersLocalStorage& a);

	ParametersLocalStorage();

	virtual ParametersLocalStorage& operator =(const ParametersLocalStorage& a);

	virtual const IParameters* getLocalParameters() const;

protected:
	virtual IParameters* getCloneableObjectAsParameters();
};

#endif /* PARAMETERSLOCALSTORAGE_H_ */
