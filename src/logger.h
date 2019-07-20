//
//  logger.h
//  fleetdevice
//
//  Created by Michael Maier on 08.09.17.
//
//

#ifndef logger_h
#define logger_h

#include <stdio.h>
#include <stdbool.h>

void logger_open(bool newValue);
void logger_close(void);

void info(const char *fmt, ...);

#endif /* logger_h */
