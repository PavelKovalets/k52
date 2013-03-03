/*
 * IMpiTask.h
 *
 *  Created on: Mar 3, 2013
 *      Author: feanor
 */

#ifndef IMPITASK_H_
#define IMPITASK_H_

#include "../ITask.h"
#include "ITransferable.h"
#include "IMpiTaskResult.h"

namespace k52
{
	namespace parallel
	{
		namespace mpi
		{

			class IMpiTask : public k52::parallel::ITask, public k52::common::ICloneable, public ITransferable
			{
			public:

				//TODO is it correct solving of contrvariant return problem
				virtual boost::shared_ptr<ITaskResult> perform() const
				{
					return performMpi();
				}

				virtual boost::shared_ptr<IMpiTaskResult> performMpi() const = 0;

				virtual boost::shared_ptr<IMpiTaskResult> createEmptyResult() const = 0;

				virtual IMpiTask* clone() const = 0;

				virtual void send(boost::mpi::communicator* communicator, int target) const = 0;

				virtual void receive(boost::mpi::communicator* communicator) = 0;
			};

		}
	}
}
#endif /* IMPITASK_H_ */
