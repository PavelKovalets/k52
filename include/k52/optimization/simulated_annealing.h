#ifndef SIMULATEDANNEALING_H_
#define SIMULATEDANNEALING_H_

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/optimization/continuous_optimizer.h>

namespace k52
{
namespace optimization
{

class SimulatedAnnealing : public ContinuousOptimizer
{
public:
    typedef boost::shared_ptr<SimulatedAnnealing> shared_ptr;

    SimulatedAnnealing(size_t max_number_of_iterations, double min_parameter_value, double max_parameter_value);
    virtual std::string get_name() const;

    ///Creates deep clone of an object with resource allocation. See ICloneable
    ///@return deep clone of an object
    virtual SimulatedAnnealing* Clone() const;

#ifdef BUILD_WITH_MPI
    virtual void Send(boost::mpi::communicator* communicator, int target) const;

    virtual void Receive(boost::mpi::communicator* communicator, int source);
#endif

protected:
    virtual std::vector<double> FindOptimalParameters(const std::vector<double>& initial_parameters);
    double CountTemperature(size_t current_iteration) const;
    double CountAcceptanceProbability(double current_value, double new_value, double temperature);
    std::vector<double> GetRandomNeighbour(const std::vector<double>& values);

private:
    size_t max_number_of_iterations_;
    double min_parameter_value_;
    double max_parameter_value_;

    DISALLOW_COPY_AND_ASSIGN(SimulatedAnnealing);
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* SIMULATEDANNEALING_H_ */
