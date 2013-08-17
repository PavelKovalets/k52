#ifndef CONIUGATEGRADIENTMETHOD_H_
#define CONIUGATEGRADIENTMETHOD_H_

#include <vector>

#include <k52/optimization/i_optimizer.h>
#include <k52/optimization/params/i_continuous_parameters.h>

namespace k52
{
namespace optimization
{

class ConjugateGradientMethod: public IOptimizer
{
public:
    ConjugateGradientMethod(
        double precision = 0.0001,
        double increment_of_the_argument = 0.00001,
        size_t number_of_iterations = 1000);

    virtual void Optimize(
        const IObjectiveFunction& function_to_optimize,
        IParameters* parametrs_to_optimize,
        bool maximize);

    /// Creates deep clone of an object with resource allocation. See ICloneable
    /// @return deep clone of an object
    virtual ConjugateGradientMethod* Clone() const;

#ifdef BUILD_WITH_MPI
    virtual void Send(boost::mpi::communicator* communicator, int target) const;

    virtual void Receive(boost::mpi::communicator* communicator, int source);
#endif

protected:
    double CountObjectiveFunctionValue(
        const std::vector<double>& parameters);

    double CalculateDerivative (
        const std::vector<double>& parameters,
        size_t index);

    std::vector<double> FindNextSearchDirection (
        const std::vector<double>& gradient,
        const std::vector<double>& previous_search_direction,
        double weighting_coefficient,
        int iteration);

    double PerformOneDimensionalSearch(
        const std::vector<double>& parameters,
        const std::vector<double>& search_direction);

    double CalculateWeightingCoefficient(
        const std::vector<double>& gradient,
        const std::vector<double>& previous_gradient);

    std::vector<double> CalculateGradient(
        const std::vector<double>& parameters);

private:
    const IContinuousParameters* parametrs_to_optimize_;
    const IObjectiveFunction* function_to_optimize_;
    bool maximize_;

    double precision_;
    double increment_of_the_argument_;
    size_t number_of_iterations_;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* CONIUGATEGRADIENTMETHOD_H_ */
