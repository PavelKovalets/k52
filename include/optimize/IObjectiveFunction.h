/*
 * IObjectiveFunction.h
 *
 *  Created on: Mar 9, 2012
 *      Author: feanor
 */

#ifndef IOBJECTIVEFUNCTION_H_
#define IOBJECTIVEFUNCTION_H_

#include <optimize/params/IParameters.h>
#ifdef BUILD_WITH_MPI
#include <common/ICloneable.h>
#endif

using ::k52::optimize::params::IParameters;

namespace k52
{
namespace optimize
{

/**
@class IObjectiveFunction
Functor that counts objective function value
*/
class IObjectiveFunction
#ifdef BUILD_WITH_MPI
	  :public k52::common::ICloneable
#endif
{
public:
	///Virtual destructor for correct deallocation of resources in derived classes
	virtual ~IObjectiveFunction() {}

	///Operator that implements counting of objective function value
	///@param parameters - parameters to count objective function value for
	virtual double operator () (const IParameters* const parameters) const = 0;
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* IOBJECTIVEFUNCTION_H_ */