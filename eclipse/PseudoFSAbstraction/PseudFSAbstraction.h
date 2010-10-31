/*
 * PseudFSAbstraction.h
 * Represents a pseudo File System. This will be used to abstract the media
 * where will be received and save the issues / config files / directories / etc.
 * In the case of an EmailFS wich will inherit from this class, will save every
 * file in diferents emails, the directories in emails with different name, or
 * whatever.
 * This FS will emitt events to advise when a file or directories its
 * created/deleted/modify or else.
 *
 *  Created on: 31/10/2010
 *      Author: agustin
 */

#ifndef PSEUDFSABSTRACTION_H_
#define PSEUDFSABSTRACTION_H_

#include "EventHandlerObject.h"
#include "simplethread.h"

class PseudFSAbstraction: public EventHandlerObject, public SimpleThread {
public:
	PseudFSAbstraction();
	virtual ~PseudFSAbstraction();
};

#endif /* PSEUDFSABSTRACTION_H_ */
