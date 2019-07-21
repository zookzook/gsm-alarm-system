#include "watchdog.h"
#include "logger.h"
#include "notify.h"

#include <stdlib.h>
#include <time.h>

bool wd_init(void) {
    char *wdtTimer = getenv("WATCHDOG_USEC");
    if(!wdtTimer) {
        info("WD not found!");
    }
    else {
        info("WD found %s", wdtTimer);
    } // else
    
    return wdtTimer != NULL;
}

void wd_ping(void) {
    
    static time_t last = 0;
    
    time_t now = time(NULL);
    if(last == 0 || (difftime(time(NULL), last) > 15)) {
        notify_watchdog();
        last = now;
    } // if
}
