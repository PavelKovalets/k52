/*
 * Individual.h
 *
 *  Created on: Jan 30, 2012
 *      Author: feanor
 */

#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <optimize/params/IParameters.h>
#include <optimize/InitializationChecker.h>
#include <optimize/params/DiscreteParameters.h>
#include <ostream>
//TODO make private

/**
@class IndividualStatistics
Represents statistics about sungle individual
 */
struct IndividualStatistics
{
	double Fitness;
	int TimesChosenForCrossover;	

	static bool less (IndividualStatistics const& leftArg, IndividualStatistics const& rightArg)
	{
		return leftArg.TimesChosenForCrossover < rightArg.TimesChosenForCrossover;
	}

	static bool greater (IndividualStatistics const& leftArg, IndividualStatistics const& rightArg)
	{
		return leftArg.TimesChosenForCrossover > rightArg.TimesChosenForCrossover;
	}
};

/**
 @class Individual
 Encapsulates single chromosome logic in Genetic Algorithm.
 Local parameters and chromosome of an Individual are always synchronized
 */
class Individual
{
public:
    ///Creates an Individual without initialization.
	///For further usage initialize method of this Individual MUST be called.
	///Otherwise exception will be thrown.
	Individual();

    ///Creates an Individual and initializes it
    ///@param parameters - parameters to be copied locally during initialization
    Individual(const IDiscreteParameters* const parameters);

    ///Creates a copy of an Individual
    ///@param a - Individual to copy
	Individual(const Individual& a);

	///Creates a copy of an Individual
	///@param a - Individual to copy
	Individual& operator =(const Individual& a);

	///Creates a local copy of parameters and sets chromosome according to them.
	///MUST be called only once, otherwise exception will be thrown.
	///@param parameters - parameters to be copied locally
	void initialize(const IDiscreteParameters* const parameters);

	///Gets a pointer to constant local parameters
	///@return local parameters synchronized with current state of chromosome
	const IDiscreteParameters* const getParametersAccordingToChromosome() const;

	///Gets Chromosome from current individual
	///@return Chromosome representation of current individual
	///ATTENTION! Returned value refferes to the inner variable of this
	///individual and no longer valid and MUST NOT be used
	///when this individual's destructor is called
	const vector<bool>& getChromosome() const;

	///Set random chromosome for current Individual and synchronizes it with local parameters
	///@return number of invalid chromosomes, generated during setting random chromosome
	int setRandomChromosome();

	///Performs random crossover with this and another Individuals.
	///After crossover both will be changed to new (so called child) Individuals.
	///@param another - an Individual to crossover this with
	///@return true if both children are valid (satisfy conditions) otherwize false
	bool crossover(Individual* another);

	///Performs random mutation of an Individual
	///@param genMutationProbability - mutation probability per one boolean gen
	///@return number of invalid chromosomes, generated during mutate
	int mutate(double genMutationProbability);

	///@return fitness counted for this Individual (if hasFitness() method returns true, otherwise throws an exception because fitness was not counted)
    double getFitness() const;

    ///@return true if fitness was counted for this Individual, otherwise - false
    bool hasFitness() const;

    ///@param fitness - fitness counted for this Individual' current state
    void setFitness(double fitness);

	///Fitness must be already counted, otherwize exception is thrown
	///@return current individual's statistics
	IndividualStatistics getIndividualStatistics() const;

	///@return number of times this individual was chosen for crossover
	int getTimesChosenForCrossover() const;

	///This function should be called when this individual is chosen for crossover
	void increaseTimesChosenForCrossover();

	///This function should be called when next generation is ready
	void resetTimesChosenForCrossover();

private:
    InitializationChecker  _initializationChecker;
	IDiscreteParameters::shared_ptr _parametersStorage;
	vector<bool> _chromosome;

	bool _hasFitness;
	double _fitness;
	int _timesChosenForCrossover;

	void setParametersAccordingToChromosome();

	///Throws exception if Individual does not still have counted fitness
	void checkForHavingFitness() const;

	static void boolCrossover(vector<bool> *first, vector<bool> *second);

	friend std::ostream& operator<< (std::ostream& out, const Individual& individual);
	
	friend std::istream& operator>> (std::istream& in, Individual& individual);
};



#endif /* INDIVIDUAL_H_ */
