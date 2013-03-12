/*
 * Random.cpp
 *
 *  Created on: Jan 29, 2012
 *      Author: feanor
 */

#include "Random.h"
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <cmath>

Random& Random::Instance()
{
	static Random self;
	return self;
}

Random::Random()
{
	//Seed random
	srand((unsigned)(time(NULL)));
	//srand(1);
	_boolBase = rand();
	_nextBitInBoolBase = 0;

	_maxBitInBoolBase = 0;
	int maxBoolBaseValue = 1;

	for(int i=0; i<sizeof(int) * 8; i++)
	{
		maxBoolBaseValue *= 2;
		if(maxBoolBaseValue > RAND_MAX)
		{
			break;
		}
		_maxBitInBoolBase ++;
	}
}

int Random::GetNextBitFromBoolBase()
{
	if( _nextBitInBoolBase >  _maxBitInBoolBase)
	{
		_nextBitInBoolBase = 0;
		_boolBase = rand();
	}
	
	int bitmask = 0x1;
	bitmask = bitmask << _nextBitInBoolBase;
	_nextBitInBoolBase ++;
	return _boolBase & bitmask;
}

bool Random::getRandomBool()
{
	int bit = GetNextBitFromBoolBase();
	return bit == 0;
}

void Random::setRandomBoolVector(std::vector<bool>* array)
{
	for(int i = 0; i < array->size(); i++)
	{
		(*array)[i] = getRandomBool();
	}
}

double Random::getBaseRandomQuantity()
{
	return ((double) rand() / RAND_MAX);
}

double Random::getContinuousRandomQuantity(double minValue, double maxValue)
{
	double base = getBaseRandomQuantity();
	return base * (maxValue - minValue) + minValue;
}

//TODO remove working spike
int Random::getUniformlyDistributedDiscreteRandomQuantity(int minValue, int maxValue)
{
	return rand() % (maxValue-minValue+1) + minValue;
}

