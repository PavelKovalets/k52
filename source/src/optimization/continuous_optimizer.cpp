#include <k52/optimization/continuous_optimizer.h>

#include <stdexcept>

using ::std::vector;

namespace k52
{
namespace optimization
{

void ContinuousOptimizer::Optimize(const IObjectiveFunction &function_to_optimize,
    IParameters* parameters_to_optimize,
    bool maximize)
{
    IContinuousParameters* continuous_parameters_to_optimize = dynamic_cast<IContinuousParameters*>(parameters_to_optimize);

    if (!continuous_parameters_to_optimize)
    {
        throw std::logic_error("ContinuousOptimizer must accept IContinuousParameters");
    }

    const ContinuousObjectiveFunction& continuous_function_to_optimize = dynamic_cast<const ContinuousObjectiveFunction&>(function_to_optimize);

    this->Optimize(continuous_function_to_optimize, continuous_parameters_to_optimize, maximize);
}

void ContinuousOptimizer::Optimize(const ContinuousObjectiveFunction &function_to_optimize,
    IContinuousParameters* parameters_to_optimize,
    bool maximize)
{
    function_to_optimize_ = &function_to_optimize;
    parameters_to_optimize_ = parameters_to_optimize;
    maximize_ = maximize;

    vector<double> initial_values = parameters_to_optimize->GetValues();
    vector<double> optimal_parameters = this->FindOptimalParameters(initial_values);

    parameters_to_optimize_->SetValues(optimal_parameters);
}

double ContinuousOptimizer::CountObjectiveFunctionValue(const std::vector<double>& parameters) const
{
    parameters_to_optimize_->SetValues(parameters);

    if (!parameters_to_optimize_->CheckConstraints())
    {
        throw std::logic_error("Objective function cannot be evalueted from params with unsatisfied constraints");
    }

    return function_to_optimize_ -> operator() (parameters_to_optimize_);
}

double ContinuousOptimizer::CountObjectiveFunctionValueToMaximize(const std::vector<double>& parameters) const
{
    double counted_value = CountObjectiveFunctionValue(parameters);
    return maximize_ ? counted_value : (-1)*counted_value;
}

double ContinuousOptimizer::CountObjectiveFunctionValueToMinimize(const std::vector<double>& parameters) const
{
    double counted_value = CountObjectiveFunctionValue(parameters);
    return maximize_ ? (-1)*counted_value : counted_value;
}

const ContinuousObjectiveFunction*  ContinuousOptimizer::get_function_to_optimize() const
{
    return function_to_optimize_;
}

const IContinuousParameters* ContinuousOptimizer::get_parameters_to_optimize() const
{
    return parameters_to_optimize_;
}

bool ContinuousOptimizer::get_maximize() const
{
    return maximize_;
}

}/* namespace optimization */
}/* namespace k52 */