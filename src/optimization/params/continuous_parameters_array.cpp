#include <k52/optimization/params/continuous_parameters_array.h>
#include <boost/mpi.hpp>
#include <boost/serialization/vector.hpp>

#include <k52/parallel/mpi/constants.h>

#include <stdexcept>

namespace k52
{
namespace optimization
{

ContinuousParametersArray::ContinuousParametersArray(size_t number_of_parameters)
    : values_(number_of_parameters)
{
}

void ContinuousParametersArray::SetValues(const std::vector<double>& values)
{
    if(values.size() != values_.size())
    {
        throw std::invalid_argument("values has incorrect size");
    }

    for(size_t i=0; i<values_.size(); i++)
    {
        values_[i] = values[i];
    }
}

std::vector<double> ContinuousParametersArray::GetValues() const
{
    return values_;
}

ContinuousParametersArray *ContinuousParametersArray::Clone() const
{
    ContinuousParametersArray* clone = new ContinuousParametersArray(values_.size());
    clone->values_ = values_;
    return clone;
}

bool ContinuousParametersArray::CheckConstraints() const
{
    return true;
}

void ContinuousParametersArray::Send(boost::mpi::communicator* communicator, int target) const
{
    //Discrete parameters are considered to be completely represented by theirs chromosome
    //TODO to optimize performance do not create intermediate chromosome
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, values_);
}

void ContinuousParametersArray::Receive(boost::mpi::communicator* communicator)
{
    //TODO to optimize performance do not create intermediate chromosome
    std::vector<double> values;
    communicator->recv(k52::parallel::mpi::constants::kServerRank, k52::parallel::mpi::constants::kCommonTag, values);
    values_ = values;
}


}/* namespace optimization */
}/* namespace k52 */
