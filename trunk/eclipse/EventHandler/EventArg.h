#ifndef EVENTARG_H_
#define EVENTARG_H_

#include <string>

/* The struct used to pass the event arguments, this is a open struct */
typedef struct eventArg_ {
	std::string emitterID;	// the ID (eventID) of the event emitter
	std::string receiverID;	// the eventID of the event receiver
	void *data;				// the argument pass throw the event
} eventArg_t;



#endif
