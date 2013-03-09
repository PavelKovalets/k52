/*
 * IWorkerPool.h
 *
 *  Created on: Mar 1, 2013
 *      Author: feanor
 */

#ifndef IWORKERPOOL_H_
#define IWORKERPOOL_H_

#include "ITask.h"
#include "ITaskResult.h"
#include <vector>

//TODO implement template?
//#include <boost/static_assert.hpp>
//#include <boost/type_traits/is_base_of.hpp>
namespace k52
{
	namespace parallel
	{
		//template<class TTask>
		class IWorkerPool
		{
		public:
			typedef boost::shared_ptr<IWorkerPool> shared_ptr;

			virtual ~IWorkerPool(){}

			virtual std::vector< ITaskResult::shared_ptr > doTasks (const std::vector<const ITask*>& tasks) = 0;

			//If you see an error here that means your TTask does not implement ITask
			//BOOST_STATIC_ASSERT((boost::is_base_of<ITask, TTask>::value));
		};
	}
}
#endif /* IWORKERPOOL_H_ */
