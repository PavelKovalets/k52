/*
 * ContinuousParametersLocalStorage.h
 *
 *  Created on: May 20, 2012
 *      Author: feanor
 */

#ifndef CONTINUOUSPARAMETERSLOCALSTORAGE_H_
#define CONTINUOUSPARAMETERSLOCALSTORAGE_H_

#include <optimize/ParametersLocalStorage.h>
#include <optimize/params/IContinuousParameters.h>

class ContinuousParametersLocalStorage: public ParametersLocalStorage
{
public:
	ContinuousParametersLocalStorage(const IContinuousParameters* const parameters);

	ContinuousParametersLocalStorage(const ContinuousParametersLocalStorage& a);

	ContinuousParametersLocalStorage();

	virtual const IContinuousParameters* getLocalParameters() const;
};

#endif /* CONTINUOUSPARAMETERSLOCALSTORAGE_H_ */
