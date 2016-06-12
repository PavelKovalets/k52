#include <k52/optimization/hooke_jeeves_method.h>

#ifdef BUILD_WITH_MPI

#include <boost/mpi.hpp>
#include <k52/parallel/mpi/constants.h>

#endif

#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdexcept>

#include <k52/common/floating_point.h>
#include <k52/optimization/params/i_continuous_parameters.h>

using ::std::vector;

namespace k52
{
namespace optimization
{

HookeJeevesMethod::HookeJeevesMethod(
    double acceleration,
    double init_step,
    size_t max_iteration_number,
    double precision,
    double step_divider)
    : acceleration_(acceleration)
    , init_step_(init_step)
    , max_iteration_number_(max_iteration_number)
    , precision_(precision)
    , step_divider_(step_divider)
{
}

HookeJeevesMethod* HookeJeevesMethod::Clone() const
{
    return new HookeJeevesMethod(
        acceleration_,
        init_step_,
        max_iteration_number_,
        precision_,
        step_divider_);
}

std::string HookeJeevesMethod::get_name() const
{
    return "Hooke-Jeeves Method";
}

#ifdef BUILD_WITH_MPI
void HookeJeevesMethod::Send(boost::mpi::communicator* communicator, int target) const
{
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, acceleration_);
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, precision_);
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, max_iteration_number_);
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, init_step_);
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, step_divider_);
}

void HookeJeevesMethod::Receive(boost::mpi::communicator* communicator, int source)
{
    communicator->recv(source, k52::parallel::mpi::constants::kCommonTag, acceleration_);
    communicator->recv(source, k52::parallel::mpi::constants::kCommonTag, precision_);
    communicator->recv(source, k52::parallel::mpi::constants::kCommonTag, max_iteration_number_);
    communicator->recv(source, k52::parallel::mpi::constants::kCommonTag, init_step_);
    communicator->recv(source, k52::parallel::mpi::constants::kCommonTag, step_divider_);
}
#endif

vector<double> HookeJeevesMethod::FindOptimalParameters(const vector<double>& initial_parameters)
{
    vector<double> arguments(initial_parameters);
    vector<double> arguments_after_search(initial_parameters.size());
    vector<double> steps_array = vector<double>(arguments.size(), init_step_);
    size_t iteration = 0;

    do
    {
        arguments_after_search = CoordinatewiseSearch(arguments, steps_array);
        if (common::FloatingPoint::AreEqual(arguments, arguments_after_search))
        {
            for (size_t i = 0; i < steps_array.size(); ++i)
            {
                steps_array[i] /= step_divider_;
            }
            continue;
        }

        vector<double> next_step_arguments(arguments.size());
        vector<double> next_step_arguments_after_search(arguments.size());
        while (true)
        {
            for (size_t i = 0; i<arguments.size(); ++i)
            {
                next_step_arguments[i] = arguments[i] + acceleration_
                        * (arguments_after_search[i] - arguments[i]);
            }
            next_step_arguments_after_search = CoordinatewiseSearch(next_step_arguments, steps_array);

            arguments = arguments_after_search;
            if (CountObjectiveFunctionValueToMinimize(arguments_after_search) <=
                    CountObjectiveFunctionValueToMinimize(next_step_arguments_after_search))
            {
                break;
            }
            arguments_after_search = next_step_arguments_after_search;

            iteration++;
            // Check number of iterations
            if (iteration == max_iteration_number_)
            {
                std::cout << "Solution not found" << std::endl;
                return arguments_after_search;
            }
        }
    } while (!IsExitCriteriaFulfilled(steps_array));
    return arguments_after_search;
}

bool HookeJeevesMethod::IsExitCriteriaFulfilled(
    const vector<double>& steps_array) const
{
    double temp = 0;
    // Check if step is small enough
    for (size_t j = 0; j<steps_array.size(); ++j)
    {
        temp += steps_array[j] * steps_array[j];
    }
    if (std::sqrt(temp) <= precision_)
    {
        return true;
    }
    return false;
}

vector<double> HookeJeevesMethod::CoordinatewiseSearch(
    const vector<double>& arguments,
    const vector<double>& steps_array) const
{
    vector<double> new_arguments(arguments);
    for (size_t i = 0; i < arguments.size(); ++i)
    {
        double new_function_value = CountObjectiveFunctionValueToMinimize(new_arguments);
        vector<double> temp(new_arguments);

        temp[i] = new_arguments[i] + steps_array[i];
        if (CountObjectiveFunctionValueToMinimize(temp) < new_function_value)
        {
            new_arguments = temp;
            continue;
        }

        temp[i] = new_arguments[i] - steps_array[i];
        if (CountObjectiveFunctionValueToMinimize(temp) < new_function_value)
        {
            new_arguments = temp;
        }
    }
    return new_arguments;
}

}/* namespace optimization */
}/* namespace k52 */