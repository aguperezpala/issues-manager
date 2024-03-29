/*
 * EventHandlerObject.cpp
 *
 *  Created on: 14/10/2010
 *      Author: agustin
 */

#include "EventHandlerObject.h"

EventHandlerObject::EventHandlerObject() : id("") {
	// TODO Auto-generated constructor stub

}

EventHandlerObject::~EventHandlerObject() {
	// TODO: Verify when there are multiple IDs
	unsubscribeID();
}

void EventHandlerObject::SusbscribeID(const std::string &Id)
{
	if((&Id == NULL) || (Id.size() == 0)) {
		debug("Trying to subscribe an empty id\n");
		return;
	}

	id = Id;

	// we probably want to verify if we have not set befor some id
	// if the id is empty then set it, if not, then do nothing?
	EventHandler::getInstance()->subscribeID(Id, this);
}

	/* Unsubscribe the actual id */
	void EventHandlerObject::unsubscribeID(void)
	{
		EventHandler::getInstance()->unsubscribeID(id, this);
	}


/* Emmit a signal from this object to the event Handler
 * REQUIRES:
 * 		data		to be sent by the EventHandler
 * 		id			the ID of the EventHandlerObject wich catch the event
 * 		type		the event type number
 * RETURNS:
 * 		errCode		the code returned from the object who handle the event.
 *
 * NOTE: this functions does not use a new thread..
 */
int EventHandlerObject::emitEvent(void *data, const std::string &destID, int type)
{
	EventHandler *instance = EventHandler::getInstance();

	if(instance == NULL) {
		debug("Cannot get EventHandler instance\n");
		return -1;
	}

	return instance->emitEvent(destID, type, this, data);
}
