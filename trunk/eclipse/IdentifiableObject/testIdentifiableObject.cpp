/*
 * testIdentifiableObject.cpp
 *
 *  Created on: 18/10/2010
 *      Author: agustin
 */

#include <iostream>
#include "IdentifiableObject.h"



class IdentifiableObjectTest : public IdentifiableObject {

public:
	IdentifiableObjectTest(){};
	~IdentifiableObjectTest(){};
};





int main(void)
{
	IdentifiableObjectTest t1;
	IdentifiableObjectTest t2;
	uniqueID_t id1, id2;

	t1.getID(id1);
	t2.getID(id2);

	std::cout << "t1.ID:" << id1 << std::endl;
	std::cout << "t2.ID:" << id2 << std::endl;



	return 0;
}
