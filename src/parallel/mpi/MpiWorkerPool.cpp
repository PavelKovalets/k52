/*
 * MpiWorkerPool.cpp
 *
 *  Created on: Sep 30, 2012
 *      Author: pavel
 */
#ifdef BUILD_WITH_MPI

#include <boost/mpi.hpp>
#include <boost/mpi/request.hpp>
#include <boost/serialization/vector.hpp>
#include "MpiWorkerPool.h"
#include <parallel/mpi/constants.h>
#include <parallel/mpi/identifyable_objects_manager.h>

namespace k52
{
namespace parallel
{
namespace mpi
{

struct ResultExpectation
{
	int workerRank;
	boost::mpi::request request;
};

ResultExpectation MpiWorkerPool::waitAndPopNextExpectation(std::list<ResultExpectation>& resultExpectations)
{
	while(true)
	{
		for(std::list<ResultExpectation>::iterator it = resultExpectations.begin();
				it!=resultExpectations.end();
				it++)
		{
			bool received = (*it).request.test();

			if(received)
			{
				ResultExpectation receivedExpectation = *it;
				resultExpectations.erase(it);

				_statisticsAggregator.registerCount(receivedExpectation.workerRank);

				return receivedExpectation;
			}
		}
	}
}

MpiWorkerPool::~MpiWorkerPool()
{
	finalizeWorkers();
	clean();
}

void MpiWorkerPool::finalizeWorkers()
{
	checkIfServer();

	for(int i=1; i<_communicator->size(); i++)
	{
		_communicator->send(i, constants::kCommonTag, constants::kEndOfWorkTaskId);
	}

	_wasFinalized = true;
}

MpiWorkerPool::MpiWorkerPool()
{
	_wasFinalized = false;
	_env = new boost::mpi::environment();
	_communicator = new boost::mpi::communicator();

	std::cerr<<"Rank "<<_communicator->rank()<<" of "<<_communicator->size()<<" starded."<<std::endl;

	if(_communicator->rank() != constants::kServerRank)
		//Worker Logic
	{
		runWorkerLoop();
	}
}

void MpiWorkerPool::runWorkerLoop()
{
	int counted = 0;
	int errors = 0;

	while(true)
	{
		std::string taskId = constants::kEndOfWorkTaskId;

		_communicator->recv(constants::kServerRank, constants::kCommonTag, taskId);

		if(taskId == constants::kEndOfWorkTaskId)
		{
			clean();
			exit(0);
		}

		counted++;

		IMpiTask::shared_ptr nextTask = createTask(taskId);

		nextTask->Receive(_communicator);

		IMpiTaskResult::shared_ptr result = nextTask->PerformMpi();

		result->Send(_communicator);
	}
}

std::vector< WorkerStatistics > MpiWorkerPool::GetStatistics()
{
	return _statisticsAggregator.getStatistics();
}

IMpiTask::shared_ptr MpiWorkerPool::createTask(std::string taskId)
{
	const IMpiTask* task = dynamic_cast<const IMpiTask*>(IdentifyableObjectsManager::Instance().GetObject(taskId));

	if(task == NULL)
	{
		std::stringstream message;
		message << "Object with id " << taskId << " was registered "
				"but is not derived from ITask .";

		throw std::invalid_argument(message.str());
	}

	return IMpiTask::shared_ptr( task->Clone() );
}

ResultExpectation MpiWorkerPool::sendTask(const IMpiTask* task, int currentWorkerRank, ITaskResult::shared_ptr* resultToSet)
{
	_communicator->send(currentWorkerRank, constants::kCommonTag, IdentifyableObjectsManager::GetId(*task));
	task->Send(_communicator, currentWorkerRank);

	IMpiTaskResult::shared_ptr mpiTaskResult = task->CreateEmptyResult();
	(*resultToSet) = mpiTaskResult;

	ResultExpectation expectaton;
	expectaton.request = mpiTaskResult->ReceiveAsync(_communicator, currentWorkerRank);
	expectaton.workerRank = currentWorkerRank;

	return expectaton;
}

const IMpiTask* MpiWorkerPool::getMpiTask(const ITask* task)
{
	const IMpiTask* mpiTask = dynamic_cast<const IMpiTask*>( task );

	if(mpiTask == NULL)
	{
		throw std::logic_error("MpiWorkerPool can process only IMpiTask, not simple ITask.");
	}

	return mpiTask;
}

std::vector< ITaskResult::shared_ptr > MpiWorkerPool::DoTasks (const std::vector<const ITask*>& tasks)
{
	checkIfServer();
	checkAwailableWorkers();

	int currentWorkerRank = 1;
	bool wasFirstPartSent = false;

	std::list<ResultExpectation> resultExpectations;
	std::vector< ITaskResult::shared_ptr > results(tasks.size());

	for(size_t i = 0; i < tasks.size(); i++)
	{
		const IMpiTask* currentTask = getMpiTask(tasks[i]);

		ResultExpectation taskExpectation = sendTask(currentTask, currentWorkerRank, &(results[i]));

		resultExpectations.push_back( taskExpectation );

		if(!wasFirstPartSent)
		{
			currentWorkerRank ++;
			if(currentWorkerRank >= _communicator->size())
			{
				wasFirstPartSent = true;
			}
		}

		if(wasFirstPartSent)
		{
			ResultExpectation receivedExpectation = waitAndPopNextExpectation(resultExpectations);
			currentWorkerRank = receivedExpectation.workerRank;
		}
	}

	//receiving last tasks
	while(!resultExpectations.empty())
	{
		waitAndPopNextExpectation(resultExpectations);
	}

	return results;
}

void MpiWorkerPool::clean()
{
	if(_communicator != NULL)
	{
		delete _communicator;
		_communicator = NULL;
	}

	if(_env != NULL)
	{
		delete _env;
		_env = NULL;
	}
}

void MpiWorkerPool::checkAwailableWorkers()
{
	if(_communicator->size() < 2)
	{
		throw std::runtime_error("No worker threads available. "
				"Try to run program like following example: "
				"\'mpirun -np x ./MyExeName\' where x > 1.");
	}
}

void MpiWorkerPool::checkIfServer()
{
	if(_communicator->rank() != constants::kServerRank)
	{
		std::stringstream message;
		message << "Critical error on " << _communicator->rank() << " node. "
				"Requested action that requires server node status.";

		throw std::logic_error(message.str());
	}
}

} /* namespace mpi */
} /* namespace parallel */
} /* namespace k52 */

#endif
