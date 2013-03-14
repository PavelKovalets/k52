/*
 * BruteForceSearch.h
 *
 *  Created on: Jan 30, 2012
 *      Author: feanor
 */

#ifndef BRUTEFORCESEARCH_H_
#define BRUTEFORCESEARCH_H_

#include <optimize/IOptimizer.h>

namespace k52
{
namespace optimize
{

/**
@class BruteForceSearch
Performs optimization via brute force search.
Simple enumeration of all possible chromosomes is done.
*//*
class BruteForceSearch: public IOptimizer
{
public:
	void optimize(IParameters* parametrsToOptimize, const IObjectiveFunction &functionToOptimize);

	/// @return best objective function value of last applied optimize method's result
	double getBestFitness();

private:
	double _bestFitness;

	static vector<bool> runThroughAllBits(
			int indexToBeginWith,
			vector<bool> boolArrayToSearch,
			IParameters* parametrsToOptimize,
			const IObjectiveFunction &functionToOptimize,
			double *bestFitness);
};
*/

}/* namespace optimize */
}/* namespace k52 */
#endif /* BRUTEFORCESEARCH_H_ */
