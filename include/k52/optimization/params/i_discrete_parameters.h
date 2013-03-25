#ifndef IDISCRETEPARAMETERS_H_
#define IDISCRETEPARAMETERS_H_

#include <k52/optimization/i_convertable_to_chromosome.h>
#include <k52/optimization/params/i_parameters.h>

namespace k52
{
namespace optimize
{

class IDiscreteParameters: public IParameters, IConvertableToChromosome
{
public:
    typedef boost::shared_ptr<IDiscreteParameters> shared_ptr;

    virtual ~IDiscreteParameters() {}

    virtual void SetChromosome(std::vector<bool>::iterator from, std::vector<bool>::iterator to) const = 0;

    virtual void SetFromChromosome(std::vector<bool>::const_iterator from, std::vector<bool>::const_iterator to) = 0;

    virtual size_t GetChromosomeSize() const = 0;

    virtual IDiscreteParameters* Clone() const = 0;

#ifdef BUILD_WITH_MPI
    virtual void Send(boost::mpi::communicator* communicator, int target) const = 0;

    virtual void Receive(boost::mpi::communicator* communicator) = 0;
#endif
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* IDISCRETEPARAMETERS_H_ */
