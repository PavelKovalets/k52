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
#include "WorkerStatistics.h"
#include "IMpiTask.h"
#include "IMpiTask.h"
#include "BoostDeclaration.h"
#include "../IWorkerPool.h"

namespace k52
{
	namespace parallel
	{
		namespace mpi
		{
			class MpiWorkerPool : public IWorkerPool
			{
			public:
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
				IMpiTask::shared_ptr createTask(std::string taskId);

				MpiWorkerPool(const MpiWorkerPool&);
				MpiWorkerPool& operator = (const MpiWorkerPool&);
			};
		}
	}
}
#endif /* MPIWORKERPOOL_H_ */
