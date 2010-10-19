#include "EventHandler.h"

EventHandler *EventHandler::instance = NULL;

EventHandler::EventHandler()
{
	// do nothing

}

EventHandler::~EventHandler()
{

}


/* Returns the instance of the singleton
 * ENSURES:
 * 		instance != NULL
 */
EventHandler *EventHandler::getInstance()
{
	if(EventHandler::instance == NULL)
		EventHandler::instance = new EventHandler();

	return EventHandler::instance;
}


/* Subscribe an EventID with a EventHandlerObject
 * REQUIRES:
 * 		eventID.size() 	!= 0
 * 		eho				!= NULL
 */
void EventHandler::subscribeID(const std::string &eventID, EventHandlerObject *eho)
{
	std::pair<std::multimap<std::string, EventHandlerObject*>::iterator,
			  std::multimap<std::string, EventHandlerObject*>::iterator> pIt;
	std::multimap<std::string, EventHandlerObject*>::iterator it;

	// check if the eventID already exists..
	pIt = eventMapper.equal_range(eventID);

	debug("New element %s suscribed \n", eventID.c_str());

	for(it = pIt.first; it != pIt.second; ++it)
		if((*it).second == eho)
			// the element had suscribe with this id befor... return
			return;

	// now we add it into the mapper
	eventMapper.insert(std::pair<std::string, EventHandlerObject*> (eventID, eho));
}

/* Unsubscribe an EventID, it should exists
 * REQUIRES:
 * 		eho			!= NULL
 * 		eventID		was subscribed before by eho
 * RETURNS:
 * 		< 0			on error
 * 		0			if success
 */
int EventHandler::unsubscribeID(const std::string &eventID, EventHandlerObject *eho)
{

	std::pair<std::multimap<std::string, EventHandlerObject*>::iterator,
			  std::multimap<std::string, EventHandlerObject*>::iterator> pIt;
	std::multimap<std::string, EventHandlerObject*>::iterator it;

	// check if the eventID already exists..
	pIt = eventMapper.equal_range(eventID);

	debug("New element %s unsubscribed \n", eventID.c_str());

	for(it = pIt.first; it != pIt.second; ++it)
		if((*it).second == eho) {
			// remove the object with this ID
			eventMapper.erase(it);
			return 0;
		}

	// there are no object subscribed with this id..
	return -1;
}

/* Emit a event
 * REQUIRES:
 * 		eho		!= NULL (the object wich emit an event)
 * 		toID	!= NULL (the ID of the object wich will receive the event)
 * 		data	!= NULL (the payload of the event)
 * RETURNS:
 * 		errCode (0 on success | < 0 if error)
 * NOTE: this will use the same thread of the event emitter. And the
 * EventArg used its automatically freed (but no the data itself)
 */
int EventHandler::emitEvent(const std::string &toID, int type,
		EventHandlerObject *eho, void *data)
{
	std::pair<std::multimap<std::string, EventHandlerObject*>::iterator,
			  std::multimap<std::string, EventHandlerObject*>::iterator> pIt;
	std::multimap<std::string, EventHandlerObject*>::iterator it;
	eventArg_t args = {};
	int ret = -1;


	if((&toID == NULL) || (eho == NULL)){
		debug("BadArgs");
		return -1;
	}

	// fill the struct
	args.data = data;
	args.receiverID = toID;
	args.emitterID = eho->getSubscribedID();
	args.eventType = type;

	debug("New event emmited from %s  to %s \n", args.emitterID.c_str(),
			toID.c_str());

	// check if the eventID already exists..
	pIt = eventMapper.equal_range(toID);

	for(it = pIt.first; it != pIt.second; ++it) {
		// now for every EventHandlerObject we emmit the event
		ret = (*it).second->handleEvent(args);
	}

	return ret;
}



