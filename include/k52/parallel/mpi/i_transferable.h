#ifndef ITRANSFERABLE_H_
#define ITRANSFERABLE_H_

#include <k52/parallel/mpi/boost_mpi_declaration.h>

namespace k52
{
namespace parallel
{
namespace mpi
{

class ITransferable
{
public:
    virtual ~ITransferable() { }

    virtual void Send(boost::mpi::communicator* communicator, int target) const = 0;

    virtual void Receive(boost::mpi::communicator* communicator, int source) = 0;
};

} /* namespace mpi */
} /* namespace parallel */
} /* namespace k52 */

#endif /* ITRANSFERABLE_H_ */
