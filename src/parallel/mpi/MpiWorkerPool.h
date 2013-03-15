/*
 * MpiWorkerPool.h
 *
 *  Created on: Sep 30, 2012
 *      Author: pavel
 */

#ifndef MPIWORKERPOOL_H_
#define MPIWORKERPOOL_H_

#include <vector>
#include <list>
#include <boost/shared_ptr.hpp>
#include <parallel/mpi/IMpiTask.h>
#include <parallel/mpi/IMpiTask.h>
#include <parallel/mpi/boost_mpi_declaration.h>
#include <parallel/IWorkerPool.h>

#include "../StatisticsAggregator.h"

#include <common/disallow_copy_and_assign.h>

namespace k52
{
namespace parallel
{
namespace mpi
{

struct ResultExpectation;

class MpiWorkerPool : public IWorkerPool
{
public:
	typedef boost::shared_ptr<MpiWorkerPool> shared_ptr;

	MpiWorkerPool();
	~MpiWorkerPool();

	virtual std::vector< ITaskResult::shared_ptr > doTasks (const std::vector<const ITask*>& tasks);
	virtual std::vector< WorkerStatistics > getStatistics();

private:
	boost::mpi::environment* _env;
	boost::mpi::communicator* _communicator;
	bool _wasFinalized;
	StatisticsAggregator _statisticsAggregator;

	void finalizeWorkers();
	void clean();
	void checkIfServer();
	void checkAwailableWorkers();
	void runWorkerLoop();
	const IMpiTask* getMpiTask(const ITask* task);
	ResultExpectation sendTask(const IMpiTask* task, int currentWorkerRank, ITaskResult::shared_ptr* resultToSet);
	ResultExpectation waitAndPopNextExpectation(std::list<ResultExpectation>& resultExpectations);
	IMpiTask::shared_ptr createTask(std::string taskId);

	DISALLOW_COPY_AND_ASSIGN(MpiWorkerPool);
};

} /* namespace mpi */
} /* namespace parallel */
} /* namespace k52 */

#endif /* MPIWORKERPOOL_H_ */
