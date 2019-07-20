//
//  watchdog.h
//  gsm-alarm
//
//  Created by Michael Maier on 20.07.19.
//

#ifndef watchdog_h
#define watchdog_h

#include <stdio.h>

void wd_init(void);
void wd_ping(void);
void wd_shutdown(void);

#endif /* watchdog_h */
