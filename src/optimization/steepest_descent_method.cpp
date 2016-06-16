#include "k52/optimization/steepest_descent_method.h"

#ifdef BUILD_WITH_MPI

#include <boost/mpi.hpp>
#include <k52/parallel/mpi/constants.h>

#endif

#include <iostream>
#include <cmath>

#include <k52/optimization/params/i_continuous_parameters.h>

namespace
{
/// @brief Golden ratio value for GoldenSectionSearch method
/// @link https://en.wikipedia.org/wiki/Golden_ratio
	const double kAlpha = (1.0 + sqrt(5.0)) / 2.0;
}

using ::std::vector;

namespace k52
{
namespace optimization
{

SteepestDescentMethod::SteepestDescentMethod(
    double increment_of_the_argument,
    size_t max_iteration_number,
    double precision)
    : increment_of_the_argument_(increment_of_the_argument)
    , max_iteration_number_(max_iteration_number)
    , precision_(precision)
{
}

SteepestDescentMethod* SteepestDescentMethod::Clone() const
{
    return new SteepestDescentMethod(
        increment_of_the_argument_,
        max_iteration_number_,
        precision_);
}

std::string SteepestDescentMethod::get_name() const
{
    return "Steepest Descent Method";
}


#ifdef BUILD_WITH_MPI
void SteepestDescentMethod::Send(boost::mpi::communicator* communicator, int target) const
 {
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, increment_of_the_argument_);
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, max_iteration_number_);
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, precision_);
}

void SteepestDescentMethod::Receive(boost::mpi::communicator* communicator, int source)
{
    communicator->recv(source, k52::parallel::mpi::constants::kCommonTag, increment_of_the_argument_);
    communicator->recv(source, k52::parallel::mpi::constants::kCommonTag, max_iteration_number_);
    communicator->recv(source, k52::parallel::mpi::constants::kCommonTag, precision_);
}
#endif


vector<double> SteepestDescentMethod::FindOptimalParameters(const vector<double>& initial_parameters)
{
    vector<double> parameters(initial_parameters);
    size_t counter = 0;
    double lambda = 1; 

    vector<double> next_step_parameters(parameters);
    do
    {
        parameters = next_step_parameters;
        counter++;
        vector<double> gradient = CalculateGradient(parameters);
        vector<double> invert_gradiend = InvertVector(gradient);

        lambda = GoldenSectionSearch(parameters, lambda, invert_gradiend);

        for (size_t i = 0; i < next_step_parameters.size(); ++i)
        {
            next_step_parameters[i] = parameters[i] + lambda * invert_gradiend[i];
        }

    } while (!IsExitCriteriaFulfilled(next_step_parameters) 
        && !(counter == max_iteration_number_));

    return parameters;
}

bool SteepestDescentMethod::IsExitCriteriaFulfilled(
    const vector<double>& steps_array) const
{
    double temp = 0;
    vector<double> gradient = CalculateGradient(steps_array);
    for (size_t i = 0; i < steps_array.size(); ++i)
    {
        temp += gradient[i] * gradient[i];
    }
    if (sqrt(temp) > precision_)
    {
        return false;
    }
    return true;
}
/// @TODO: needs to replaced copy-pasted method to the method from Math
/// @Source: conjugate_gradient_method.cpp
/// @link https://github.com/PavelKovalets/k52/blob/develop/src/optimization/conjugate_gradient_method.cpp#L159
vector<double> SteepestDescentMethod::CalculateGradient(
    const vector<double>& parameters) const
{
    vector<double> gradient(parameters.size());

    for (size_t i = 0; i<parameters.size(); ++i)
    {
        gradient[i] = CalculateDerivative(parameters, i);
    }

    return gradient;
}

/// @TODO: needs to replaced copy-pasted method to the method from Math
/// @Source: conjugate_gradient_method.cpp
/// @link https://github.com/PavelKovalets/k52/blob/develop/src/optimization/conjugate_gradient_method.cpp#L126
double SteepestDescentMethod::CalculateDerivative(
    const vector<double>& parameters,
    const size_t& index) const
{
    double half = 0.5;
    vector<double> decrement_function(parameters);
    vector<double> increment_function(parameters);
    decrement_function[index] = parameters[index] - increment_of_the_argument_ * half;
    increment_function[index] = parameters[index] + increment_of_the_argument_ * half;
    double increment_function_value = CountObjectiveFunctionValueToMinimize(increment_function);
    double decrement_function_value = CountObjectiveFunctionValueToMinimize(decrement_function);
    return (increment_function_value - decrement_function_value) / increment_of_the_argument_;
}

/// @TODO: needs to replaced to the method from Math
vector<double> SteepestDescentMethod::InvertVector(
    const vector<double>& parameters) const
{
    vector<double> new_parameters(parameters);
    for (size_t i = 0; i < new_parameters.size(); ++i)
    {
        new_parameters[i] *= -1;
    }
    return new_parameters;
}

double SteepestDescentMethod::GoldenSectionSearch(
    const vector<double>& init_point, 
    const double& step, 
    const vector<double>& direction) const
{
    vector<double> next_point(init_point.size());
    double lambda = 0;
    double step_for_borders = 0;

    step_for_borders = Localization(init_point, step, direction);
	
    lambda = FindStepLength(init_point, step_for_borders, direction);

    return lambda;
}

double SteepestDescentMethod::FindStepLength(
    const vector<double>& init_parameters, 
    const double& step_for_borders,
    const vector<double>& direction) const
{
    vector<double> right_border_parameters(init_parameters.size());
    vector<double> next_left_border_point(init_parameters.size());
    vector<double> next_right_border_point(init_parameters.size());
    double left_border = 0;
    double next_left_border = 0;
    double next_right_border = 0;
    double constriction_number = 0.382;
    double right_border = step_for_borders;
	
    for (size_t i = 0; i < init_parameters.size(); ++i)
    {
        right_border_parameters[i] = init_parameters[i] + step_for_borders*direction[i];
    }
	
    next_left_border = left_border + constriction_number*(right_border - left_border);
    next_right_border = right_border - constriction_number*(right_border - left_border);

    double last_left_border = 0;
    double last_right_border = 0;
    double next_left_border_value = 0;
    double next_right_border_value = 0;
    do
    {
        for (size_t i = 0; i < init_parameters.size(); ++i)
        {
            next_left_border_point[i] = init_parameters[i] + next_left_border*direction[i];
            next_right_border_point[i] = init_parameters[i] + next_right_border*direction[i];
        }
        next_left_border_value = CountObjectiveFunctionValueToMinimize(next_left_border_point);
        next_right_border_value = CountObjectiveFunctionValueToMinimize(next_right_border_point);

        last_left_border = left_border;
        last_right_border = right_border;

        if (next_left_border < next_right_border)
        {
            if (next_left_border_value > next_right_border_value)
            {
                left_border = next_left_border;
                next_left_border = next_right_border;
                next_right_border = right_border - constriction_number * (right_border - left_border);
            }
            else
            {
                right_border = next_right_border;
                next_right_border = next_left_border;
                next_left_border = left_border + constriction_number * (right_border - left_border);
            }
        }
        else
        {
            if (next_right_border_value > next_left_border_value)
            {
                left_border = next_right_border;
                next_right_border = next_left_border;
                next_left_border = right_border - constriction_number * (right_border - left_border);
            }
            else
            {
                right_border = next_left_border;
                next_left_border = next_right_border;
                next_right_border = left_border + constriction_number * (right_border - left_border);
            }
        }
        if ((left_border == last_left_border && right_border == last_right_border)) {
            break;
        }

    } while ((abs(left_border - right_border) > precision_));

    return (left_border + right_border) / 2;
}

double SteepestDescentMethod::Localization(
    const vector<double>& init_parameters, 
    const double& init_step, 
    const vector<double>& direction) const
{
    vector<double> point(init_parameters.size());
    double step = init_step*2;

    do {
		step /= 2;
        for (size_t i = 0; i < point.size(); ++i)
        {
            point[i] = init_parameters[i] + step*direction[i];
        }       		
    } while ((CountObjectiveFunctionValueToMinimize(point) > CountObjectiveFunctionValueToMinimize(init_parameters))
        && (abs(step) > precision_));


    vector<double> next_step_point(point);
    do
    {
        point = next_step_point;
        step *= kAlpha;
        for (size_t i = 0; i < point.size(); ++i)
        {
        next_step_point[i] = init_parameters[i] + step*direction[i];
        }

        
    } while (CountObjectiveFunctionValueToMinimize(next_step_point) <= CountObjectiveFunctionValueToMinimize(point));

    double final_step = 0;
    for (size_t i = 0; i < next_step_point.size(); ++i)
    {
        final_step += (next_step_point[i] - init_parameters[i])*(next_step_point[i] - init_parameters[i]);
    }

    return sqrt(final_step);
}

}//optimization
}//k52