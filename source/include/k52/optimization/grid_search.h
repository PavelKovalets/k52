#ifndef GRIDSEARCH_H_
#define GRIDSEARCH_H_

#include <boost/shared_ptr.hpp>

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/optimization/i_optimizer.h>

namespace k52
{
namespace optimization
{

class ObjectiveFunctionCounter;

class GridSearch: public IOptimizer
{
public:
    GridSearch(double precision, double lower_bound, double upper_bound);

    virtual void Optimize(
        const IObjectiveFunction& function_to_optimize,
        IParameters* parameters_to_optimize);

    ///Creates deep clone of an object with resource allocation. See ICloneable
    ///@return deep clone of an object
    virtual GridSearch* Clone() const;

#ifdef BUILD_WITH_MPI
    virtual void Send(boost::mpi::communicator* communicator, int target) const;

    virtual void Receive(boost::mpi::communicator* communicator);
#endif

protected:
    static size_t IntegerPow(size_t value, size_t pow);

private:
    boost::shared_ptr<ObjectiveFunctionCounter> fitness_counter_;
    double lower_bound_;
    double upper_bound_;
    double precision_;

    DISALLOW_COPY_AND_ASSIGN(GridSearch);
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* GRIDSEARCH_H_ */
