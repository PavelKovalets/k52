#ifndef HLEBORODOV_ROSENBROCK_METHOD_H_
#define HLEBORODOV_ROSENBROCK_METHOD_H_

#include <boost/shared_ptr.hpp>

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/optimization/continuous_optimizer.h>

namespace k52
{
namespace optimization
{

class HleborodovRosenbrockMethod: public ContinuousOptimizer
{
public:
    HleborodovRosenbrockMethod(
        double precision,
        size_t max_iteration_number,
        double first_step,
        double max_step);

    /// Creates deep clone of an object with resource allocation. See ICloneable
    /// @return deep clone of an object
    virtual HleborodovRosenbrockMethod* Clone() const;

#ifdef BUILD_WITH_MPI
    virtual void Send(boost::mpi::communicator* communicator, int target) const;

    virtual void Receive(boost::mpi::communicator* communicator, int source);
#endif

protected:
    virtual std::vector<double> FindOptimalParameters(const std::vector<double>& initial_values);

    /// Set basis to Decart and steps to default
    void InitializeBasisAndSteps();

    /// Checks if differance between current and previous arguments
    /// satisfies an exit criteria
    bool IsExitCriteriaFulfilled(
        const std::vector<double>& arguments,
        const std::vector<double>& previous_step_arguments);

    /// Make test step in old basis
    void MakeStep(std::vector<double> &arguments);

    void MakeStepPerCoordinate(int basis_index, std::vector<double>* arguments);

    /// Make new orthonormal basis using increase of tested function arguments
    /// and old basis (ortogonalization by Gramm-Shmidt)
    void CreateNewBasis();

    void NormalizeVector(std::vector<double>& target_vector);

    /// Return scalar composition of two vectors
    //TODO provide general solution
    double ScalarComposition(
        const std::vector<double>& first_vector,
        const std::vector<double>& second_vector);

    /// Step should not become more then maximal step
    void CorrectStep(size_t step_index);

private:
    /// Rolling (according with method) coordinate system,
    /// each line - the direction of one of the perpendicular vectors
    std::vector< std::vector<double> > basis_;

    /// An array of steps for each coordinate
    std::vector<double> steps_array_;

    /// Number of coordinats in the function
    size_t dimension_;

    /// Used precesion
    double precision_;

    /// Parameters of step increasing (it is advisable not to change)
    double arguments_increase_;

    /// Parameters of step decreasing (it is advisable not to change)
    double arguments_decrease_;

    /// First (tested) step by all of coordinats
    double first_step_;

    /// Maximum iterations number
    size_t max_iteration_number_;

    /// Maximal step value (step changes in the process)
    double max_step_;

    DISALLOW_COPY_AND_ASSIGN(HleborodovRosenbrockMethod);
};

}
}
#endif
