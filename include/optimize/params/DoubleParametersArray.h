/*
 * DoubleParametersArray.h
 *
 *  Created on: Mar 25, 2012
 *      Author: feanor
 */

#ifndef DOUBLEPARAMETERSARRAY_H_
#define DOUBLEPARAMETERSARRAY_H_

#include "DiscreteParameters.h"
#include "DoubleParameter.h"
#include "CompositeDiscreteParameters.h"
#include "ConstChromosomeSizeParemeters.h"

namespace k52
{
namespace optimize
{

class DoubleParametersArray : public DiscreteParameters
{
public:
	typedef boost::shared_ptr<DoubleParametersArray> shared_ptr;

	DoubleParametersArray(double minValue, double maxValue, double desiredPrecision, size_t numberOfParameters);

	DoubleParametersArray* Clone() const;

	bool checkConstraints() const;

	size_t getChromosomeSize() const;

	void setChromosome(std::vector<bool>::iterator from, std::vector<bool>::iterator to) const;

	void setFromChromosome(std::vector<bool>::const_iterator from, std::vector<bool>::const_iterator to);

    double getMaxValue() const;
    double getMinValue() const;
    size_t getNumberOfParameters() const;
    double getActualPrecision() const;
    std::vector<double> getValues() const;

protected:
    const DoubleParameter::shared_ptr getDoubleParameter(size_t index) const;

private:
	double _minValue;
	double _maxValue;
	double _desiredPrecision;

	CompositeDiscreteParameters::shared_ptr _doubleParameters;
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* DOUBLEPARAMETERSARRAY_H_ */
