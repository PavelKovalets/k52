/*
 * WorkerStatistics.h
 *
 *  Created on: Nov 10, 2012
 *      Author: pavel
 */

#ifndef WORKERSTATISTICS_H_
#define WORKERSTATISTICS_H_

#include "BoostDeclaration.h"

namespace k52
{
	namespace parallel
	{
		namespace mpi
		{
			class WorkerStatistics
			{
			public:
				WorkerStatistics():
					_counted(), _errors(), _rank() {}

				WorkerStatistics(int counted, int errors, int rank):
					_counted(counted), _errors(errors), _rank(rank) {}

				int getCounted() const
				{
					return _counted;
				}

				int getErrors() const
				{
					return _errors;
				}

				int getRank() const
				{
					return _rank;
				}

			private:
				friend class boost::serialization::access;

				template<class Archive>
				void serialize(Archive & ar, const unsigned int version)
				{
					ar & _counted;
					ar & _errors;
					ar & _rank;
				}

				int _counted;
				int _errors;
				int _rank;
			};
		}
	}
}
#endif /* WORKERSTATISTICS_H_ */
