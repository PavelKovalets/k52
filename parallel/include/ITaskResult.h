/*
 * TaskResult.h
 *
 *  Created on: Oct 14, 2012
 *      Author: pavel
 */

#ifndef TASKRESULT_H_
#define TASKRESULT_H_

#include <boost/shared_ptr.hpp>

namespace k52
{
namespace parallel
{

class ITaskResult
{
public:
	typedef boost::shared_ptr<ITaskResult> shared_ptr;

	virtual ~ITaskResult() {}
};

} /* namespace parallel */
} /* namespace k52 */
#endif /* TASKRESULT_H_ */
