/*
 * MpiWorkerPool.h
 *
 *  Created on: Sep 30, 2012
 *      Author: pavel
 */

#ifndef MPIWORKERPOOL_H_
#define MPIWORKERPOOL_H_

#include <vector>
#include <boost/shared_ptr.hpp>
#include <parallel/mpi/WorkerStatistics.h>
#include <parallel/mpi/IMpiTask.h>
#include <parallel/mpi/IMpiTask.h>
#include <parallel/mpi/BoostDeclaration.h>
#include <parallel/IWorkerPool.h>

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
	std::vector< WorkerStatistics > getStatistics();

private:
	boost::mpi::environment* _env;
	boost::mpi::communicator* _communicator;
	bool _wasFinalized;

	void finalizeWorkers();
	void clean();
	void checkIfServer();
	void checkAwailableWorkers();
	void runWorkerLoop();
	const IMpiTask* getMpiTask(const ITask* task);
	ResultExpectation sendTask(const IMpiTask* task, int currentWorkerRank, ITaskResult::shared_ptr* resultToSet);
	IMpiTask::shared_ptr createTask(std::string taskId);

	MpiWorkerPool(const MpiWorkerPool&);
	MpiWorkerPool& operator = (const MpiWorkerPool&);
};

} /* namespace mpi */
} /* namespace parallel */
} /* namespace k52 */

#endif /* MPIWORKERPOOL_H_ */
