//
//  watchdog.c
//  gsm-alarm
//
//  Created by Michael Maier on 20.07.19.
//

#include "watchdog.h"
#include "logger.h"

#include <stdlib.h>
#include <time.h>
#include <systemd/sd-daemon.h>

void wd_init(void) {
    char *wdtTimer = getenv("WATCHDOG_USEC");
    if(!wdtTimer) {
        info("WD not found!");
    }
    else {
        info("WD found %s", wdtTimer);
    } // else
}

void wd_ping(void) {
    
    static time_t last = 0;
    
    time_t now = time(NULL);
    
    if(last == 0) {
        last = now;
    }
    
    if(difftime(time(NULL), last) > 15) {
        
        if (sd_notify(0, "WATCHDOG=1") < 0) {
            info("Error notifying watchdog service");
        }
        else {
            info("Ping");
        }

        last = now;
    }
    
}

void wd_shutdown(void) {
}
