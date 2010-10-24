#ifndef DEBUG_H
#define DEBUG_H


#ifdef DEBUG
#include <stdio.h>
#define debug(format, ...) {fprintf(stderr, "DEBUG[%s, %s, %d]: ", \
				 __FILE__, __FUNCTION__, __LINE__); \
				fprintf(stderr, format, ## __VA_ARGS__);}
#else
#define debug(format,...)
#endif



#endif
