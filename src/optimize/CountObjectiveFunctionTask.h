/*
 * CountObjectiveFunctionTask.h
 *
 *  Created on: Mar 11, 2012
 *      Author: feanor
 */

#ifndef COUNTOBJECTIVEFUNCTIONTASK_H_
#define COUNTOBJECTIVEFUNCTIONTASK_H_

#include <string>
#include <boost/shared_ptr.hpp>
#include <optimize/IObjectiveFunction.h>
#include <parallel/ITask.h>

#include <common/disallow_copy_and_assign.h>

#ifdef BUILD_WITH_MPI
#include <parallel/mpi/IMpiTask.h>
#include <parallel/mpi/IMpiTaskResult.h>
#endif

namespace k52
{
namespace optimize
{

class CountObjectiveFunctionTask
#ifdef BUILD_WITH_MPI
	: public k52::parallel::mpi::IMpiTask
#else
	: public k52::parallel::ITask
#endif
{
public:
	typedef boost::shared_ptr<CountObjectiveFunctionTask> shared_ptr;

	CountObjectiveFunctionTask();

	CountObjectiveFunctionTask(const IParameters* parameters,
			const IObjectiveFunction* functionToOptimize);

#ifdef BUILD_WITH_MPI

	virtual k52::parallel::mpi::IMpiTaskResult::shared_ptr performMpi() const;

	virtual k52::parallel::mpi::IMpiTaskResult::shared_ptr createEmptyResult() const;

	virtual CountObjectiveFunctionTask* clone() const;

	virtual void send(boost::mpi::communicator* communicator, int target) const;

	virtual void receive(boost::mpi::communicator* communicator);

#else

	k52::parallel::ITaskResult::shared_ptr perform() const;

#endif

protected:
	const IObjectiveFunction* getFunction() const;
	const IParameters* getParameters() const;

private:
	//TODO are functors thread-safe not to copy locally them?
	const IObjectiveFunction* const _functionToOptimize;
	const IParameters* const  _parameters;

	//Indicates if task was created at once - so const pointers to be used
	//Otherwise it is received - so shared_ptr's should be used
	bool _wasCreated;

	IParameters::shared_ptr _receivedParameters;
	IObjectiveFunction::shared_ptr _receivedFunction;

	DISALLOW_COPY_AND_ASSIGN(CountObjectiveFunctionTask);
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* COUNTOBJECTIVEFUNCTIONTASK_H_ */
