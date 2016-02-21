#ifndef CONTINUOUSOPTIMIZER_H_
#define CONTINUOUSOPTIMIZER_H_

#include <k52/optimization/i_optimizer.h>
#include <k52/optimization/continuous_objective_function.h>

namespace k52
{
namespace optimization
{

class ContinuousOptimizer : public IOptimizer
{
public:
    typedef boost::shared_ptr<ContinuousOptimizer> shared_ptr;

    ///Virtual destructor for correct deallocation of resources in derived classes
    virtual ~ContinuousOptimizer() {}

    virtual void Optimize(const IObjectiveFunction &function_to_optimize,
        IParameters* parameters_to_optimize,
        bool maximize);

    virtual void Optimize(const ContinuousObjectiveFunction &function_to_optimize,
        IContinuousParameters* parameters_to_optimize,
        bool maximize);

    ///Creates deep clone of an object with resource allocation. See ICloneable
    ///@return deep clone of an object
    virtual ContinuousOptimizer* Clone() const = 0;

protected:
    virtual std::vector<double> FindOptimalParameters(const std::vector<double>& initial_parameters) = 0;

    double CountObjectiveFunctionValueToMaximize(const std::vector<double>& parameters) const;
    double CountObjectiveFunctionValueToMinimize(const std::vector<double>& parameters) const;

    const ContinuousObjectiveFunction* get_function_to_optimize() const;
    const IContinuousParameters* get_parameters_to_optimize() const;
    bool get_maximize() const;

private:
    double CountObjectiveFunctionValue(const std::vector<double>& parameters) const;

    const ContinuousObjectiveFunction* function_to_optimize_;
    IContinuousParameters* parameters_to_optimize_;
    bool maximize_;

};

}/* namespace optimization */
}/* namespace k52 */

#endif /* CONTINUOUSOPTIMIZER_H_ */