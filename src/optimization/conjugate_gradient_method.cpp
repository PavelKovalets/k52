#include <k52/optimization/conjugate_gradient_method.h>

#ifdef BUILD_WITH_MPI

#include <boost/mpi.hpp>
#include <k52/parallel/mpi/constants.h>

#endif

#include <cmath>
#include <stdexcept>
#include <iostream>

#include <k52/optimization/params/i_continuous_parameters.h>

using ::std::vector;

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

vector<double> ConjugateGradientMethod::FindOptimalParameters(
    const vector<double>& initial_values)
{
    vector<double> parameters = initial_values;

    vector<double> gradient = CalculateGradient(parameters);
    vector<double> previous_gradient(parameters.size());

    vector<double> search_direction(parameters.size());
    vector<double> previous_search_direction(parameters.size());

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
        for (size_t i = 0; i<parameters.size(); i++)
        {
            parameters[i] += minimizing_parameter * search_direction[i];
        }

        previous_gradient = gradient;
        gradient = CalculateGradient(parameters);

        weighting_coefficient = CalculateWeightingCoefficient(gradient, previous_gradient);

        //TODO use vector math
        exit = 0;
        for (size_t i = 0; i<parameters.size(); i++)
        {
            exit += pow(gradient[i], 2);
        }
        exit = sqrt(exit);

        iteration++;
        if (iteration == number_of_iterations_)
        {
            std::cout << "Solution not found" << std::endl;
            break;
        }
    } while (exit >= precision_);

    return parameters;
}

double ConjugateGradientMethod::CountCorrectedObjectiveFunctionValue(
    const vector<double>& parameters)
{
    //Searching for minimum in the method
    return CountObjectiveFunctionValueToMinimize(parameters);
}

double ConjugateGradientMethod::CalculateDerivative(
    const vector<double>& parameters,
    size_t index)
{
    vector<double> decrement_function (parameters);
    vector<double> increment_function (parameters);
    decrement_function[index] = parameters[index] - increment_of_the_argument_/2;
    increment_function[index] = parameters[index] + increment_of_the_argument_/2;
    double increment_function_value = CountCorrectedObjectiveFunctionValue(increment_function);
    double decrement_function_value = CountCorrectedObjectiveFunctionValue(decrement_function);
    return (increment_function_value - decrement_function_value)/increment_of_the_argument_;
}

vector<double> ConjugateGradientMethod::FindNextSearchDirection(
    const vector<double>& gradient,
    const vector<double>& previous_search_direction,
    double weighting_coefficient,
    int iteration)
{
    vector<double> search_direction = gradient;

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

vector<double> ConjugateGradientMethod::CalculateGradient(
    const vector<double>& parameters)
{
    vector<double> gradient(parameters.size());

    //TODO use vector math
    for (size_t i=0; i<parameters.size(); i++)
    {
        gradient[i] = CalculateDerivative(parameters, i);
    }

    return gradient;
}

double ConjugateGradientMethod::PerformOneDimensionalSearch(
    const vector<double>& parameters,
    const vector<double>& search_direction)
{
    double x = 0, previous_x=0;

    //Using Newton method to find one-dim minimum
    do
    {
        previous_x = x;

        //Counting derivatives
        //TODO use vector math
        vector<double> point = parameters;
        vector<double> incremented = parameters;
        vector<double> decremented = parameters;
        for(size_t i=0; i<parameters.size(); i++)
        {
            point[i] += x*search_direction[i];
            incremented[i] += (x + increment_of_the_argument_/2)*search_direction[i];
            decremented[i] += (x - increment_of_the_argument_/2)*search_direction[i];
        }

        double f = CountCorrectedObjectiveFunctionValue(point);
        double f_incremented = CountCorrectedObjectiveFunctionValue(incremented);
        double f_decremented = CountCorrectedObjectiveFunctionValue(decremented);

        double dirivative = (f_incremented - f_decremented)/increment_of_the_argument_;
        double secound_derivative = (f_incremented - 2*f + f_decremented) / (increment_of_the_argument_*increment_of_the_argument_/4);

        x = previous_x - dirivative/secound_derivative;
    } while(std::abs(previous_x - x) > precision_);
    return x;
}

double ConjugateGradientMethod::CalculateWeightingCoefficient(
    const vector<double>& gradient,
    const vector<double>& previous_gradient)
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
