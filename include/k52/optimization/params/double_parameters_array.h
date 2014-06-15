#ifndef DOUBLEPARAMETERSARRAY_H_
#define DOUBLEPARAMETERSARRAY_H_

#include <k52/optimization/params/double_parameter.h>
#include <k52/optimization/params/const_chromosome_size_paremeters.h>

namespace k52
{
namespace optimization
{

class DoubleParametersArray : public ConstChromosomeSizeParemeters
{
public:
    typedef boost::shared_ptr<DoubleParametersArray> shared_ptr;

    DoubleParametersArray(double min_value,
                          double max_value,
                          double desired_precision,
                          size_t number_of_parameters);

    DoubleParametersArray* Clone() const;

    bool HasSameMetaParameters(const IDiscreteParameters* parameters) const;

    bool CheckConstraints() const;

    void SetChromosome(ChromosomeType::iterator from, ChromosomeType::iterator to) const;

    void SetFromChromosome(ChromosomeType::const_iterator from, ChromosomeType::const_iterator to);

    void SetValues(const std::vector<double>& values);
    std::vector<double> get_values() const;
    double get_max_value() const;
    double get_min_value() const;
    size_t get_number_of_parameters() const;
    double get_actual_precision() const;

private:
    DoubleParametersArray();
    size_t CountTotalChromosomeSize() const;

    DoubleParameter::shared_ptr sample_parameter_;
    std::vector<double> values_;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* DOUBLEPARAMETERSARRAY_H_ */
