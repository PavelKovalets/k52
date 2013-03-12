/*
 * BruteForceSearch.cpp
 *
 *  Created on: Jan 30, 2012
 *      Author: feanor
 */

#include "BruteForceSearch.h"
/*
void BruteForceSearch::optimize(IParameters* parametrsToOptimize, const IObjectiveFunction &functionToOptimize)
{
	size_t size = parametrsToOptimize->getChromosome().size();
	vector<bool> boolArrayToSearch(size), result(size);

	result = runThroughAllBits(size, boolArrayToSearch, parametrsToOptimize, functionToOptimize, &_bestFitness);

	parametrsToOptimize->setFromChromosome(result);
}

double BruteForceSearch::getBestFitness()
{
	return _bestFitness;
}

//Returns best set of parameters in binary form and its fitness in bestFitness
vector<bool> BruteForceSearch::runThroughAllBits(
		int indexToBeginWith,
		vector<bool> boolArrayToSearch,
		IParameters* parametrsToOptimize,
		const IObjectiveFunction &functionToOptimize,
		double *bestFitness)
{
	double trueFit = 0, falseFit = 0;
	vector<bool> trueResult, falseResult;

	if(indexToBeginWith > 0)
	{
		boolArrayToSearch[indexToBeginWith] = true;
		trueResult = runThroughAllBits(
				indexToBeginWith-1,
				boolArrayToSearch,
				parametrsToOptimize,
				functionToOptimize,
				&trueFit);

		boolArrayToSearch[indexToBeginWith] = false;
		falseResult = runThroughAllBits(
				indexToBeginWith-1,
				boolArrayToSearch,
				parametrsToOptimize,
				functionToOptimize,
				&falseFit);

	}
	else if(indexToBeginWith == 0)
	{
		//All bits are ready => count fitness
		parametrsToOptimize->setFromChromosome(boolArrayToSearch);

		if(!parametrsToOptimize->checkConstraints())
		{
			*bestFitness = -1;
		}
		else
		{
			*bestFitness = functionToOptimize(parametrsToOptimize);
		}

		return boolArrayToSearch;
	}

	if( trueFit > falseFit )
	{
		*bestFitness = trueFit;
		return trueResult;
	}
	else
	{
		*bestFitness = falseFit;
		return falseResult;
	}
}
*/

