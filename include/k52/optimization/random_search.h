#ifndef RANDOMSEARCH_H_
#define RANDOMSEARCH_H_

#include <vector>

#include <k52/optimization/i_optimizer.h>
#include <k52/optimization/params/i_continuous_parameters.h>

namespace k52
{
namespace optimization
{

class IParametersProcessor;

class RandomSearch : public IOptimizer
{
public:
    RandomSearch(size_t number_of_random_points, double lower_bound, double upper_bound);

    virtual void Optimize(const IObjectiveFunction &function_to_optimize,
                          IParameters* parametrs_to_optimize,
                          bool maximize);

protected:
    std::vector<double> GenerateRandomPoint(size_t vector_size);

private:
    boost::shared_ptr<IParametersProcessor> parameters_processor_;
    size_t number_of_random_points_;
    double lower_bound_;
    double upper_bound_;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* RANDOMSEARCH_H_ */
