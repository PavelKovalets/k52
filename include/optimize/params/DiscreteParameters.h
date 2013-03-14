/*
 * DiscreteParameters.h
 *
 *  Created on: Jan 31, 2013
 *      Author: pavel
 */

#ifndef DISCRETEPARAMETERS_H_
#define DISCRETEPARAMETERS_H_

#include <optimize/params/IDiscreteParameters.h>

namespace k52
{
namespace optimize
{
namespace params
{

class DiscreteParameters : public IDiscreteParameters
{
public:
	typedef boost::shared_ptr<DiscreteParameters> shared_ptr;

	virtual ~DiscreteParameters() {}

	virtual void setChromosome(vector<bool>::iterator from, vector<bool>::iterator to) const = 0;

	virtual void setFromChromosome(vector<bool>::const_iterator from, vector<bool>::const_iterator to) = 0;

	virtual size_t getChromosomeSize() const = 0;

	virtual IDiscreteParameters* clone() const = 0;

#ifdef BUILD_WITH_MPI
	virtual void send(boost::mpi::communicator* communicator, int target) const;

	virtual void receive(boost::mpi::communicator* communicator);
#endif
};

}/* namespace params */
}/* namespace optimize */
}/* namespace k52 */

#endif /* DISCRETEPARAMETERS_H_ */
