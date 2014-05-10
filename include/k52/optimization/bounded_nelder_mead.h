#ifndef BOUNDEDNELDERMEAD_H_
#define BOUNDEDNELDERMEAD_H_

#include <boost/shared_ptr.hpp>

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/optimization/continuous_optimizer.h>

namespace k52
{
namespace optimization
{

class ObjectiveFunctionCounter;

class BoundedNelderMead: public ContinuousOptimizer
{
public:
    BoundedNelderMead(double l, double precision, double lower_bound, double upper_bound);

    ///Creates deep clone of an object with resource allocation. See ICloneable
    ///@return deep clone of an object
    virtual BoundedNelderMead* Clone() const;

    double get_lower_bound() const;

    double get_upper_bound() const;

#ifdef BUILD_WITH_MPI
    virtual void Send(boost::mpi::communicator* communicator, int target) const;

    virtual void Receive(boost::mpi::communicator* communicator, int source);
#endif

protected:
    virtual std::vector<double> FindOptimalParameters(const std::vector<double>& initial_values);

    void CorrectByProjectingToBounds(std::vector<double>* point);

    std::vector<double> CountObjectiveFunctionValues(
        const std::vector< std::vector<double> >& parameters_values);

    double CountSingleObjectiveFunctionValue(const std::vector<double>& parameters);

    static void GetIndexes(const std::vector<double>& values, size_t* first_max_index, size_t* secound_max_index, size_t* min_index);
    static std::vector< std::vector<double> > GetRegularSimplex(const std::vector<double>& base_point, double l);
    static std::vector<double> Reflexion(const std::vector<double>& center_of_mass, const std::vector<double>& target_point);
    static std::vector<double> Expansion(const std::vector<double>& center_of_mass, const std::vector<double>& target_point);
    static std::vector<double> Contraction(const std::vector<double>& center_of_mass, const std::vector<double>& target_point);
    static void Reduction(std::vector< std::vector<double> >* polygon, size_t point_index);
    static double CountDifferance(const std::vector<double>& values);
    static std::vector<double> GetCenterOfMass(const std::vector< std::vector<double> >& polygon, size_t point_index);
    static void OutputPolygon(const std::vector< std::vector<double> >& polygon);

private:
    double precision_;
    double lower_bound_;
    double upper_bound_;
    double l_;

    DISALLOW_COPY_AND_ASSIGN(BoundedNelderMead);
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* BOUNDEDNELDERMEAD_H_ */
