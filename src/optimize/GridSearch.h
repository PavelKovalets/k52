/*
 * GridSearch.h
 *
 *  Created on: May 20, 2012
 *      Author: feanor
 */

#ifndef GRIDSEARCH_H_
#define GRIDSEARCH_H_

#include <optimize/IOptimizer.h>
#include "ObjectiveFunctionCounter.h"

#include <common/disallow_copy_and_assign.h>

namespace k52
{
namespace optimize
{

class GridSearch: public IOptimizer
{
public:
	GridSearch(double precision, double lowerBound, double upperBound, int numberOfThreads);

	virtual void optimize(IParameters* parametrsToOptimize, const IObjectiveFunction &functionToOptimize);

protected:
	static size_t integerPow(size_t value, size_t pow);

private:
	double _precision;
	double _lowerBound;
	double _upperBound;

	ObjectiveFunctionCounter _fitnessCounter;
	DISALLOW_COPY_AND_ASSIGN(GridSearch);
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* GRIDSEARCH_H_ */
