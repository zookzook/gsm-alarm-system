//
//  daemon.h
//  gsm-alarm
//
//  Created by Michael Maier on 19.07.19.
//

#ifndef daemon_h
#define daemon_h

#include <stdio.h>
#include <stdbool.h>

volatile bool gContinueRunning;

int daemonize(void);

void loop(void);

#endif /* daemon_h */
