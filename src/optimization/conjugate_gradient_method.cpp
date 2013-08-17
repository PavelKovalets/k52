#include <k52/optimization/conjugate_gradient_method.h>

#ifdef BUILD_WITH_MPI

#include <boost/mpi.hpp>
#include <k52/parallel/mpi/constants.h>

#endif

#include <cmath>
#include <stdexcept>

#include <k52/optimization/params/i_continuous_parameters.h>

namespace k52
{
namespace optimization
{

ConjugateGradientMethod::ConjugateGradientMethod(
    double precision,
    double increment_of_the_argument,
    size_t number_of_iterations)
{
    precision_ = precision;
    increment_of_the_argument_ = increment_of_the_argument;
    number_of_iterations_ = number_of_iterations;
}

void ConjugateGradientMethod::Optimize(
    const IObjectiveFunction& function_to_optimize,
    IParameters* parametrs_to_optimize,
    bool maximize)
{
    function_to_optimize_ = &function_to_optimize;
    maximize_ = maximize;
    IContinuousParameters* continuous_parameters = dynamic_cast<IContinuousParameters*> (parametrs_to_optimize);
    parametrs_to_optimize_ = continuous_parameters;
    std::vector<double> parameters = continuous_parameters->GetValues();

    std::vector<double> gradient = CalculateGradient(parameters);
    std::vector<double> previous_gradient(parameters.size());

    std::vector<double> search_direction(parameters.size());
    std::vector<double> previous_search_direction(parameters.size());

    double weighting_coefficient = 0;
    double exit = 0;
    size_t iteration = 1;

    //http://en.wikipedia.org/wiki/Nonlinear_conjugate_gradient_method
    do
    {
        previous_search_direction = search_direction;
        search_direction = FindNextSearchDirection(gradient, previous_search_direction, weighting_coefficient, iteration);

        double minimizing_parameter = PerformOneDimensionalSearch(parameters, search_direction);
        //TODO use vector math
        for (size_t i=0; i<parameters.size(); i++)
        {
            parameters[i] += minimizing_parameter * search_direction[i];
        }

        previous_gradient = gradient;
        gradient = CalculateGradient(parameters);

        weighting_coefficient = CalculateWeightingCoefficient(gradient, previous_gradient);

        //TODO use vector math
        exit = 0;
        for (size_t i=0; i<parameters.size(); i++)
        {
            exit += pow(gradient[i],2);
        }
        exit = sqrt(exit);

        iteration++;
        if (iteration == number_of_iterations_)
        {
            std::cout<<"Solution not found"<<std::endl;
            break;
        }
    }
    while (exit >= precision_);

    continuous_parameters->SetValues(parameters);
}

ConjugateGradientMethod* ConjugateGradientMethod::Clone() const
{
    return new ConjugateGradientMethod(precision_, increment_of_the_argument_, number_of_iterations_);
}

#ifdef BUILD_WITH_MPI
void ConjugateGradientMethod::Send(boost::mpi::communicator* communicator, int target) const
{
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, precision_);
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, increment_of_the_argument_);
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, number_of_iterations_);
}

void ConjugateGradientMethod::Receive(boost::mpi::communicator* communicator, int source)
{
    communicator->recv(source,
        k52::parallel::mpi::constants::kCommonTag,
        precision_);
    communicator->recv(source,
        k52::parallel::mpi::constants::kCommonTag,
        increment_of_the_argument_);
    communicator->recv(source,
        k52::parallel::mpi::constants::kCommonTag,
        number_of_iterations_);
}
#endif

double ConjugateGradientMethod::CountObjectiveFunctionValue(
    const std::vector<double>& parameters)
{
    IContinuousParameters::shared_ptr parameters_clone( parametrs_to_optimize_->Clone() );
    parameters_clone->SetValues(parameters);

    double counted_value = (*function_to_optimize_)(parameters_clone.get());

    //Searching for minimum in the method
    if (maximize_)
    {
        return (-1)*counted_value;
    }
    else
    {
        return counted_value;
    }
}

double ConjugateGradientMethod::CalculateDerivative(
    const std::vector<double>& parameters,
    size_t index)
{
    std::vector<double> decrement_function (parameters);
    std::vector<double> increment_function (parameters);
    decrement_function[index] = parameters[index] - increment_of_the_argument_/2;
    increment_function[index] = parameters[index] + increment_of_the_argument_/2;
    double increment_function_value = CountObjectiveFunctionValue(increment_function);
    double decrement_function_value = CountObjectiveFunctionValue(decrement_function);
    return (increment_function_value - decrement_function_value)/increment_of_the_argument_;
}

std::vector<double> ConjugateGradientMethod::FindNextSearchDirection(
    const std::vector<double>& gradient,
    const std::vector<double>& previous_search_direction,
    double weighting_coefficient,
    int iteration)
{
    std::vector<double> search_direction = gradient;

    if (iteration > 1)
    {
        //TODO use vector math
        for (size_t i=0; i<gradient.size(); i++)
        {
            search_direction[i] += weighting_coefficient * previous_search_direction[i];
        }
    }

    return search_direction;
}

std::vector<double> ConjugateGradientMethod::CalculateGradient(
    const std::vector<double>& parameters)
{
    std::vector<double> gradient(parameters.size());

    //TODO use vector math
    for (size_t i=0; i<parameters.size(); i++)
    {
        gradient[i] = CalculateDerivative(parameters, i);
    }

    return gradient;
}

double ConjugateGradientMethod::PerformOneDimensionalSearch(
    const std::vector<double>& parameters,
    const std::vector<double>& search_direction)
{
    double x = 0, previous_x=0;

    //Using Newton method to find one-dim minimum
    do
    {
        previous_x = x;

        //Counting derivatives
        //TODO use vector math
        std::vector<double> point = parameters;
        std::vector<double> incremented = parameters;
        std::vector<double> decremented = parameters;
        for(size_t i=0; i<parameters.size(); i++)
        {
            point[i] += x*search_direction[i];
            incremented[i] += (x + increment_of_the_argument_/2)*search_direction[i];
            decremented[i] += (x - increment_of_the_argument_/2)*search_direction[i];
        }

        double f = CountObjectiveFunctionValue(point);
        double f_incremented = CountObjectiveFunctionValue(incremented);
        double f_decremented = CountObjectiveFunctionValue(decremented);

        double dirivative = (f_incremented - f_decremented)/increment_of_the_argument_;
        double secound_derivative = (f_incremented - 2*f + f_decremented) / (increment_of_the_argument_*increment_of_the_argument_/4);

        x = previous_x - dirivative/secound_derivative;
    } while(fabs(previous_x - x) > precision_);
    return x;
}

double ConjugateGradientMethod::CalculateWeightingCoefficient(
    const std::vector<double>& gradient,
    const std::vector<double>& previous_gradient)
{
    //Fletcher–Reeves coefficient
    double gradient_square=0;
    double previous_gradient_square=0;

    //TODO replace pow 2
    //TODO use vector math
    for (size_t i=0; i<gradient.size(); i++)
    {
        gradient_square += pow(gradient[i], 2);
        previous_gradient_square += pow(previous_gradient[i], 2);
    }

    //TODO usew float compare
    if(previous_gradient_square == 0)
    {
        throw std::runtime_error("previous_gradient_square == 0");
    }

    return gradient_square / previous_gradient_square;
}

}/* namespace optimization */
}/* namespace k52 */
