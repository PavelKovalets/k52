/*
 * WorkerStatistics.h
 *
 *  Created on: Mar 14, 2013
 *      Author: feanor
 */

#ifndef WORKERSTATISTICS_H_
#define WORKERSTATISTICS_H_

namespace k52
{
namespace parallel
{

class WorkerStatistics
{
public:
	WorkerStatistics();

	WorkerStatistics(int counted, int errors, int id);

	void increaseCounted();

	void increaseErrors();

	int getCounted() const;

	int getErrors() const;

	int getId() const;

protected:
	int _counted;
	int _errors;
	int _id;
};

} /* namespace parallel */
} /* namespace k52 */
#endif /* WORKERSTATISTICS_H_ */
