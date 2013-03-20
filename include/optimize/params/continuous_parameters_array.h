#ifndef CONTINUOUSPARAMETERSARRAY_H_
#define CONTINUOUSPARAMETERSARRAY_H_

#include <optimize/params/i_continuous_parameters.h>

namespace k52
{
namespace optimize
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
    //TODO implementation needed!!!
    virtual void Send(boost::mpi::communicator* communicator, int target) const;

    //TODO implementation needed!!!
    virtual void Receive(boost::mpi::communicator* communicator);
#endif

private:
    std::vector<double> values_;
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* CONTINUOUSPARAMETERSARRAY_H_ */
