/*
 * EventHandlerObject.h
 *
 *  Created on: 14/10/2010
 *      Author: agustin
 */

#ifndef EVENTHANDLEROBJECT_H_
#define EVENTHANDLEROBJECT_H_

#include <string>

#include "debug.h"
#include "EventHandler.h"
#include "EventArg.h"


class EventHandlerObject {
public:
	EventHandlerObject();
	~EventHandlerObject();

	/* get the subscribed ID */
	const std::string &getSubscribedID(void){return this->id;};

	/* Set the subscribed ID */
	void setSusbscribedID(const std::string &Id);

	/*! Virtual method to reimplement in the class wich will be able to
	 * receive events..
	 *	PARAMS:
	 *		@arg [IN] wich contains all the data of the event
	 *
	 *	RETURNS:
	 *		errCode
	 */
	virtual int handleEvent(const eventArg_t &arg){};

protected:

	/* Emit a signal from this object to the event Handler
	 * REQUIRES:
	 * 		data		to be sent by the EventHandler
	 * 		id			the ID of the EventHandlerObject wich catch the event
	 * 		type		the event type number
	 * RETURNS:
	 * 		errCode		the code returned from the object who handle the event.
	 *
	 * NOTE: this functions does not use a new thread..
	 */
	int emitEvent(void *data, const std::string &destID, int type);




private:
	// the id used when subscribe to the eventHandler
	std::string id;

};

#endif /* EVENTHANDLEROBJECT_H_ */
