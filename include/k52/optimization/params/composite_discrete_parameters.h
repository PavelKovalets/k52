#ifndef COMPOSITEDISCRETEPARAMETERS_H_
#define COMPOSITEDISCRETEPARAMETERS_H_

#include <k52/optimization/initialization_checker.h>
#include <k52/optimization/params/const_chromosome_size_paremeters.h>

namespace k52
{
namespace optimization
{

class DiscreteParametersLocalStorage;

class CompositeDiscreteParameters: public ConstChromosomeSizeParemeters
{
public:
    typedef boost::shared_ptr<CompositeDiscreteParameters> shared_ptr;

    CompositeDiscreteParameters* Clone() const;

    bool CheckConstraints() const;

    void SetChromosome(ChromosomeType::iterator from, ChromosomeType::iterator to) const;

    void SetFromChromosome(ChromosomeType::const_iterator from, ChromosomeType::const_iterator to);

    void Initialize(const std::vector<IDiscreteParameters::shared_ptr>& parameters);

    void Initialize(const IDiscreteParameters::shared_ptr& sample_parameter, size_t number_of_parameters);

    size_t GetNumberOfParameters() const;

    const IDiscreteParameters::shared_ptr GetParameter(size_t index) const;

private:
    size_t CountTotalChromosomeSize() const;

    std::vector<IDiscreteParameters::shared_ptr> parameters_set_;
    InitializationChecker initialization_checker_;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* COMPOSITEDISCRETEPARAMETERS_H_ */
