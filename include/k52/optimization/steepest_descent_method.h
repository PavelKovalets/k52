#ifndef STEEPEST_DESCENT_METHOD_H_
#define STEEPEST_DESCENT_METHOD_H_

#include <boost/shared_ptr.hpp>

#include <k52/common/constants.h>
#include <k52/optimization/continuous_optimizer.h>

namespace k52
{
namespace optimization
{


/// @class Realization of Steepest descent optimization method
/// @see
///SteepestDescentMethod, localization method:
/// @link http://elib.bsu.by/handle/123456789/8648
///DOC5.NB  ||  MVE - chast'2-2006.ppt
///Alternative link:
/// @link https://drive.google.com/folderview?id=0B6NiSXfI55hTMjhTTF85bHpyYzQ&usp=drive_web&tid=0B6NiSXfI55hTSWpYV0g2Z25PejA#list	
///DOC5.pdf
///Golden Section Search method:
/// @link http://vsem-dm.narod.ru/27.html
class SteepestDescentMethod : public ContinuousOptimizer
{
public:
    /// @brief Creates instance of SteepestDescentMethod.
    /// @param alfa - number that defines optimal multiplication step for Golden Section Search method
    /// @param increment_of_the_argument - number that defines value of gradient step per coordinate
    /// @param max_iteration_number - maximum number of iterations before computations will be stopped
    /// @param precision - number that defines accuracy of our computations
    SteepestDescentMethod(
        double increment_of_the_argument = 0.00001,
        size_t max_iteration_number = 100,
        double precision = common::Constants::Eps);

    /// @see ICloneable::Clone()
    virtual SteepestDescentMethod* Clone() const;

    /// @see ContinuousOptimizer::get_name()
    virtual std::string get_name() const;

#ifdef BUILD_WITH_MPI
    virtual void Send(boost::mpi::communicator* communicator, int target) const;

    virtual void Receive(boost::mpi::communicator* communicator, int source);
#endif

protected:
    virtual std::vector<double> FindOptimalParameters(const std::vector<double>&);

    /// @brief Checks if steps vector length satisfies an exit criteria.
    /// @param steps_array - vector of steps values for diffirent coordinates 
    /// @return true if steps vector norm less than specified precision, false other way
    bool IsExitCriteriaFulfilled(
        const std::vector<double>& steps_array) const;

    /// @brief Calculates gradient in the point.
    /// @param parameters - vector of coordinates
    /// @return new vector with direction to the function increase
    std::vector<double> CalculateGradient(
        const std::vector<double>& parameters) const;

    /// @brief Calculates partial derivative for the point.
    /// @param parameters - vector of coordinates
    /// @param index - index of coordinate
    /// @return value of partial derivative for the point
    double CalculateDerivative(
        const std::vector<double>& parameters,
        const size_t& index) const;

    /// @brief Multiply each coordinate of vector by -1
    /// @param parameters - vector of coordinates
    /// @return invert vector
    std::vector<double> InvertVector(
        const std::vector<double>& parameters) const;

    /// @brief Calculate optimal coefficient for Steepest descent method
    /// @param init_point - vector of current point
    /// @param step - previous step in Steepest descent method
    /// @param direction - vector of steps for each coordiante
    /// @return cooficient for next step in Steepest descent method
    double GoldenSectionSearch(
        const std::vector<double>& init_point, 
        const double& step, 
        const std::vector<double>& direction) const;

    /// @brief Supporting method for search of Steepest descent optimal coefficient
    /// @param init_parameters - vector of current point
    /// @param step_for_borders - step for localization segment with minimum of function
    /// @param direction - vector of steps for each coordiante
    /// @return cooficient for next step in Steepest descent method
    double FindStepLength(
        const std::vector<double>& init_parameters,
        const double& step_for_borders,
        const std::vector<double>& direction) const;

    /// @brief Supporting method for search of Steepest descent optimal coefficient
    /// @param init_parameters - vector of current point
    /// @param init_step - step value for first iteration of method
    /// @param direction - vector of steps for each coordiante
    /// @return border step for golden section search method
    double Localization(
        const std::vector<double>& init_parameters,
        const double& init_step,
        const std::vector<double>& direction) const;

private:

    /// Step for gradient to coordinates
    double increment_of_the_argument_;

    ///Maximum iterations number
    size_t max_iteration_number_;

    ///Used precision
    double precision_;

};

}
}

#endif
