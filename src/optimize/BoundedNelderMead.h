/*
 * BoundedNelderMead.h
 *
 *  Created on: May 23, 2012
 *      Author: feanor
 */

#ifndef BOUNDEDNELDERMEAD_H_
#define BOUNDEDNELDERMEAD_H_

#include <optimize/IOptimizer.h>
#include <optimize/params/IContinuousParameters.h>
#include "ObjectiveFunctionCounter.h"

#include <common/disallow_copy_and_assign.h>

namespace k52
{
namespace optimize
{

class BoundedNelderMead: public IOptimizer
{
public:
	BoundedNelderMead(double l, double precision, double lowerBound, double upperBound, int numberOfThreads);

	virtual void optimize(IParameters* parametrsToOptimize, const IObjectiveFunction &functionToOptimize);

protected:

	static void getIndexes(const std::vector<double>& values, int* firstMaxIndex, int* secoundMaxIndex, int* minIndex);
	
	static std::vector< std::vector<double> > getRegularSimplex(const std::vector<double>& basePoint, double l);

	std::vector<double> countObjectiveFunctionValues(const std::vector< std::vector<double> >& parametersValues,
		IContinuousParameters* baseParameters,
		const IObjectiveFunction & functionToOptimize);

	double countObjectiveFunctionValue(const std::vector<double>& parameters,
		IContinuousParameters* baseParameters,
		const IObjectiveFunction & functionToOptimize);

	static std::vector<double> reflexion(const std::vector<double>& centerOfMass, const std::vector<double>& targetPoint);

	static std::vector<double> expansion(const std::vector<double>& centerOfMass, const std::vector<double>& targetPoint);

	static std::vector<double> contraction(const std::vector<double>& centerOfMass, const std::vector<double>& targetPoint);

	static void reduction(std::vector< std::vector<double> >* polygon, int pointIndex);

	static double countDifferance(const std::vector<double>& values);

	void correctByProjectingToBounds(std::vector<double>* point);

	static std::vector<double> getCenterOfMass(const std::vector< std::vector<double> >& polygon, int pointIndex);

	static void outputPolygon(const std::vector< std::vector<double> >& polygon);

private:
	double _precision;
	double _lowerBound;
	double _upperBound;
	double _l;

	ObjectiveFunctionCounter _fitnessCounter;

	DISALLOW_COPY_AND_ASSIGN(BoundedNelderMead);
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* BOUNDEDNELDERMEAD_H_ */
