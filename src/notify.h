//
//  notify.h
//  gsm-alarm
//
//  Created by Michael Maier on 21.07.19.
//

#ifndef notify_h
#define notify_h

#include <stdio.h>

void notify_failure(void);
void notify_ready(void);
void notify_stopping(void);
void notify_watchdog(void);

#endif /* notifiy_h */
