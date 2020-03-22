//
//  loop.h
//  gsm-alarm
//
//  Created by Michael Maier on 21.07.19.
//

#ifndef loop_h
#define loop_h

#include <stdio.h>
#include <stdbool.h>

#define ALARM_STATUS 1
#define CHANGES_STATUS 2

volatile bool gContinueRunning;
volatile bool gIsLocked;

void run_loop(void);

void loop_load_state(void);
void loop_save_state(void);

#endif /* loop_h */
