#ifndef GRIDSEARCH_H_
#define GRIDSEARCH_H_

#include <boost/shared_ptr.hpp>

#include <common/disallow_copy_and_assign.h>
#include <optimize/i_optimizer.h>

namespace k52
{
namespace optimize
{

class ObjectiveFunctionCounter;

class GridSearch: public IOptimizer
{
public:
    GridSearch(double precision, double lower_bound, double upper_bound);

    virtual void Optimize(
        const IObjectiveFunction& function_to_optimize,
        IParameters* parametrs_to_optimize);

protected:
    static size_t IntegerPow(size_t value, size_t pow);

private:
    boost::shared_ptr<ObjectiveFunctionCounter> fitness_counter_;
    double lower_bound_;
    double upper_bound_;
    double precision_;

    DISALLOW_COPY_AND_ASSIGN(GridSearch);
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* GRIDSEARCH_H_ */
