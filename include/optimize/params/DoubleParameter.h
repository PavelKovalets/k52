/*
 * DoubleParameter.h
 *
 *  Created on: Mar 22, 2012
 *      Author: feanor
 */

#ifndef DOUBLEPARAMETER_H_
#define DOUBLEPARAMETER_H_

#include "int_parameter.h"
#include "const_chromosome_size_paremeters.h"

namespace k52
{
namespace optimize
{

class DoubleParameter : public ConstChromosomeSizeParemeters
{
public:
	typedef boost::shared_ptr<DoubleParameter> shared_ptr;

	DoubleParameter(double desiredValue, double minValue, double maxValue, double desiredPrecision);

	DoubleParameter(const DoubleParameter& a);

	DoubleParameter();

	DoubleParameter& operator=(const DoubleParameter & a);

	DoubleParameter* Clone() const;

	bool CheckConstraints() const;

	void SetChromosome(std::vector<bool>::iterator from, std::vector<bool>::iterator to) const;

	void SetFromChromosome(std::vector<bool>::const_iterator from, std::vector<bool>::const_iterator to);

    double getValue() const;
    double getMaxValue() const;
    double getMinValue() const;
	double getActualPrecision() const;

protected:
    static int getMaxInt( double minValue, double maxValue, double precision);
	static int CountBestMaxInt(int initialMaxInt);
	bool checkBounds(double value) const;

private:
	double _minValue;
	double _maxValue;
	double _precision;

	IntParameter::shared_ptr _baseIntParameter;
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* DOUBLEPARAMETER_H_ */
