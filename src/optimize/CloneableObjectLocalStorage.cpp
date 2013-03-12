/*
 * CloneableObjectLocalStorage.cpp
 *
 *  Created on: Mar 11, 2012
 *      Author: feanor
 */

#include <optimize/CloneableObjectLocalStorage.h>
#include <cstddef>

const k52::common::ICloneable* const CloneableObjectLocalStorage::getLocalCloneableObject() const
{
	return _localCloneableObject;
}

CloneableObjectLocalStorage::CloneableObjectLocalStorage()
{
	_localCloneableObject = NULL;
}

CloneableObjectLocalStorage::CloneableObjectLocalStorage(const k52::common::ICloneable* const parameters)
{
	if(parameters != NULL)
	{
		_localCloneableObject = parameters->clone();
	}
	else
	{
		_localCloneableObject = NULL;
	}
}

CloneableObjectLocalStorage::CloneableObjectLocalStorage(const CloneableObjectLocalStorage& a)
{
	_localCloneableObject = NULL;
	*this = a;
}

CloneableObjectLocalStorage& CloneableObjectLocalStorage::operator=(const CloneableObjectLocalStorage & a)
{
	if (this != &a) // protect against invalid self-assignment
	{
		if(a._localCloneableObject == NULL)
		{
			_localCloneableObject = NULL;
			return *this;
		}

		// 1: allocate new memory and copy the elements
		k52::common::ICloneable* newParametrs = a._localCloneableObject->clone();

		// 2: deallocate old memory
		if(_localCloneableObject!=NULL)
		{
			delete _localCloneableObject;
		}

		// 3: assign the new memory to the object
		_localCloneableObject = newParametrs;
	}
	// by convention, always return *this
	return *this;
}

CloneableObjectLocalStorage::~CloneableObjectLocalStorage()
{
	if(_localCloneableObject!=NULL)
	{
		delete _localCloneableObject;
	}
}

