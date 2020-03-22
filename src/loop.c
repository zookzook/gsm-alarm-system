//
//  loop.c
//  gsm-alarm
//
//  Created by Michael Maier on 21.07.19.
//

#include "loop.h"
#include "d-sensors.h"
#include "logger.h"
#include "watchdog.h"
#include "commands.h"
#include "sms.h"
#include "owasys-io-module.h"
#include "owasys-rtu-module.h"
#include "owasys-gsm-module.h"
#include "user.h"

#include <time.h>
#include <unistd.h>

volatile bool gIsLocked;
volatile bool gContinueRunning;

#define LOCKED_FILE "/home/debian/data/locked"

static void process_switch(bool *changes, uint8_t swIndex) {
    if(changes[swIndex]) {
        SWITCH* sw = &gSwitches.switches[swIndex];
        cmd_sensor_change(swIndex, sw->value);
    }
}

static void process_pir(bool *changes, uint8_t pirIndex) {
    if(changes[pirIndex]) {
        cmd_pir_detected(pirIndex);
    } // if
}

static void process_switches(bool *changes) {
    if(gIsLocked) {
        uint8_t i = 0;
        while( i < MAX_SWITCHES) {
            process_switch(changes, i);
            i += 1;
        }
    } // if
}

static void process_pirs(bool* changes) {
    if(gIsLocked) {
        uint8_t i = 0;
        while( i < MAX_PIRS) {
            process_pir(changes, i);
            i += 1;
        }
    } // if
}

static void send_low_voltage_sms(float v) {

    uint8_t i = 0;
    while(i < admins.size) {
        char msg[1024];
        snprintf(msg, 1023, "Batteriespannung niedrig: %.2fv", v);
        msg[1023] = '\0';
        gsm_send_sms(admins.users[i].number, msg);
        i += 1;
    } //
}

static void send_voltage_ok_sms(float v) {
    
    uint8_t i = 0;
    while(i < admins.size) {
        char msg[1024];
        snprintf(msg, 1023, "Batteriespannung wieder gut: %.2fv", v);
        msg[1023] = '\0';
        gsm_send_sms(admins.users[i].number, msg);
        i += 1;
    } //
}


void update_vin(time_t now) {
    
    static time_t last_update = 0;
    static bool warning       = false;
    
    if(last_update == 0 || difftime(now, last_update) > 5*60) {
        
        float voltage = rtu_get_vin();
        if(!warning) {
            if(voltage < 12.10) {
                warning = true;
                send_low_voltage_sms(voltage);
            } // if
        } // if
        else {
            if(voltage > 12.50) {
                send_voltage_ok_sms(voltage);
                warning = false;
            } // if
        } // else
        
        last_update = now;
    } // if
}

void loop_load_state(void) {
    
    if(access(LOCKED_FILE, F_OK) != -1 ) {
        gIsLocked = true;
    } else {
        gIsLocked = false;
    }
}

void loop_save_state(void) {
    if(gIsLocked) {
        FILE *fp = fopen(LOCKED_FILE,"w");
        fclose(fp);
    } // if
    else {
        remove(LOCKED_FILE);
    } // else
}

bool update_pir_switch(time_t now) {
    
    static bool on = false;
    static time_t last = 0;

    bool result = false;
    
    if(on) {
        if(all_closed()) {
            on = false;
            io_pir_off();
            last = 0;
            //info("Loop: pir off");
        } // if
    } // if
    else {
        if(!all_closed()) {
            on = true;
            sms_init_pirs();
            init_pirs();
            io_pir_on();
            last = now;
            //info("Loop: pir on");
        } // if
    } // else
    
    if(on) {
        if(difftime(now, last) > 15) {
            result = true;
        } // if
    } // if
    
    return result;
}

void run_loop(void) {
    
    gContinueRunning = true;

    // time_t x = time(NULL);
    while(gContinueRunning) {
        
        usleep(250);
        
        wd_ping();
        
        time_t now = time(NULL);
        update_vin(now);

        sms_check_counter(now);

        bool changes[6];
        update_switches(now, changes);
        process_switches(changes);
        
        if(update_pir_switch(now)) {
            update_pirs(now, changes);
            process_pirs(changes);
        }
        
/*        if(difftime(now, x) > 10 ) {
            if(gPIRs.pirs[0].t > 0) {
                info("Status: %f", (float)difftime(now, gPIRs.pirs[0].t));
            }
            else {
                info("No motion");
            }
            x = now;
        }*/

    } // if
}

