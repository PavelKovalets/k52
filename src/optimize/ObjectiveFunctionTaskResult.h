/*
 * ObjectiveFunctionTaskResult.h
 *
 *  Created on: Oct 14, 2012
 *      Author: pavel
 */

#ifndef OBJECTIVEFUNCTIONTASKRESULT_H_
#define OBJECTIVEFUNCTIONTASKRESULT_H_

#include <parallel/ITaskResult.h>

#ifdef BUILD_WITH_MPI
#include <parallel/mpi/IMpiTaskResult.h>
#endif

namespace k52
{
namespace optimize
{

class ObjectiveFunctionTaskResult: 

#ifdef BUILD_WITH_MPI
	public k52::parallel::mpi::IMpiTaskResult
#else
	public k52::parallel::ITaskResult
#endif
{
public:
	typedef boost::shared_ptr<ObjectiveFunctionTaskResult> shared_ptr;

	virtual ~ObjectiveFunctionTaskResult() {}

#ifdef BUILD_WITH_MPI

	virtual boost::mpi::request ireceive(boost::mpi::communicator* communicator, int source);

	virtual void send(boost::mpi::communicator* communicator);

#endif

	double getObjectiveFunctionValue() const;

	void setObjectiveFunctionValue(double objectiveFunctionValue);

private:
	double _objectiveFunctionValue;
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* OBJECTIVEFUNCTIONTASKRESULT_H_ */
