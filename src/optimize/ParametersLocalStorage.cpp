/*
 * ParametersLocalStorage.cpp
 *
 *  Created on: Mar 25, 2012
 *      Author: feanor
 */

#include <optimize/ParametersLocalStorage.h>

ParametersLocalStorage::ParametersLocalStorage(const IParameters *const parameters)
	: CloneableObjectLocalStorage(parameters)
{
}

ParametersLocalStorage::ParametersLocalStorage(const ParametersLocalStorage & a)
	: CloneableObjectLocalStorage(a)
{
}

ParametersLocalStorage::ParametersLocalStorage()
	: CloneableObjectLocalStorage()
{
}

ParametersLocalStorage& ParametersLocalStorage::operator =(const ParametersLocalStorage & a)
{
	return (ParametersLocalStorage& ) this->CloneableObjectLocalStorage::operator =(a);
}

const IParameters* ParametersLocalStorage::getLocalParameters() const
{
	return (const IParameters *const) this->getLocalCloneableObject();
}

IParameters* ParametersLocalStorage::getCloneableObjectAsParameters()
{
	return (IParameters *)_localCloneableObject;
}


