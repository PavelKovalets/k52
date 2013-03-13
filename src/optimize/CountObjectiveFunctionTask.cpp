/*
 * CountFitnessTask.cpp
 *
 *  Created on: Mar 11, 2012
 *      Author: feanor
 */

#include "CountObjectiveFunctionTask.h"
#include "ObjectiveFunctionTaskResult.h"

#ifdef BUILD_WITH_MPI

#include <boost/mpi.hpp>
#include <parallel/mpi/Constants.h>
#include <parallel/mpi/IdentifyableObjectsManager.h>

k52::parallel::mpi::IMpiTaskResult::shared_ptr CountObjectiveFunctionTask::createEmptyResult() const
{
	return ObjectiveFunctionTaskResult::shared_ptr ( new ObjectiveFunctionTaskResult() );
}

k52::parallel::mpi::IMpiTaskResult::shared_ptr CountObjectiveFunctionTask::performMpi() const
{
	double value = _functionToOptimize->operator ()(_parameters);
	ObjectiveFunctionTaskResult::shared_ptr result ( new ObjectiveFunctionTaskResult() );
	result->setObjectiveFunctionValue(value);
	return result;
}

CountObjectiveFunctionTask* CountObjectiveFunctionTask::clone() const
{
	CountObjectiveFunctionTask* clone = new CountObjectiveFunctionTask(_parameters, _functionToOptimize);

	//TODO WRITE VALUE TO DOES NOT GET CLONED - REFACTOR THIS APPROACH (2 separate classes for threads and MPI)
	//or not to use cloning for MPI?

	return clone;
}

void CountObjectiveFunctionTask::send(boost::mpi::communicator* communicator, int target) const
{
	communicator->send(target, k52::parallel::mpi::Constants::CommonTag, k52::parallel::mpi::IdentifyableObjectsManager::getId(_functionToOptimize));
	communicator->send(target, k52::parallel::mpi::Constants::CommonTag, k52::parallel::mpi::IdentifyableObjectsManager::getId(_parameters));
	_parameters->send(communicator, target);
}

void CountObjectiveFunctionTask::receive(boost::mpi::communicator* communicator)
{
	std::string objectiveFunctionId;
	communicator->recv(k52::parallel::mpi::Constants::ServerRank, k52::parallel::mpi::Constants::CommonTag, objectiveFunctionId);
	_functionToOptimize = dynamic_cast<const IObjectiveFunction*>( k52::parallel::mpi::IdentifyableObjectsManager::Instance().getObject(objectiveFunctionId) );

	std::string parametersId;
	communicator->recv(k52::parallel::mpi::Constants::ServerRank, k52::parallel::mpi::Constants::CommonTag, parametersId);
	const k52::common::ICloneable* templateParameters = k52::parallel::mpi::IdentifyableObjectsManager::Instance().getObject(parametersId);

	//TODO memory LEEK HERE!!!
	IParameters* parameters = dynamic_cast<IParameters*>( templateParameters->clone() );
	parameters->receive(communicator);
	_parameters = parameters;
}
#else

//TODO use polymorphysm
k52::parallel::ITaskResult::shared_ptr CountObjectiveFunctionTask::perform() const
{
	double value = _functionToOptimize->operator ()(_parameters);
	ObjectiveFunctionTaskResult::shared_ptr result ( new ObjectiveFunctionTaskResult() );
	result->setObjectiveFunctionValue(value);
	return result;
}

#endif

CountObjectiveFunctionTask::CountObjectiveFunctionTask(): _parameters(NULL) {}

CountObjectiveFunctionTask::CountObjectiveFunctionTask(
		const IParameters*  parameters,
		const IObjectiveFunction* functionToOptimize)
			: _parameters(parameters), _functionToOptimize(functionToOptimize) {}
