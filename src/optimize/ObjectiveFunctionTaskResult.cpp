/*
 * ObjectiveFunctionTaskResult.cpp
 *
 *  Created on: Oct 14, 2012
 *      Author: pavel
 */

#include "ObjectiveFunctionTaskResult.h"

void ObjectiveFunctionTaskResult::setObjectiveFunctionValue(double objectiveFunctionValue)
{
	_objectiveFunctionValue = objectiveFunctionValue;
}

double ObjectiveFunctionTaskResult::getObjectiveFunctionValue() const
{
	return _objectiveFunctionValue;
}

#ifdef BUILD_WITH_MPI

#include <boost/mpi.hpp>
#include <parallel/mpi/Constants.h>

boost::mpi::request ObjectiveFunctionTaskResult::ireceive(boost::mpi::communicator* communicator, int source)
{
	return communicator->irecv(source, k52::parallel::mpi::Constants::CommonTag, _objectiveFunctionValue);
}

void ObjectiveFunctionTaskResult::send(boost::mpi::communicator* communicator)
{
	communicator->send(k52::parallel::mpi::Constants::ServerRank, k52::parallel::mpi::Constants::CommonTag, _objectiveFunctionValue);
}

#endif
