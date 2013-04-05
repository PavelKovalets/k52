#ifndef CONTINUOUSPARAMETERSARRAY_H_
#define CONTINUOUSPARAMETERSARRAY_H_

#include <k52/optimization/params/i_continuous_parameters.h>

namespace k52
{
namespace optimization
{

class ContinuousParametersArray: public IContinuousParameters
{
public:
    typedef boost::shared_ptr<ContinuousParametersArray> shared_ptr;

    explicit ContinuousParametersArray(size_t number_of_parameters);

    virtual void SetValues(const std::vector<double>& values);

    virtual std::vector<double> GetValues() const;

    virtual ContinuousParametersArray* Clone() const;

    virtual bool CheckConstraints() const;

#ifdef BUILD_WITH_MPI
    virtual void Send(boost::mpi::communicator* communicator, int target) const;

    virtual void Receive(boost::mpi::communicator* communicator);
#endif

private:
    std::vector<double> values_;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* CONTINUOUSPARAMETERSARRAY_H_ */
