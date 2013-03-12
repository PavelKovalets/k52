/*
 * ContinuousParametersArray.h
 *
 *  Created on: May 20, 2012
 *      Author: feanor
 */

#ifndef CONTINUOUSPARAMETERSARRAY_H_
#define CONTINUOUSPARAMETERSARRAY_H_

#include <optimize/params/IContinuousParameters.h>

class ContinuousParametersArray: public IContinuousParameters
{
public:
	ContinuousParametersArray(size_t numberOfParameters);

	virtual void setValues(const std::vector<double>& values);

	virtual std::vector<double> getValues() const;

	virtual ContinuousParametersArray* clone() const;

	virtual bool checkConstraints() const;

#ifdef BUILD_WITH_MPI
	//TODO implementation needed!!!
	virtual void send(boost::mpi::communicator* communicator, int target) const;

	//TODO implementation needed!!!
	virtual void receive(boost::mpi::communicator* communicator);
#endif

private:
	std::vector<double> _values;
};

#endif /* CONTINUOUSPARAMETERSARRAY_H_ */
