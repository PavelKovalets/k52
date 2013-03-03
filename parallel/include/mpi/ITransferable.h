/*
 * ITransferable.h
 *
 *  Created on: Nov 11, 2012
 *      Author: pavel
 */

#ifndef ITRANSFERABLE_H_
#define ITRANSFERABLE_H_

#include "BoostDeclaration.h"

namespace k52
{
	namespace parallel
	{
		namespace mpi
		{
			class ITransferable
			{
			public:
				virtual ~ITransferable() { }

				virtual void send(boost::mpi::communicator* communicator, int target) const = 0;

				virtual void receive(boost::mpi::communicator* communicator) = 0;
			};
		}
	}
}
#endif /* ITRANSFERABLE_H_ */
