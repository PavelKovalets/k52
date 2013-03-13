/*
 * IntParameter.h
 *
 *  Created on: Jan 29, 2012
 *      Author: feanor
 */

#ifndef INTPARAMETER_H_
#define INTPARAMETER_H_

#include "ConstChromosomeSizeParemeters.h"

/**
@class IntParameter
Represents simple integer parameter with upper and lower bound.
*/
class IntParameter: public ConstChromosomeSizeParemeters
{
public:
	typedef boost::shared_ptr<IntParameter> shared_ptr;

	///Creates an instance of IntParameter
	///@param value - value of IntParameter to be set initially
	///@param minValue - minimum allowed value of IntParameter, it's lower bound constraint
	///@param maxValue - maximum allowed value of IntParameter, it's upper bound constraint
	IntParameter(int value, int minValue, int maxValue);

	///@return current value of IntParameter
	int getValue() const;

	///@return maximum allowed value of IntParameter
	int getMaxValue() const;

	///@return minimum allowed value of IntParameter
	int getMinValue() const;

	IntParameter* clone() const;

	bool checkConstraints() const;

	void setChromosome(vector<bool>::iterator from, vector<bool>::iterator to) const;

	void setFromChromosome(vector<bool>::const_iterator from, vector<bool>::const_iterator to);
private:

	int _value;
	int _maxValue;
	int _minValue;

	static size_t countVectorSize(int minValue, int maxValue);
	static int getIntFromBoolVector(vector<bool>::const_iterator from, vector<bool>::const_iterator to);
	static void setBoolVectorFromInt(vector<bool>::iterator from, vector<bool>::iterator to, int value);

};

#endif /* INTPARAMETER_H_ */
