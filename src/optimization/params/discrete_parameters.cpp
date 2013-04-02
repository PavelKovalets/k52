#ifdef BUILD_WITH_MPI

#include <boost/mpi.hpp>
#include <boost/serialization/vector.hpp>

#include <k52/parallel/mpi/constants.h>
#include <k52/optimization/params/discrete_parameters.h>

namespace k52
{
namespace optimization
{

void DiscreteParameters::Send(boost::mpi::communicator* communicator, int target) const
{
    //Discrete parameters are considered to be completely represented by theirs chromosome
    //TODO to optimize performance do not create intermediate chromosome
    std::vector<bool> intermediate_chromosome = std::vector<bool>(this->GetChromosomeSize());
    this->SetChromosome(intermediate_chromosome.begin(), intermediate_chromosome.end());
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, intermediate_chromosome);
}

void DiscreteParameters::Receive(boost::mpi::communicator* communicator)
{
    //TODO to optimize performance do not create intermediate chromosome
    std::vector<bool> intermediate_chromosome;
    communicator->recv(k52::parallel::mpi::constants::kServerRank, k52::parallel::mpi::constants::kCommonTag, intermediate_chromosome);
    this->SetFromChromosome(intermediate_chromosome.begin(), intermediate_chromosome.end());
}

}/* namespace optimization */
}/* namespace k52 */

#endif
