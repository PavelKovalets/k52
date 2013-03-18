#ifndef ICLONEABLE_H_
#define ICLONEABLE_H_

#include <boost/shared_ptr.hpp>

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

    ///Virtual destructor for correct deallocation of resources in derived classes
    virtual ~ICloneable() {}

    ///Creates deep clone of an object with resource allocation.
    ///One calling this method MUST delete clone after usage
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
};

};/* namespace common */
};/* namespace k52 */

#endif /* ICLONEABLE_H_ */
