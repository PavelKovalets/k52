/*
 * IContinuousParameters.h
 *
 *  Created on: May 20, 2012
 *      Author: feanor
 */

#ifndef ICONTINUOUSPARAMETERS_H_
#define ICONTINUOUSPARAMETERS_H_

#include <vector>

#include "IParameters.h"

namespace k52
{
namespace optimize
{

class IContinuousParameters: public IParameters
{
public:
	typedef boost::shared_ptr<IContinuousParameters> shared_ptr;

	virtual ~IContinuousParameters() {}

	virtual void setValues(const std::vector<double>& values) = 0;

	virtual std::vector<double> getValues() const = 0;

	virtual bool checkConstraints() const = 0;

	virtual IContinuousParameters* Clone() const = 0;
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* ICONTINUOUSPARAMETERS_H_ */
