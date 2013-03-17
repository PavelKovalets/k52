/*
 * GenerationStatistics.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: feanor
 */

#include <optimize/GenerationStatistics.h>
#include <cstddef>

using ::std::list;

namespace k52
{
namespace optimize
{

GenerationStatistics::GenerationStatistics(double averageFithess,
		const IParameters* const bestParameters,
		double bestFitness,
		size_t numberOfGeneration,
		int cacheHits,
		int invalidChromosomes,
		list<std::string>* filesToSave,
		list<IndividualStatistics> allIndividualsStatistics)
{
	_bestParametersStorage = IParameters::shared_ptr( bestParameters->clone() );
	_invalidChromosomes = invalidChromosomes;
	_cacheHits = cacheHits;
	_numberOfGeneration = numberOfGeneration;
	_averageFithess = averageFithess;
	_bestFitness = bestFitness;
	_filesToSave = filesToSave;
	_allIndividualsStatistics = allIndividualsStatistics;
}

void GenerationStatistics::saveCurrentPopulationToFile(std::string fileName)
{
	_filesToSave->push_back(fileName);
}

GenerationStatistics::GenerationStatistics(const GenerationStatistics& a)
{
	*this = a;
}

GenerationStatistics& GenerationStatistics::operator=(const GenerationStatistics & a)
{
	if (this != &a) // protect against invalid self-assignment
	{
		_bestParametersStorage = IParameters::shared_ptr( a._bestParametersStorage->clone() );
		_averageFithess = a._averageFithess;
		_numberOfGeneration = a._numberOfGeneration;
		_cacheHits = a._cacheHits;
		_invalidChromosomes = a._invalidChromosomes;
		_bestFitness = a._bestFitness;
		_filesToSave = a._filesToSave;
		_allIndividualsStatistics = a._allIndividualsStatistics;
	}
	// by convention, always return *this
	return *this;
}

double GenerationStatistics::getAverageFithess() const
{
	return _averageFithess;
}

size_t GenerationStatistics::getNumberOfGeneration() const
{
	return _numberOfGeneration;
}

const IParameters* const GenerationStatistics::getBestParameters() const
{
	//TODO FIX do not return inner ptr
	return _bestParametersStorage.get();
}

int GenerationStatistics::getCacheHits() const
{
    return _cacheHits;
}

int GenerationStatistics::getInvalidChromosomes() const
{
    return _invalidChromosomes;
}

double GenerationStatistics::getBestFitness() const
{
	return _bestFitness;
}

list<IndividualStatistics> GenerationStatistics::getAllIndividualsStatistics() const
{
	return _allIndividualsStatistics;
}

}/* namespace optimize */
}/* namespace k52 */
