/*
 * IWorkerPool.h
 *
 *  Created on: Mar 1, 2013
 *      Author: feanor
 */

#ifndef IWORKERPOOL_H_
#define IWORKERPOOL_H_

#include <parallel/ITask.h>
#include <parallel/ITaskResult.h>
#include <parallel/WorkerStatistics.h>
#include <vector>

namespace k52
{
namespace parallel
{

class IWorkerPool
{
public:
	typedef boost::shared_ptr<IWorkerPool> shared_ptr;

	virtual ~IWorkerPool(){}

	virtual std::vector< WorkerStatistics > getStatistics() = 0;

	virtual std::vector< ITaskResult::shared_ptr > doTasks (const std::vector<const ITask*>& tasks) = 0;
};

} /* parallel */
} /* k52 */
#endif /* IWORKERPOOL_H_ */
