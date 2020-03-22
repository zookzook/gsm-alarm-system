//
//  d-sensors.c
//  gsm-alarm
//
//  Created by Michael Maier on 19.07.19.
//

#include "d-sensors.h"
#include "logger.h"
#include "owasys-io-module.h"
#include "owasys-rtu-module.h"
#include "watchdog.h"
#include "main.h"

#include <unistd.h>
#include <time.h>
#include <stdint.h>

SWITCHES gSwitches;
PIRS gPIRs;

void init_pirs(void) {
    uint8_t i = 0;
    while(i < MAX_PIRS) {
        gPIRs.pirs[i].t = 0;
        i += 1;
    } // while
}

bool all_closed(void) {
    
    bool result = true;
    uint8_t i = 0;
    while(i < MAX_SWITCHES && result) {
        result = result && gSwitches.switches[i].value;
        i += 1;
    }
    
    return result;
}

bool no_motions(void) {
    
    bool result = true;
    uint8_t i = 0;
    while(i < MAX_PIRS && result) {
        result = result && (gPIRs.pirs[i].t == 0);
        i += 1;
    }
    
    return result;
}

static bool pir_in_cool_down(PIR* pir, time_t now) {
    
    bool result = false;
    time_t t = pir->t;
    if(t != 0) {
        if(difftime(now, t) > 30) {
            pir->t = 0;
        } // if
        else {
            result = true;
        } // else
    } // if
    
    return result;
}
static bool in_cool_down(SWITCH* sw, time_t now) {
    
    bool result = false;
    time_t t = sw->t;
    if(t != 0) {
        if(difftime(now, t) > 2) {
            sw->t = 0;
        } // if
        else {
            result = true;
        } // else
    } // if
    
    return result;
}

static bool update_pir_status(uint8_t pirIndex, bool value, time_t now) {
    
    bool result = false;
    PIR* pir = &gPIRs.pirs[pirIndex];
    if(value) {
        if(!pir_in_cool_down(pir, now)){
            pir->t = now;
            result = true;
        } // if 
    } // if
    else {
        pir_in_cool_down(pir, now);
    } // else
    
    return result;
}

static bool update_switch_status(uint8_t swIndex, bool value, time_t now) {
    
    bool result = false;
    SWITCH* sw = &gSwitches.switches[swIndex];
    if(!in_cool_down(sw, now)) {
        if(sw->value != value) {
            sw->value = value;
            sw->t     = now;
            result    = true;
        } // if
    } // if
    
    return result;
}

static void set_switch(uint8_t swIndex, bool value) {
    SWITCH* sw = &gSwitches.switches[swIndex];
    sw->value = value;
    sw->t     = 0;
}

bool load_switches(void) {
    bool result = false;
    unsigned short int mask = 0x0000;
    if(io_read_all_pin(&mask)) {
        set_switch(LOCKER, mask & 1<<0);
        set_switch(STUGA_DOOR, mask & 1<<1);
        set_switch(KITCHEN_OUTSIDE, mask & 1<<2);
        set_switch(KITCHEN_INSIDE, mask & 1<<3);
        set_switch(LOFT, mask & 1<<4);
        set_switch(STOREROOM, mask & 1<<5);
    } // if
    
    return result;
}

bool update_switches(time_t now, bool *changes) {
    bool result = false;
    unsigned short int mask = 0x0000;
    if(io_read_all_pin(&mask)) {
        changes[LOCKER]          = update_switch_status(LOCKER, mask & 1<<0, now);
        changes[STUGA_DOOR]      = update_switch_status(STUGA_DOOR, mask & 1<<1, now);
        changes[KITCHEN_OUTSIDE] = update_switch_status(KITCHEN_OUTSIDE, mask & 1<<2, now);
        changes[KITCHEN_INSIDE]  = update_switch_status(KITCHEN_INSIDE, mask & 1<<3, now);
        changes[LOFT]            = update_switch_status(LOFT, mask & 1<<4, now);
        changes[STOREROOM]       = update_switch_status(STOREROOM, mask & 1<<5, now);
    } // if
    
    return result;
}

bool update_pirs(time_t now, bool *changes) {
    bool result = false;
    unsigned short int mask = 0x0000;
    
    static time_t t = 0;
    
    if( t == 0)
        t = time(NULL);
    
    if(io_read_all_pin(&mask)) {
        
        changes[STUGA_PIR]     = update_pir_status(STUGA_PIR, !(mask & 1<<6), now);
        changes[KITCHEN_PIR_1] = update_pir_status(KITCHEN_PIR_1, mask & 1<<7, now);
        changes[KITCHEN_PIR_2] = update_pir_status(KITCHEN_PIR_2, mask & 1<<8, now);
    } // if
    
    return result;
}

