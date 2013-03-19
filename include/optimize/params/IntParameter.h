/*
 * IntParameter.h
 *
 *  Created on: Jan 29, 2012
 *      Author: feanor
 */

#ifndef INTPARAMETER_H_
#define INTPARAMETER_H_

#include "const_chromosome_size_paremeters.h"

namespace k52
{
namespace optimize
{

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

	IntParameter* Clone() const;

	bool CheckConstraints() const;

	void SetChromosome(std::vector<bool>::iterator from, std::vector<bool>::iterator to) const;

	void SetFromChromosome(std::vector<bool>::const_iterator from, std::vector<bool>::const_iterator to);
private:

	int _value;
	int _maxValue;
	int _minValue;

	static size_t countVectorSize(int minValue, int maxValue);
	static int getIntFromBoolVector(std::vector<bool>::const_iterator from, std::vector<bool>::const_iterator to);
	static void setBoolVectorFromInt(std::vector<bool>::iterator from, std::vector<bool>::iterator to, int value);

};

}/* namespace optimize */
}/* namespace k52 */

#endif /* INTPARAMETER_H_ */
