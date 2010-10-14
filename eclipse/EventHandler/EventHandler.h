/*
 * EventHandler.h
 *
 *  Created on: 12/10/2010
 *      Author: agustin
 */

#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include <string>
#include <map>
/* own libs */
#include "debug.h"
#include "EventHandlerObject.h"
#include "EventArg.h"

/* this is a singleton class */
class EventHandler {


public:
	EventHandler *getInstance();

	/* Subscribe an EventID with a EventHandlerObject
	 * REQUIRES:
	 * 		eventID.size() 	!= 0
	 * 		eho				!= NULL
	 */
	void subscribeID(const std::string &eventID, EventHandlerObject *eho);

	/* Unsubscribe an EventID, it should exists
	 * REQUIRES:
	 * 		eho			!= NULL
	 * 		eventID		was subscribed before by eho
	 * RETURNS:
	 * 		< 0			on error
	 * 		0			if success
	 */
	int unsubscribeID(const std::string &eventID, EventHandlerObject *eho);

	/* Emit a event
	 * REQUIRES:
	 * 		eho		!= NULL (the object wich emit an event)
	 * 		toID	!= NULL (the ID of the object wich will receive the event)
	 * 		data	!= NULL (the payload of the event)
	 * RETURNS:
	 * 		errCode (0 on success | < 0 if error)
	 */
	int emitEvent(const std::string &toID, EventHandlerObject *eho, void *data);








private:
	EventHandler();
	~EventHandler();

	/* this will be the hash used to send events from one obeject to other */
	std::multimap<std::string, EventHandlerObject*>;

	static EventHandler *instance;
};


#endif /* EVENTHANDLER_H_ */
