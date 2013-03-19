/*
 * IOptimizer.h
 *
 *  Created on: Jan 29, 2012
 *      Author: feanor
 */

#ifndef IOPTIMIZER_H_
#define IOPTIMIZER_H_

#include <optimize/i_objective_function.h>

namespace k52
{
namespace optimize
{

/**
@class IOptimizer
Provides optimization of certain objective function
over the parameters within the bounds of certain constraints.
Optimization is performed in terms of minimization or maximization
*/
class IOptimizer
{
public:
	///Virtual destructor for correct deallocation of resources in derived classes
	virtual ~IOptimizer() {}

	///Performs optimization of parametrsToOptimize according to functionToOptimize
	///@param parametrsToOptimize - this will be set to the optimal values after method's invocation
	///@param functionToOptimize - the target function to be optimized for maximum
	virtual void optimize(IParameters* parametrsToOptimize, const IObjectiveFunction &functionToOptimize) = 0;
};


}/* namespace optimize */
}/* namespace k52 */

#endif /* IOPTIMIZER_H_ */
