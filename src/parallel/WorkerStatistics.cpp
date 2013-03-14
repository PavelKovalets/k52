/*
 * WorkerStatistics.cpp
 *
 *  Created on: Mar 14, 2013
 *      Author: feanor
 */

#include <parallel/WorkerStatistics.h>

namespace k52
{
namespace parallel
{

WorkerStatistics::WorkerStatistics():
	_counted(), _errors(), _id() {}

WorkerStatistics::WorkerStatistics(int counted, int errors, int id):
	_counted(counted), _errors(errors), _id(id) {}


void WorkerStatistics::increaseCounted()
{
	++_counted;
}

void WorkerStatistics::increaseErrors()
{
	++_errors;
}

int WorkerStatistics::getCounted() const
{
	return _counted;
}

int WorkerStatistics::getErrors() const
{
	return _errors;
}

int WorkerStatistics::getId() const
{
	return _id;
}

} /* namespace parallel */
} /* namespace k52 */
