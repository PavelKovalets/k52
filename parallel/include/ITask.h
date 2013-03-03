/*
 * ITask.h
 *
 *  Created on: Oct 14, 2012
 *      Author: pavel
 */

#ifndef ITASK_H_
#define ITASK_H_

#include "ITaskResult.h"
#include <include/ICloneable.h>
#include <boost/shared_ptr.hpp>

namespace k52
{
	namespace parallel
	{
		class ITask
		{
		public:
			virtual ~ITask() {}

			virtual boost::shared_ptr<ITaskResult> perform() const = 0;
		};

	}
}
#endif /* ITASK_H_ */
