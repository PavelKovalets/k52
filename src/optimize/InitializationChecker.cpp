/*
 * InitializationChecker.cpp
 *
 *  Created on: Apr 22, 2012
 *      Author: feanor
 */

#include <optimize/InitializationChecker.h>
#include <stdexcept>

namespace k52
{
namespace optimize
{

InitializationChecker::InitializationChecker()
{
	_wasInitialized = false;
}

void InitializationChecker::initializationCheck() const
{
	if(!_wasInitialized)
	{
		throw std::logic_error("Individual was used without being initialized");
	}
}

void InitializationChecker::setInitialized()
{
	if(!_wasInitialized)
	{
		_wasInitialized = true;
	}
	else
	{
		throw std::logic_error("Another initialization happened");
	}
}

}/* namespace optimize */
}/* namespace k52 */
