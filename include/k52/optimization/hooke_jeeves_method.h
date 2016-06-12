#ifndef HOOKE_JEEVES_METHOD_H_
#define HOOKE_JEEVES_METHOD_H_

#include <boost/shared_ptr.hpp>

#include <k52/common/constants.h>
#include <k52/optimization/continuous_optimizer.h>

namespace k52
{
namespace optimization
{

//Sources:
//http://elib.bsu.by/handle/123456789/8648
//DOC5.NB  ||  MVE - chast'2-2006.ppt
//Alternative link:
//https://drive.google.com/folderview?id=0B6NiSXfI55hTMjhTTF85bHpyYzQ&usp=drive_web&tid=0B6NiSXfI55hTSWpYV0g2Z25PejA#list	
//DOC5.pdf

/// @class HookeJeevesMethod
/// @brief Realization of Hooke-Jeeves optimization method.
class HookeJeevesMethod: public ContinuousOptimizer
{
public:
    /// @brief Creates instance of HookeJeevesMethod.
    /// @param acceleration - number defines value of increase for step value for better convergence.
    /// Some researches have shown that minimum number of iterations will be achieved by coefficient that equals 3.5.
    /// @param init_step - number that defines value of step on first iteration.
    /// @param max_iteration_number - maximum number of iterations before computations will be stopped.
    /// @param precision - number that defines accuracy of our computations.
    /// @param step_divider - number that uses for decrease step value during search of direction.
    HookeJeevesMethod(
        double acceleration = 3.5,
        double init_step = 1,
        size_t max_iteration_number = 10000,
        double precision = common::Constants::Eps,
        double step_divider = 10 );

    /// @brief  See ICloneable.
    /// Creates deep clone of an object with resource allocation.
    /// @return deep clone of an object.
    virtual HookeJeevesMethod* Clone() const;

    virtual std::string get_name() const;

#ifdef BUILD_WITH_MPI
    virtual void Send(boost::mpi::communicator* communicator, int target) const;

    virtual void Receive(boost::mpi::communicator* communicator, int source);
#endif

protected:
    virtual std::vector<double> FindOptimalParameters(const std::vector<double>&);

    /// @brief Checks if steps vector length satisfies an exit criteria.
    /// @param steps_array - vector of steps values for different coordinates.
    /// @return true if steps vector norm is less than specified precision, false other way.
    bool IsExitCriteriaFulfilled(
        const std::vector<double>& steps_array) const;

    /// @brief Realization of Coordinate wise search.
    /// Method implements search from start point in all directions with specified step value.
    /// Hooke-Jeeves method is based on this optimization method.
    /// @param arguments - vector of coordinates of start point.
    /// @param steps_array - vector of values of step for different coordinates.
    /// @return vector of new coordinates.
    std::vector<double> CoordinatewiseSearch(
        const std::vector<double>& arguments,
        const std::vector<double>& steps_array) const;

private:
    /// Multiplier that increases step value for better convergence.
    double acceleration_;

    /// First step by all of coordinates.
    double init_step_;

    /// Maximum iterations number.
    size_t max_iteration_number_;

    /// Used precision.
    double precision_;

    /// Divider that uses for decrease step value during search of direction.
    double step_divider_;
};

}// namespace optimization
}// namespace k52
#endif