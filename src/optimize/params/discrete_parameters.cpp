#ifdef BUILD_WITH_MPI

#include <boost/mpi.hpp>
#include <boost/serialization/vector.hpp>

#include <parallel/mpi/constants.h>
#include <optimize/params/DiscreteParameters.h>

namespace k52
{
namespace optimize
{

void DiscreteParameters::send(boost::mpi::communicator* communicator, int target) const
{
    //Discrete parameters are considered to be completely represented by theirs chromosome
    //TODO to optimize performance do not create intermediate chromosome
    std::vector<bool> intermediate_chromosome = std::vector<bool>(this->getChromosomeSize());
    this->setChromosome(intermediate_chromosome.begin(), intermediate_chromosome.end());
    communicator->send(target, k52::parallel::mpi::Constants::CommonTag, intermediate_chromosome);
}

void DiscreteParameters::receive(boost::mpi::communicator* communicator)
{
    //TODO to optimize performance do not create intermediate chromosome
    std::vector<bool> intermediate_chromosome;
    communicator->recv(k52::parallel::mpi::Constants::ServerRank, k52::parallel::mpi::Constants::CommonTag, intermediate_chromosome);
    this->setFromChromosome(intermediate_chromosome.begin(), intermediate_chromosome.end());
}

}/* namespace optimize */
}/* namespace k52 */

#endif
