#ifndef COMPOSITEDISCRETEPARAMETERS_H_
#define COMPOSITEDISCRETEPARAMETERS_H_

#include <vector>

#include <optimize/initialization_checker.h>
#include <optimize/params/const_chromosome_size_paremeters.h>

namespace k52
{
namespace optimize
{

class DiscreteParametersLocalStorage;

class CompositeDiscreteParameters: public ConstChromosomeSizeParemeters
{
public:
    typedef boost::shared_ptr<CompositeDiscreteParameters> shared_ptr;

    CompositeDiscreteParameters* Clone() const;

    bool CheckConstraints() const;

    void SetChromosome(std::vector<bool>::iterator from, std::vector<bool>::iterator to) const;

    void SetFromChromosome(std::vector<bool>::const_iterator from, std::vector<bool>::const_iterator to);

    void Initialize(std::vector<IDiscreteParameters::shared_ptr> parameters);

    size_t GetNumberOfParameters() const;

    const IDiscreteParameters::shared_ptr GetParameter(size_t index) const;

private:
    size_t CountTotalChromosomeSize() const;

    std::vector<IDiscreteParameters::shared_ptr> parameters_set_;
    InitializationChecker initialization_checker_;
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* COMPOSITEDISCRETEPARAMETERS_H_ */
