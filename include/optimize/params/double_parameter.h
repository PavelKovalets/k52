#ifndef DOUBLEPARAMETER_H_
#define DOUBLEPARAMETER_H_

#include <optimize/params/const_chromosome_size_paremeters.h>
#include <optimize/params/int_parameter.h>

namespace k52
{
namespace optimize
{

class DoubleParameter : public ConstChromosomeSizeParemeters
{
public:
    typedef boost::shared_ptr<DoubleParameter> shared_ptr;

    DoubleParameter();

    DoubleParameter(double desired_value, double min_value, double max_value, double desired_precision);

    DoubleParameter(const DoubleParameter& a);

    DoubleParameter& operator=(const DoubleParameter & a);

    DoubleParameter* Clone() const;

    bool CheckConstraints() const;

    void SetChromosome(std::vector<bool>::iterator from, std::vector<bool>::iterator to) const;

    void SetFromChromosome(std::vector<bool>::const_iterator from, std::vector<bool>::const_iterator to);

    double GetValue() const;

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
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* DOUBLEPARAMETER_H_ */
