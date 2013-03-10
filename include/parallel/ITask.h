/*
 * ITask.h
 *
 *  Created on: Oct 14, 2012
 *      Author: pavel
 */

#ifndef ITASK_H_
#define ITASK_H_

#include <common/ICloneable.h>
#include <parallel/ITaskResult.h>
#include <boost/shared_ptr.hpp>

namespace k52
{
namespace parallel
{

class ITask
{
public:
	typedef boost::shared_ptr<ITask> shared_ptr;

	virtual ~ITask() {}

	virtual ITaskResult::shared_ptr perform() const = 0;
};

} /* namespace parallel */
} /* namespace k52 */

#endif /* ITASK_H_ */
