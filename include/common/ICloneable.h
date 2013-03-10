/*
 * ICloneable.h
 *
 *  Created on: Jan 30, 2012
 *      Author: feanor
 */

#ifndef ICLONEABLE_H_
#define ICLONEABLE_H_

namespace k52
{
namespace common
{

/**
@class ICloneable
It's implementation allows deep cloning with resources allocation
*/
class ICloneable
{
public:
	///Virtual destructor for correct deallocation of resources in derived classes
	virtual ~ICloneable() {}

	///Creates deep clone of an object with resource allocation.
	///One calling this method MUST delete clone after usage
	///In derived classes returned type SHOULD be changed to subclasse's type, for example
	///@code
	///class NewClonableClass : public ICloneable
	///{
	///public:
	///    virtual NewClonableClass* clone() = 0;
	///};
	///@endcode
	///@return deep clone of an object
	virtual ICloneable* clone() const = 0;
};

};/* namespace common */
};/* namespace k52 */

#endif /* ICLONEABLE_H_ */
