/*
 * Random.h
 *
 *  Created on: Jan 29, 2012
 *      Author: feanor
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include <vector>

/**
@class Random
Provides methods to generate random quantities
*/
class Random
{
public:
	/// Implementation of singleton pattern to avoid multiple seed
	/// @return the only instance of Random class
	static Random& Instance();

	///Generates base random quantity - uniformly distributed on interval [0, 1]
	///@return base random quantity
	double getBaseRandomQuantity();

	///Generates continuous random quantity - uniformly distributed on interval [minValue, maxValue]
	///@param minValue - interval lower bound
	///@param maxValue - interval upper bound 
	///@return base random quantity
	double getContinuousRandomQuantity(double minValue, double maxValue);

	///Generates uniformly distributed boolean - 0.5 to true, 0.5 to false
	///@return random boolean
	bool getRandomBool();

	///Sets vector to uniformly distributed booleans - 0.5 to true, 0.5 to false
	///@param array - vector to be set for random boolean values
	void setRandomBoolVector(std::vector<bool>* array);

	///Generates uniformly distributed discrete random quantity within specified interval
	///@param minValue - interval lower bound
	///@param maxValue - interval upper bound
	///@return random integer between minValue and maxValue
	int getUniformlyDistributedDiscreteRandomQuantity(int minValue, int maxValue);

private:
	Random();
	int GetNextBitFromBoolBase();

	int _boolBase;
	int _nextBitInBoolBase;
	int _maxBitInBoolBase;
};

#endif /* RANDOM_H_ */
