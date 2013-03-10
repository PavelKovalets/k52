/*
 * MpiWorkerPool.cpp
 *
 *  Created on: Sep 30, 2012
 *      Author: pavel
 */

#include <boost/mpi.hpp>
#include <boost/mpi/request.hpp>
#include <boost/serialization/vector.hpp>
#include <list>
#include "MpiWorkerPool.h"
#include <parallel/mpi/Constants.h>
#include <parallel/mpi/IdentifyableObjectsManager.h>

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

ResultExpectation waitAndPopNextExpectation(std::list<ResultExpectation>& resultExpectations)
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
		_communicator->send(i, Constants::CommonTag, Constants::EndOfWorkTaskId);
	}

	_wasFinalized = true;
}

std::vector< WorkerStatistics > MpiWorkerPool::getStatistics()
{
	if(_wasFinalized)
	{
		throw std::logic_error("Statistics cannot be acquired after workers finalization.");
	}

	checkIfServer();

	std::vector< WorkerStatistics > statistics( _communicator->size() - 1 );

	for(int i=1; i<_communicator->size(); i++)
	{
		_communicator->send(i, Constants::CommonTag, Constants::GetStatisticsTaskId);
		_communicator->recv(i, Constants::CommonTag, statistics[i - 1]);
	}

	return statistics;
}

MpiWorkerPool::MpiWorkerPool()
{
	_wasFinalized = false;
	_env = new boost::mpi::environment();
	_communicator = new boost::mpi::communicator();

	std::cerr<<"Rank "<<_communicator->rank()<<" of "<<_communicator->size()<<" starded."<<std::endl;

	if(_communicator->rank() != Constants::ServerRank)
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
		std::string taskId = Constants::EndOfWorkTaskId;

		_communicator->recv(Constants::ServerRank, Constants::CommonTag, taskId);

		if(taskId == Constants::GetStatisticsTaskId)
		{
			WorkerStatistics statistics(counted, errors, _communicator->rank());
			_communicator->send(Constants::ServerRank, Constants::CommonTag, statistics);
			continue;
		}

		if(taskId == Constants::EndOfWorkTaskId)
		{
			clean();
			exit(0);
		}

		counted++;

		IMpiTask::shared_ptr nextTask = createTask(taskId);

		nextTask->receive(_communicator);

		IMpiTaskResult::shared_ptr result = nextTask->performMpi();

		result->send(_communicator);
	}
}


IMpiTask::shared_ptr MpiWorkerPool::createTask(std::string taskId)
{
	const IMpiTask* task = dynamic_cast<const IMpiTask*>(IdentifyableObjectsManager::Instance().getObject(taskId));

	if(task == NULL)
	{
		std::stringstream message;
		message << "Object with id " << taskId << " was registered "
				"but is not derived from ITask .";

		throw std::invalid_argument(message.str());
	}

	return IMpiTask::shared_ptr( task->clone() );
}

ResultExpectation MpiWorkerPool::sendTask(const IMpiTask* task, int currentWorkerRank, ITaskResult::shared_ptr* resultToSet)
{
	_communicator->send(currentWorkerRank, Constants::CommonTag, IdentifyableObjectsManager::getId(task));
	task->send(_communicator, currentWorkerRank);

	IMpiTaskResult::shared_ptr mpiTaskResult = task->createEmptyResult();
	(*resultToSet) = mpiTaskResult;

	ResultExpectation expectaton;
	expectaton.request = mpiTaskResult->ireceive(_communicator, currentWorkerRank);
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

std::vector< ITaskResult::shared_ptr > MpiWorkerPool::doTasks (const std::vector<const ITask*>& tasks)
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
	if(_communicator->rank() != Constants::ServerRank)
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


