/*
 * Mutator.h
 *
 *  Created on: Apr 1, 2012
 *      Author: feanor
 */

#ifndef MUTATOR_H_
#define MUTATOR_H_

#include <vector>

class Mutator
{
public:
	/// Implementation of singleton pattern
	/// @return the only instance of Mutator class
	static Mutator& Instance();

	void mutateBoolArray(double genMutationProbability, std::vector<bool>* array);

private:
	bool _wasProbabilitySet;
	double _mutationProbability;
	int _maxNumberOfSkippedGens;
	int _gensToSkipNow;
	int _currentlySkippedGens;

	void setMutationProbability(double genMutationProbability);
	void setGensToSkipNow();

	Mutator();
};

#endif /* MUTATOR_H_ */
