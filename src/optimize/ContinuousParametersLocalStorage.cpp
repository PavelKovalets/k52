/*
 * ContinuousParametersLocalStorage.cpp
 *
 *  Created on: May 20, 2012
 *      Author: feanor
 */

#include <optimize/ContinuousParametersLocalStorage.h>

ContinuousParametersLocalStorage::ContinuousParametersLocalStorage(const IContinuousParameters* const parameters)
	: ParametersLocalStorage(parameters)
{
}

ContinuousParametersLocalStorage::ContinuousParametersLocalStorage(const ContinuousParametersLocalStorage & a)
	: ParametersLocalStorage(a)
{
}

ContinuousParametersLocalStorage::ContinuousParametersLocalStorage()
	: ParametersLocalStorage()
{
}

const IContinuousParameters* ContinuousParametersLocalStorage::getLocalParameters() const
{
	return (const IContinuousParameters *const) this->getLocalCloneableObject();
}

