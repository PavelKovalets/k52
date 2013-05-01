#ifndef ICLONEABLE_H_
#define ICLONEABLE_H_

#include <boost/shared_ptr.hpp>

#include <k52/common/disallow_copy_and_assign.h>

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
    typedef boost::shared_ptr<ICloneable> shared_ptr;

    ///Default counstructor should be explicitelly defined if DISALLOW_COPY_AND_ASSIGN used
    ICloneable() {}

    ///Virtual destructor for correct deallocation of resources in derived classes
    virtual ~ICloneable() {}

    ///Creates deep clone of an object with resource allocation.
    ///One calling this method MUST delete the clone after usage or
    ///the clone could be wrapped into shared_ptr.
    ///In derived classes returned type SHOULD be changed to subclasse's type, for example
    ///@code
    ///class NewClonableClass : public ICloneable
    ///{
    ///public:
    ///    virtual NewClonableClass* Clone() = 0;
    ///};
    ///@endcode
    ///@return deep clone of an object
    virtual ICloneable* Clone() const = 0;

private:
    DISALLOW_COPY_AND_ASSIGN(ICloneable);
};

};/* namespace common */
};/* namespace k52 */

#endif /* ICLONEABLE_H_ */
