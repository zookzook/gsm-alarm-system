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
#include "daemon.h"

#include <unistd.h>
#include <time.h>

D_SENSORS gDSensors;

static void _sensors_init(D_SENSORS *out) {
    
    out->sensor_1 = false;
    out->sensor_2 = false;
    out->sensor_3 = false;
    out->sensor_4 = false;
    out->sensor_5 = false;
    out->sensor_6 = false;
    out->sensor_7 = false;
    out->sensor_8 = false;
    out->sensor_9 = false;
    
    sensors_update_values(out);
}

static bool all_closed(D_SENSORS* in) {
    
    bool result = in->sensor_1 && in->sensor_2 && in->sensor_3 && in->sensor_4 &&
                  in->sensor_5 && in->sensor_6 && in->sensor_7 && in->sensor_8 &&
                  in->sensor_9;
    
    return result;
}

static bool changed(D_SENSORS* current, D_SENSORS* new) {
    
    return current->sensor_1 != new->sensor_1 ||
           current->sensor_2 != new->sensor_2 ||
           current->sensor_3 != new->sensor_3 ||
           current->sensor_4 != new->sensor_4 ||
           current->sensor_5 != new->sensor_5 ||
           current->sensor_6 != new->sensor_6 ||
           current->sensor_7 != new->sensor_7 ||
           current->sensor_8 != new->sensor_8 ||
           current->sensor_9 != new->sensor_9;
}

void sensors_init( void ) {
    _sensors_init(&gDSensors);
}

void sensors_send(void) {
    
}

void sensors_dump(D_SENSORS *s) {
    info("Sensor 1: %s", s->sensor_1 ? "ein" : "aus");
    info("Sensor 2: %s", s->sensor_2 ? "ein" : "aus");
    info("Sensor 3: %s", s->sensor_3 ? "ein" : "aus");
    info("Sensor 4: %s", s->sensor_4 ? "ein" : "aus");
    info("Sensor 5: %s", s->sensor_5 ? "ein" : "aus");
    info("Sensor 6: %s", s->sensor_6 ? "ein" : "aus");
    info("Sensor 7: %s", s->sensor_7 ? "ein" : "aus");
    info("Sensor 8: %s", s->sensor_8 ? "ein" : "aus");
    info("Sensor 9: %s", s->sensor_9 ? "ein" : "aus");
}

void sensors_update_values(D_SENSORS* out) {
    
    unsigned short int mask = 0x0000;
    if(io_read_all_pin(&mask)) {
        out->sensor_1 = mask & 1<<0;
        out->sensor_2 = mask & 1<<2;
        out->sensor_3 = mask & 1<<3;
        out->sensor_4 = mask & 1<<4;
        out->sensor_5 = mask & 1<<5;
        out->sensor_6 = !(mask & 1<<6); // All inputs are inverted except DIO6,
        out->sensor_7 = mask & 1<<7;
        out->sensor_8 = mask & 1<<8;
        out->sensor_9 = mask & 1<<9;
    } // if
}

void update_vin(time_t now) {
    
    static time_t last_update = 0;
    if(last_update == 0) {
        last_update = time(NULL);
    } // if
    else {
        if(difftime(now, last_update) > 10) {
            
            float current = rtu_get_vin();
            info("Checking Volt: %f", current);
            if(current < 12.00) {
                info("Low voltage");
            } // if
            last_update = now;
        } // if
    } // else
}

int sensors_running_loop(void) {
    
    D_SENSORS current;
    D_SENSORS new;
    _sensors_init(&current);
    new = current;
    
    while(gContinueRunning) {


        usleep(500);

        wd_ping();
        
        time_t now = time(NULL);
        update_vin(now);
        
        sensors_update_values(&new);
        
        if(changed(&current, &new)) {
            
            info("Changes detected!");
            
            // entprellen
            time_t last_update = now;
            D_SENSORS last     = new;
            while(difftime(now, last_update) > 1) {

                sensors_update_values(&last);
                if(changed(&new, &last)) {
                    last_update = time(NULL);
                    new         = last;
                } // if

                now = time(NULL);
            }
            
            current = last;
            sensors_dump(&current);
        }
        
        if(all_closed(&current)) {
            gContinueRunning = false;
        } // if
        
    } // if
    
    return 0;
}
