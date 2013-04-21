#include <k52/optimization/params/continuous_parameters_array.h>
#ifdef BUILD_WITH_MPI

#include <boost/mpi.hpp>
#include <boost/serialization/vector.hpp>

#include <k52/parallel/mpi/constants.h>

#endif

#include <stdexcept>

namespace k52
{
namespace optimization
{

ContinuousParametersArray::ContinuousParametersArray(const std::vector<double>& values)
    : values_(values.size())
{
    SetValues(values);
}

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

#ifdef BUILD_WITH_MPI

void ContinuousParametersArray::Send(boost::mpi::communicator* communicator, int target) const
{
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, values_);
}

void ContinuousParametersArray::Receive(boost::mpi::communicator* communicator)
{
    std::vector<double> values;
    communicator->recv(k52::parallel::mpi::constants::kServerRank, k52::parallel::mpi::constants::kCommonTag, values);
    values_ = values;
}

#endif


}/* namespace optimization */
}/* namespace k52 */
