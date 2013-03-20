/*
 * ObjectiveFunctionTaskResult.cpp
 *
 *  Created on: Oct 14, 2012
 *      Author: pavel
 */

#include "ObjectiveFunctionTaskResult.h"

#ifdef BUILD_WITH_MPI

#include <boost/mpi.hpp>
#include <parallel/mpi/constants.h>

#endif

namespace k52
{
namespace optimize
{

void ObjectiveFunctionTaskResult::setObjectiveFunctionValue(double objectiveFunctionValue)
{
	_objectiveFunctionValue = objectiveFunctionValue;
}

double ObjectiveFunctionTaskResult::getObjectiveFunctionValue() const
{
	return _objectiveFunctionValue;
}

#ifdef BUILD_WITH_MPI

boost::mpi::request ObjectiveFunctionTaskResult::ireceive(boost::mpi::communicator* communicator, int source)
{
	return communicator->irecv(source, k52::parallel::mpi::constants::kCommonTag, _objectiveFunctionValue);
}

void ObjectiveFunctionTaskResult::send(boost::mpi::communicator* communicator)
{
	communicator->send(k52::parallel::mpi::constants::kServerRank, k52::parallel::mpi::constants::kCommonTag, _objectiveFunctionValue);
}

#endif

}/* namespace optimize */
}/* namespace k52 */
