/*
 * IMpiTaskResult.h
 *
 *  Created on: Mar 3, 2013
 *      Author: feanor
 */

#ifndef IMPITASKRESULT_H_
#define IMPITASKRESULT_H_

#include <include/ITaskResult.h>

namespace k52
{
namespace parallel
{
namespace mpi
{

class IMpiTaskResult : public k52::parallel::ITaskResult
{
public:
	typedef boost::shared_ptr<IMpiTaskResult> shared_ptr;

	//TODO return boost::mpi::request? how?
	virtual void ireceive(boost::mpi::communicator* communicator, int source, boost::mpi::request* returnedRequest) = 0;

	virtual void send(boost::mpi::communicator* communicator) = 0;
};

} /* namespace mpi */
} /* namespace parallel */
} /* namespace k52 */

#endif /* IMPITASKRESULT_H_ */
