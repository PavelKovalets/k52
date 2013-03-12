/*
 * ObjectiveFunctionTaskResult.h
 *
 *  Created on: Oct 14, 2012
 *      Author: pavel
 */

#ifndef OBJECTIVEFUNCTIONTASKRESULT_H_
#define OBJECTIVEFUNCTIONTASKRESULT_H_

#ifdef BUILD_WITH_MPI

#include <parallel/mpi/IMpiTaskResult.h>

class ObjectiveFunctionTaskResult: public k52::parallel::mpi::IMpiTaskResult
{
public:
	typedef boost::shared_ptr<ObjectiveFunctionTaskResult> shared_ptr;

	virtual ~ObjectiveFunctionTaskResult() {}

	virtual boost::mpi::request ireceive(boost::mpi::communicator* communicator, int source);

	virtual void send(boost::mpi::communicator* communicator);

	double getObjectiveFunctionValue() const;

	void setObjectiveFunctionValue(double objectiveFunctionValue);

private:
	double _objectiveFunctionValue;
};

#endif

#endif /* OBJECTIVEFUNCTIONTASKRESULT_H_ */
