/*
 * DoubleParameter.h
 *
 *  Created on: Mar 22, 2012
 *      Author: feanor
 */

#ifndef DOUBLEPARAMETER_H_
#define DOUBLEPARAMETER_H_

#include "IntParameter.h"
#include "ConstChromosomeSizeParemeters.h"

class DoubleParameter : public ConstChromosomeSizeParemeters
{
public:
	typedef boost::shared_ptr<DoubleParameter> shared_ptr;

	DoubleParameter(double value, double minValue, double maxValue, double desiredPrecision);

	DoubleParameter(const DoubleParameter& a);

	DoubleParameter();

	~DoubleParameter();

	DoubleParameter& operator=(const DoubleParameter & a);

	DoubleParameter* clone() const;

	bool checkConstraints() const;

	void setChromosome(vector<bool>::iterator from, vector<bool>::iterator to) const;

	void setFromChromosome(vector<bool>::const_iterator from, vector<bool>::const_iterator to);

    double getValue() const;
    void setValue(double value);
    double getMaxValue() const;
    double getMinValue() const;
	double getActualPrecision() const;

//    void printBinaryValue();
protected:
    static int getMaxInt( double minValue, double maxValue, double precision);
	static int CountBestMaxInt(int initialMaxInt);

private:
	double _value;
	double _minValue;
	double _maxValue;
	double _precision;

	IntParameter* _baseIntParameter;
};

#endif /* DOUBLEPARAMETER_H_ */
