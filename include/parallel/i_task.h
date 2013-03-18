#ifndef ITASK_H_
#define ITASK_H_

#include <boost/shared_ptr.hpp>
#include <common/i_cloneable.h>
#include <parallel/i_task_result.h>

namespace k52
{
namespace parallel
{

class ITask
{
public:
    typedef boost::shared_ptr<ITask> shared_ptr;

    virtual ~ITask() {}

    virtual ITaskResult::shared_ptr Perform() const = 0;
};

} /* namespace parallel */
} /* namespace k52 */

#endif /* ITASK_H_ */
