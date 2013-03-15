/*
 * Mutator.h
 *
 *  Created on: Apr 1, 2012
 *      Author: feanor
 */

#ifndef MUTATOR_H_
#define MUTATOR_H_

#include <vector>
#include <common/disallow_copy_and_assign.h>

namespace k52
{
namespace optimize
{

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
	DISALLOW_COPY_AND_ASSIGN(Mutator);
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* MUTATOR_H_ */
