#include "EventHandler.h"

EventHandler EventHandler::instance = NULL;

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
	if(this->instance == NULL)
		this->instance = new EventHandler();

	return this->instance;
}





