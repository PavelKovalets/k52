/*
 * CloneableObjectLocalStorage.h
 *
 *  Created on: Mar 11, 2012
 *      Author: feanor
 */

#ifndef CLONEABLEOBJECTLOCALSTORAGE_H_
#define CLONEABLEOBJECTLOCALSTORAGE_H_

#include <common/ICloneable.h>

class CloneableObjectLocalStorage
{
public:
	CloneableObjectLocalStorage(const k52::common::ICloneable* const cloneableObject);

	CloneableObjectLocalStorage(const CloneableObjectLocalStorage& a);

	CloneableObjectLocalStorage();

	virtual CloneableObjectLocalStorage& operator =(const CloneableObjectLocalStorage& a);

	virtual ~CloneableObjectLocalStorage();

	virtual const k52::common::ICloneable* const getLocalCloneableObject() const;

protected:
	k52::common::ICloneable* _localCloneableObject;
};

#endif /* CLONEABLEOBJECTLOCALSTORAGE_H_ */
