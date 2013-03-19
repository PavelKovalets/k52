/*
 * DiscreteParameters.cpp
 *
 *  Created on: Jan 31, 2013
 *      Author: pavel
 */

#ifdef BUILD_WITH_MPI

#include <optimize/params/DiscreteParameters.h>
#include <parallel/mpi/constants.h>
#include <boost/mpi.hpp>
#include <boost/serialization/vector.hpp>

namespace k52
{
namespace optimize
{

void DiscreteParameters::send(boost::mpi::communicator* communicator, int target) const
{
	//Discrete parameters are considered to be completely represented by theirs chromosome
	//TODO to optimize performance do not create intermediate chromosome
	std::vector<bool> intermediateChromosome = std::vector<bool>(this->getChromosomeSize());
	this->setChromosome(intermediateChromosome.begin(), intermediateChromosome.end());
	communicator->send(target, k52::parallel::mpi::Constants::CommonTag, intermediateChromosome);
}

void DiscreteParameters::receive(boost::mpi::communicator* communicator)
{
	//TODO to optimize performance do not create intermediate chromosome
	std::vector<bool> intermediateChromosome;
	communicator->recv(k52::parallel::mpi::Constants::ServerRank, k52::parallel::mpi::Constants::CommonTag, intermediateChromosome);
	this->setFromChromosome(intermediateChromosome.begin(), intermediateChromosome.end());
}

}/* namespace optimize */
}/* namespace k52 */

#endif
