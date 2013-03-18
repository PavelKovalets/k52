/*
 * IParameters.h
 *
 *  Created on: Feb 27, 2012
 *      Author: feanor
 */

#ifndef IPARAMETERS_H_
#define IPARAMETERS_H_

#include <common/i_cloneable.h>
#include <optimize/IConvertableToChromosome.h>

#ifdef BUILD_WITH_MPI
#include <parallel/mpi/ITransferable.h>
#endif

namespace k52
{
namespace optimize
{

/**
@class IParameters
Encapsulates optimization parameters and constraints logic.
May be used to represent multiple as well as single parameter.
Also can be used as a basic interface for pattern Conpositor:
Class wich derives from IParameters will also contain a collection
of IParameters and extend their behaviour by adding additional constraints etc.
*/
class IParameters
	: public k52::common::ICloneable
#ifdef BUILD_WITH_MPI
	  ,public k52::parallel::mpi::ITransferable
#endif
{
public:
	typedef boost::shared_ptr<IParameters> shared_ptr;

	///Virtual destructor for correct deallocation of resources in derived classes
	virtual ~IParameters() {}

	///Checks all constraints to be satisfied for currently set value(s) of parameter(s)
	///@return TRUE if constraints are satisfied, otherwise FALSE
	virtual bool checkConstraints() const = 0;

	///Creates deep clone of an object with resource allocation. See ICloneable
	///@return deep clone of an object
	virtual IParameters* Clone() const = 0;

#ifdef BUILD_WITH_MPI
	virtual void send(boost::mpi::communicator* communicator, int target) const = 0;

	virtual void receive(boost::mpi::communicator* communicator) = 0;
#endif
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* IPARAMETERS_H_ */
