#ifndef DOUBLEPARAMETERSARRAY_H_
#define DOUBLEPARAMETERSARRAY_H_

#include <optimize/params/discrete_parameters.h>
#include <optimize/params/double_parameter.h>
#include <optimize/params/composite_discrete_parameters.h>
#include <optimize/params/const_chromosome_size_paremeters.h>

namespace k52
{
namespace optimize
{

class DoubleParametersArray : public DiscreteParameters
{
public:
    typedef boost::shared_ptr<DoubleParametersArray> shared_ptr;

    DoubleParametersArray(double min_value, double max_value, double desired_precision, size_t number_of_parameters);

    DoubleParametersArray* Clone() const;

    bool CheckConstraints() const;

    size_t GetChromosomeSize() const;

    void SetChromosome(std::vector<bool>::iterator from, std::vector<bool>::iterator to) const;

    void SetFromChromosome(std::vector<bool>::const_iterator from, std::vector<bool>::const_iterator to);

    std::vector<double> GetValues() const;

    double get_max_value() const;
    double get_min_value() const;
    size_t get_number_of_parameters() const;
    double get_actual_precision() const;

protected:
    const DoubleParameter::shared_ptr GetDoubleParameter(size_t index) const;

private:
    DoubleParametersArray();

    CompositeDiscreteParameters::shared_ptr double_parameters_;
    double min_value_;
    double max_value_;
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* DOUBLEPARAMETERSARRAY_H_ */
