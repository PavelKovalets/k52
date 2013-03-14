/*
 * GeneticAlgorithm.h
 *
 *  Created on: Jan 29, 2012
 *      Author: feanor
 */

#ifndef GENETICALGORITHM_H_
#define GENETICALGORITHM_H_

#include <optimize/IOptimizer.h>
#include <optimize/params/IDiscreteParameters.h>
#include "Individual.h"
#include "GenerationStatistics.h"
#include <boost/shared_ptr.hpp>

namespace k52
{
namespace optimize
{

class ObjectiveFunctionCounter;

typedef void (*NextGenerationReadyCallback)(GenerationStatistics);

/**
 @class GeneticAlgorithm
Performs evolutionary optimization.
Best individual of all generations is selected and returned as result.
 */
class GeneticAlgorithm: public IOptimizer
{
public:
	///Creates an instance of GA with specified parameters
	///@param populationSize - size of population that will be used during GA
	///@param elitismPairs - number of best pairs in population to be copied to the next population every time 
	///(for example if elitismPairs=1, 2 best individs will be transfered to the next population)
	///@param maxNumberOfGenerations - maximum number of generations for population. One of the stop criteria.
	///@param numberOfThreads - to use for fitness count (if <= 0 - fitness will be counted sequentially).
	///@param fitnessStopCriteria - the value of objective function witch consider to be optimal and further optimization has no need. One of the stop criteria.
	///@param mutationProbability - mutation probability per one boolean gen in chromosome
	///@param populationFileName - file to load population from(if no load is needed - pass empty string or ignore)
	GeneticAlgorithm(int populationSize,
			int elitismPairs,
			int maxNumberOfGenerations,
			int numberOfThreads = -1,
			bool useFitnessValueCaching = false,
			double fitnessStopCriteria = 10000000,
			double mutationProbability = 0.005,
			std::string populationFileName = "");

	void optimize(IParameters* parametrsToOptimize, const IObjectiveFunction &functionToOptimize);

	void onNextGenerationReadyConnect(NextGenerationReadyCallback);

protected:
	void fireNextGenerationReady(GenerationStatistics statistics);
	double getPopulationAveradgeFitness();
	void initialize(IDiscreteParameters* parametrsToOptimize);
	void mutate();
	void countFitness(const IObjectiveFunction &functionToOptimize);
	void countFitnessParallel(const IObjectiveFunction &functionToOptimize);
	void printPopulation();
	void generateNextPopulation();
	void savePopulationToFile(std::string populationFileName);
	void outputPopulation(std::ostream & out);
	void readPopulationFromFile();
	void inputPopulation(std::ifstream & in);
	int selectRandomIndividualIndexForCrossover(double totalFitness);
	void gatherAllIndividualsStatistics();
	static bool greaterFitness(const Individual* first, const Individual* second);

private:

	GeneticAlgorithm();

	double _fitnessStopCriteria ;
	double _mutationProbability;
	int  _elitismPairs;
	int _maxNumberOfGenerations;
	int _populationSize;
	int _invalidChromosomes;
	vector<Individual> _population;
	vector<IndividualStatistics> _populationStatistics;
	std::string _populationFileName;

	Individual _bestIndivid;

	NextGenerationReadyCallback _callbackFunction;
	boost::shared_ptr<ObjectiveFunctionCounter> _fitnessCounter;
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* GENETICALGORITHM_H_ */
