/*
 * IContinuousParameters.h
 *
 *  Created on: May 20, 2012
 *      Author: feanor
 */

#ifndef ICONTINUOUSPARAMETERS_H_
#define ICONTINUOUSPARAMETERS_H_

#include "IParameters.h"

class IContinuousParameters: public IParameters
{
public:
	virtual ~IContinuousParameters() {}

	virtual void setValues(const std::vector<double>& values) = 0;

	virtual std::vector<double> getValues() const = 0;

	virtual bool checkConstraints() const = 0;

	virtual IContinuousParameters* clone() const = 0;
};

#endif /* ICONTINUOUSPARAMETERS_H_ */
