#ifndef ITASK_H_
#define ITASK_H_

#include <boost/shared_ptr.hpp>
#include <k52/common/i_cloneable.h>
#include <k52/parallel/i_task_result.h>

namespace k52
{
namespace parallel
{

class ITask
{
public:
    typedef boost::shared_ptr<ITask> shared_ptr;

    virtual ~ITask() {}

    ///Performs task and creates its result with resource allocation.
    ///One calling this method MUST delete the result after usage or
    ///the result could be wrapped into shared_ptr.
    ///In derived classes returned type SHOULD be changed
    ///to corresponding ITaskResult subclasse's type, for example
    ///@code
    ///class NewTaskClass : public ITask
    ///{
    ///public:
    ///    virtual NewTaskResultClass* Perform() = 0;
    ///};
    ///@endcode
    ///@return result of the performed task
    virtual ITaskResult* Perform() const = 0;
};

} /* namespace parallel */
} /* namespace k52 */

#endif /* ITASK_H_ */
