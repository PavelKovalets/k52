/*
 * IndividualStatistics.h
 *
 *  Created on: Mar 17, 2013
 *      Author: feanor
 */

#ifndef INDIVIDUALSTATISTICS_H_
#define INDIVIDUALSTATISTICS_H_

namespace k52
{
namespace optimize
{

/**
@class IndividualStatistics
Represents statistics about sungle individual
 */
class IndividualStatistics
{
public:
	double Fitness;
	int TimesChosenForCrossover;

	static bool less (IndividualStatistics const& leftArg, IndividualStatistics const& rightArg)
	{
		return leftArg.TimesChosenForCrossover < rightArg.TimesChosenForCrossover;
	}

	static bool greater (IndividualStatistics const& leftArg, IndividualStatistics const& rightArg)
	{
		return leftArg.TimesChosenForCrossover > rightArg.TimesChosenForCrossover;
	}
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* INDIVIDUALSTATISTICS_H_ */
