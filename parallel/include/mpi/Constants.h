/*
 * Constants.h
 *
 *  Created on: Oct 14, 2012
 *      Author: pavel
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <string>

namespace k52
{
	namespace parallel
	{
		namespace mpi
		{
			//TODO incapsulate and hide from user - !!! to remove using namespace k52::parallel::mpi::Constants;
			namespace Constants
			{
				static const int ServerRank = 0;

				static const int CommonTag = 0;

				static const char EndOfWorkTaskId [100] = "TheIdOfTheTaskThatMeanThatWorkerShouldEndItsWork";

				static const char GetStatisticsTaskId [100] = "TheIdOfTheTaskThatMeanThatWorkerShouldSendItsStatistics";
			}
		}
	}
}
#endif /* CONSTANTS_H_ */
