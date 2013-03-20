/*
 * IMpiTask.h
 *
 *  Created on: Mar 3, 2013
 *      Author: feanor
 */

#ifndef IMPITASK_H_
#define IMPITASK_H_

#include <parallel/i_task.h>
#include <parallel/mpi/ITransferable.h>
#include <parallel/mpi/IMpiTaskResult.h>

namespace k52
{
namespace parallel
{
namespace mpi
{

class IMpiTask : public k52::parallel::ITask, public k52::common::ICloneable, public ITransferable
{
public:
	typedef boost::shared_ptr<IMpiTask> shared_ptr;

	//TODO is it correct solving of contrvariant return problem
	virtual ITaskResult::shared_ptr Perform() const
	{
		return performMpi();
	}

	virtual IMpiTaskResult::shared_ptr performMpi() const = 0;

	virtual IMpiTaskResult::shared_ptr createEmptyResult() const = 0;

	virtual IMpiTask* Clone() const = 0;

	virtual void send(boost::mpi::communicator* communicator, int target) const = 0;

	virtual void receive(boost::mpi::communicator* communicator) = 0;
};

} /* namespace mpi */
} /* namespace parallel */
} /* namespace k52 */

#endif /* IMPITASK_H_ */
