/*
 * IssueFactory.h
 *
 *  Created on: 24/10/2010
 *      Author: agustin
 */

#ifndef ISSUEMANAGER_H_
#define ISSUEMANAGER_H_


#include <string>
#include <pthread.h>
/* own libs */
#include "EventHandler.h"
#include "EventHandlerObject.h"
#include "simplethread.h"



class IssueManager : public EventHandlerObject, SimpleThread {
public:
	IssueManager();
	~IssueManager();

private:
	pthread_mutex_t mutex;

};

#endif /* ISSUEMANAGER_H_ */
