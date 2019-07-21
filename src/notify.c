//
//  notify.c
//  gsm-alarm
//
//  Created by Michael Maier on 21.07.19.
//

#include "notify.h"
#include "logger.h"
#include <systemd/sd-daemon.h>

static void notify(char* message) {
    if (sd_notify(0, message)<0){
        info("Main: unable to notify '%s' systemd!", message);
    } // if
    else {
        info("Main: notified '%s'", message);
    } // else
    
}

void notify_failure(void) {
    notify("STATUS=Failed to start up");
}

void notify_ready(void) {
    notify("READY=1");
}

void notify_stopping(void) {
    notify("STOPPING=1");
}

void notify_watchdog(void) {
    notify("WATCHDOG=1");
}
