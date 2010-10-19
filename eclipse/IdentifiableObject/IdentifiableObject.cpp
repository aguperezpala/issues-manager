/*
 * IdentifiableObject.cpp
 *
 *  Created on: 18/10/2010
 *      Author: agustin
 */

#include "IdentifiableObject.h"

unsigned int IdentifiableObject::counter = 0;

IdentifiableObject::IdentifiableObject()
{
	time_t actualTime = time(NULL);
	std::stringstream ss;

	// get the time (seconds from the Epoch
	ss << actualTime << "-" << counter;
	counter++;

	// here we have to add some other identifier to ensure that we are only
	// having a unique ID
	this->uniqueID = ss.str();
}



