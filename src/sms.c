//
//  sms.c
//  gsm-alarm
//
//  Created by Michael Maier on 19.07.19.
//

#include "sms.h"
#include "logger.h"
#include "d-sensors.h"
#include "loop.h"

SMS_INFO database[SMS_LENGTH];

void sms_init(void) {
    
    uint8_t i = 0;
    while(i < SMS_LENGTH) {
        SMS_INFO *info = &database[i];
        info->last_send = 0;
        info->counter   = 0;
        i += 1;
    }
}

void sms_init_switches(void) {
    
    uint8_t i = 0;
    while(i < MAX_SWITCHES) {
        SMS_INFO *info = &database[i];
        info->last_send = 0;
        info->counter   = 0;
        i += 1;
    }
}

void sms_init_pirs(void) {
    
    uint8_t i = PIR1;
    while(i <= PIR3 ) {
        SMS_INFO *info = &database[i];
        info->last_send = 0;
        info->counter   = 0;
        i += 1;
    }
}

bool sms_update_counter(uint8_t index) {
    
    bool result = false;
    SMS_INFO *i = &database[index];
    if(i->counter < 3) {
        
        i->last_send = time(NULL);
        i->counter   += 1;
        result = true;
    } // if
    
    return result;
}

void sms_check_counter(time_t now) {
    
    static time_t lastSwitches = 0;
    static time_t lastPIRs = 0;
    
    if(gIsLocked) {
        if(all_closed()){
            if(lastSwitches == 0 || difftime(now, lastSwitches) > 30) {
                sms_init_switches();
                // info("SMS: switch counter automatically reset");
                lastSwitches = now;
            } // if
        } // if
        if(no_motions()) {
            if(lastPIRs == 0 || difftime(now, lastPIRs) > 30) {
                sms_init_pirs();
                // info("SMS: pir counter automatically reset");
                lastPIRs = now;
            } // if
        } // if
    } // if
    else {
        lastSwitches = now;
        lastPIRs     = now;
    } // else 
}
