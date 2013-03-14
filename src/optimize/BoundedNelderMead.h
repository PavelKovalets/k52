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

using ::k52::optimize::params::IParameters;
using ::k52::optimize::params::IContinuousParameters;

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

	static void getIndexes(const vector<double>& values, int* firstMaxIndex, int* secoundMaxIndex, int* minIndex);
	
	static vector< vector<double> > getRegularSimplex(const vector<double>& basePoint, double l);

	vector<double> countObjectiveFunctionValues(const vector< vector<double> >& parametersValues,
		IContinuousParameters* baseParameters,
		const IObjectiveFunction & functionToOptimize);

	double countObjectiveFunctionValue(const vector<double>& parameters,
		IContinuousParameters* baseParameters,
		const IObjectiveFunction & functionToOptimize);

	static vector<double> reflexion(const vector<double>& centerOfMass, const vector<double>& targetPoint);

	static vector<double> expansion(const vector<double>& centerOfMass, const vector<double>& targetPoint);

	static vector<double> contraction(const vector<double>& centerOfMass, const vector<double>& targetPoint);

	static void reduction(vector< vector<double> >* polygon, int pointIndex);

	static double countDifferance(const vector<double>& values);

	void correctByProjectingToBounds(vector<double>* point);

	static vector<double> getCenterOfMass(const vector< vector<double> >& polygon, int pointIndex);

	static void outputPolygon(const vector< vector<double> >& polygon);

private:
	double _precision;
	double _lowerBound;
	double _upperBound;
	double _l;

	ObjectiveFunctionCounter _fitnessCounter;

};

}/* namespace optimize */
}/* namespace k52 */

#endif /* BOUNDEDNELDERMEAD_H_ */
