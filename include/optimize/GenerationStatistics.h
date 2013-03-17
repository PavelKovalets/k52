/*
 * GenerationStatistics.h
 *
 *  Created on: Mar 10, 2012
 *      Author: feanor
 */

#ifndef GENERATIONSTATISTICS_H_
#define GENERATIONSTATISTICS_H_

#include <list>
#include <string>
#include <optimize/IndividualStatistics.h>
#include <optimize/params/IParameters.h>

namespace k52
{
namespace optimize
{

/**
@class GenerationStatistics
Represents statistics about Genetic Algorithm population
 */
class GenerationStatistics
{
public:
	///Creates GenerationStatistics instance and copies currentlyBestParameters to it
	GenerationStatistics(double averageFithess,
			const IParameters* const bestParameters,
			double bestFitness,
			size_t numberOfGeneration,
			int cacheHits,
			int invalidChromosomes,
			std::list<std::string>* filesToSave,
			std::list<IndividualStatistics> allIndividualsStatistics);

	///Creates a copy of a GenerationStatistics
	///@param a - GenerationStatistics to copy
	GenerationStatistics(const GenerationStatistics& a);

	///Creates a copy of an GenerationStatistics
	///@param a - GenerationStatistics to copy
	GenerationStatistics& operator =(const GenerationStatistics& a);

	///@return average fitness value of current population (or generation)
	double getAverageFithess() const;

	///@return sequential number of current population (or generation)
	size_t getNumberOfGeneration() const;

	///@return number of hits to the fitness cache for current population (or generation)
	int getCacheHits() const;

	///@return number of invalid chromosomes generated during current population (or generation)
	int getInvalidChromosomes() const;

	///Returns the best parameters during current population (or generation)
	///@return - parameters to be set to the best values
	///ATTENTION! Returned value points to the inner variable of this
	///GenerationStatistics object and no longer valid and MUST NOT be used
	///when this GenerationStatistics object's destructor is called
	const IParameters* const getBestParameters() const;

	///Returns fitness for parameters, returned by getBestParameters() method
	///@return - fitness, counted for the best parameters during current population (or generation)
    double getBestFitness() const;

	///Indicates that current population should be saved to file
	///ATTENTION! Saving itself will not occur immediatelly, but only after all NextGenerationReadyCallback functions will be called
	///It is garanteed only that it will be saved before next call to current NextGenerationReadyCallback function
	///@param fileName - name of file save population to
	void saveCurrentPopulationToFile(std::string fileName);

	///@return statistics for all individuals in current population
	std::list<IndividualStatistics> getAllIndividualsStatistics() const;

private:
	int _cacheHits;
	int _invalidChromosomes;
	size_t _numberOfGeneration;
	double _averageFithess;
	double _bestFitness;
	IParameters::shared_ptr _bestParametersStorage;
	std::list<IndividualStatistics> _allIndividualsStatistics;
	std::list<std::string>* _filesToSave;
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* GENERATIONSTATISTICS_H_ */
