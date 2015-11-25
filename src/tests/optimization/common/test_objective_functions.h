#ifndef TEST_OBJECTIVE_FUNCTIONS_H_
#define TEST_OBJECTIVE_FUNCTIONS_H_

#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <k52/optimization/continuous_objective_function.h>
#include <k52/optimization/params/i_continuous_parameters.h>

#include "consts.h"

namespace k52
{
namespace optimization_tests
{

class SquareObjectiveFunction : public k52::optimization::ContinuousObjectiveFunction
{
public:

    virtual double operator () (const std::vector<double>& values) const
    {
        double summ = 0;

        for(size_t i=0; i<values.size(); i++)
        {
            double value = values[i];
            double diff = std::abs(value*value - 2);
            summ += 1/diff;
        }

        return summ;
    }

    virtual SquareObjectiveFunction* Clone() const
    {
        return new SquareObjectiveFunction();
    }
};

class SimpleSquareObjectiveFunction : public k52::optimization::ContinuousObjectiveFunction
{
public:

    virtual double operator () (const std::vector<double>& values) const
    {
        double summ = 0;

        for(size_t i=0; i<values.size(); i++)
        {
            double value = values[i];
            double diff = (value*value - 2);

            summ += diff*diff;
        }

        return summ;
    }

    virtual SimpleSquareObjectiveFunction* Clone() const
    {
        return new SimpleSquareObjectiveFunction();
    }
};

class SquareSummObjectiveFunction : public k52::optimization::ContinuousObjectiveFunction
{
public:

    virtual double operator () (const std::vector<double>& values) const
    {
        double summ = 0;

        for(size_t i=0; i<values.size(); i++)
        {
            double value = values[i];
            summ += value*value;
        }

        return summ;
    }

    virtual SquareSummObjectiveFunction* Clone() const
    {
        return new SquareSummObjectiveFunction();
    }
};

class DifractionObjectiveFunction : public k52::optimization::ContinuousObjectiveFunction
{
public:

    virtual double operator () (const std::vector<double>& values) const
    {
        double summ = 0;

        for(size_t i=0; i<values.size(); i++)
        {
            double value = values[i];
            double add = 0;

            if(std::abs(value) < consts::eps)
            {
                add = 1;
            }
            else
            {
                add = std::sin(value) / value;
            }

            summ += add;
        }

        return summ;
    }

    virtual SimpleSquareObjectiveFunction* Clone() const
    {
        return new SimpleSquareObjectiveFunction();
    }
};

class TwoDimmensionalObjectiveFunction : public k52::optimization::ContinuousObjectiveFunction
{
public:
    virtual double operator () (const std::vector<double>& values) const
    {
        if(values.size() != 2)
        {
            throw std::invalid_argument(
                "TwoDimmensionalObjectiveFunction supports only 2 dimmensions."
            );
        }
        double x = values[0];
        double y = values[1];

        return (*this) (x, y);
    }
    virtual double operator () (const double& x, const double& y) const = 0;
};

class MultiminimumObjectiveFunction : public TwoDimmensionalObjectiveFunction
{
public:
    virtual double operator () (const double& x, const double& y) const
    {
        double result = x * std::sin(4 * x) + 1.1 * y * std::sin(2 * y);

        return result;
    }

    virtual MultiminimumObjectiveFunction* Clone() const
    {
        return new MultiminimumObjectiveFunction();
    }
};

}/* namespace optimization_tests */
}/* namespace k52 */

#endif /* TEST_OBJECTIVE_FUNCTIONS_H_ */
