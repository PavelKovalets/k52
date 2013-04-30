#ifndef DOUBLEPARAMETER_H_
#define DOUBLEPARAMETER_H_

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/optimization/params/const_chromosome_size_paremeters.h>
#include <k52/optimization/params/int_parameter.h>

namespace k52
{
namespace optimization
{

class DoubleParameter : public ConstChromosomeSizeParemeters
{
public:
    typedef boost::shared_ptr<DoubleParameter> shared_ptr;

    DoubleParameter();

    DoubleParameter(double desired_value, double min_value, double max_value, double desired_precision);

    DoubleParameter* Clone() const;

    bool CheckConstraints() const;

    void SetChromosome(std::vector<bool>::iterator from, std::vector<bool>::iterator to) const;

    void SetFromChromosome(std::vector<bool>::const_iterator from, std::vector<bool>::const_iterator to);

    double GetValue() const;
    void SetValue(double value);

    double get_max_value() const;
    double get_min_value() const;
    double get_actual_precision() const;

protected:
    static int GetMaxInt(double min_value, double max_value, double precision);
    static int CountBestMaxInt(int initial_max_int);
    bool CheckBounds(double value) const;

private:
    IntParameter::shared_ptr base_int_parameter_;
    double min_value_;
    double max_value_;
    double precision_;

    DISALLOW_COPY_AND_ASSIGN(DoubleParameter);
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* DOUBLEPARAMETER_H_ */
