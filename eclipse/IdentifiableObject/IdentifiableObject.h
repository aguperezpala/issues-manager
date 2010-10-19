/*
 * IdentifiableObject.h
 *
 * Used to set objects with a unique ID. This ID will be based on the time
 * (probably it will be necessary add another identification like machine name
 * or user id or something like that)
 *
 *  Created on: 18/10/2010
 *      Author: agustin
 */

#ifndef IDENTIFIABLEOBJECT_H_
#define IDENTIFIABLEOBJECT_H_

#include <string>
#include <ctime>
#include <iostream>
#include <sstream>

/* for now we will use a string to represent the id */
typedef std::string uniqueID_t;


class IdentifiableObject {
public:
	/* Here is where the ID it is generated using the system time */
	IdentifiableObject();
	~IdentifiableObject(){};

	/* returns the id over the arg */
	void getID(uniqueID_t &id){id = this->uniqueID;};

private:
	uniqueID_t uniqueID;
	// we will use an auxiliar field to ensure there will no similar IDs
	static unsigned int counter;

};

#endif /* IDENTIFIABLEOBJECT_H_ */
