#ifndef SEQUENTIALWORKERPOOL_H_
#define SEQUENTIALWORKERPOOL_H_

#include <parallel/IWorkerPool.h>

namespace k52
{
namespace parallel
{

class SequentialWorkerPool : public IWorkerPool
{
public:
	typedef boost::shared_ptr<SequentialWorkerPool> shared_ptr;

	virtual std::vector< ITaskResult::shared_ptr > doTasks (const std::vector<const ITask*>& tasks);
};

} /* parallel */
} /* k52 */

#endif /* SEQUENTIALWORKERPOOL_H_ */
