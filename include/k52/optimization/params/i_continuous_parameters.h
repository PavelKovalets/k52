#ifndef ICONTINUOUSPARAMETERS_H_
#define ICONTINUOUSPARAMETERS_H_

#include <vector>

#include <k52/optimization/params/i_parameters.h>

namespace k52
{
namespace optimization
{

class IContinuousParameters: public IParameters
{
public:
    typedef boost::shared_ptr<IContinuousParameters> shared_ptr;

    virtual ~IContinuousParameters() {}

    virtual void SetValues(const std::vector<double>& values) = 0;

    virtual std::vector<double> GetValues() const = 0;

    virtual bool CheckConstraints() const = 0;

    virtual IContinuousParameters* Clone() const = 0;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* ICONTINUOUSPARAMETERS_H_ */
