//
//  sms.c
//  gsm-alarm
//
//  Created by Michael Maier on 19.07.19.
//

#include "sms.h"
#include "owasys-gsm-module.h"
#include "owasys-rtu-module.h"
#include "logger.h"

#include <string.h>

static SMS_INFO database[4];

static void send_message(char* message) {
    
    char* destinations = "004916090984428";
    // gsm_send_sms(destinations, message);
    
    info("Sending '%s' to '%s'", message, destinations);
}

void init(void) {
    memset( &database[0], 0, sizeof(SMS_INFO) * 4);
}

bool sms_send(uint8_t type, uint16_t mask, uint16_t *counter) {
    
    bool result = false;
    if(type < 4) {
        
        time_t now = time(NULL);
        SMS_INFO *info = &database[type];
        
        if(info->last_send == 0) {
            info->last_send = now;
            info->counter   = 1;
            info->mask      = mask;
            *counter        = 0;
            result          = true;
        }
        else
        // Differenz ist noch nicht hoch groß genug
        if(difftime(now, info->last_send) < info->limit){
            
            // Maske ist gleich, wir zählen nur
            if(info->mask == mask) {
                info->counter = info->counter + 1;
            } // if
            else {
                *counter        = info->counter;
                info->last_send = now;
                info->counter   = 1;
                info->mask      = mask;
                result = true;
            } // else
        } // if
        else {
            *counter        = info->counter;
            info->last_send = now;
            info->counter   = 1;
            info->mask      = mask;
            result = true;
        }
        
    } // todo counter muss noch zurückgeliefert werden
    
    return result;
}

void sms_send_ping(void) {
    uint16_t counter;
    if(sms_send(PING_TYPE, 0, &counter)) {

        char msg[1024];
        snprintf(msg, 1023, "Ping %f", rtu_get_vin());
        msg[1023] = '\0';
        
        send_message(msg);
    }
}

void sms_send_reboot_message(void) {
    uint16_t counter;
    if(sms_send(REBOOT_TYPE, 0, &counter)) {
        
        char msg[1024];
        snprintf(msg, 1023, "Booting %f", rtu_get_vin());
        msg[1023] = '\0';
        
        send_message(msg);
    }
}

void sms_send_vin_alert_message(float vin) {
    uint16_t counter;
    if(sms_send(VIN_ALERT_TYPE, 0, &counter)) {
        char msg[1024];
        if(counter > 1) {
            snprintf(msg, 1023, "Volt too low %f, repeated %d", rtu_get_vin(), counter);
        } // if
        else {
            snprintf(msg, 1023, "Volt too low %f", rtu_get_vin());
        } // else
        msg[1023] = '\0';
        send_message(msg);
    } // if
}

void sms_send_changes_alert_message(D_SENSORS *in) {
    uint16_t counter;
    
    if(sms_send(CHANGES_ALERT_TYPE, 0, &counter)) {
        char msg[1024];
        if(counter > 1) {
            snprintf(msg, 1023, "Changes detected\n%s\nrepeated %d", "1010", counter);
        } // if
        else {
            snprintf(msg, 1023, "Changes detected\n%s", "1010");
        } // else
        msg[1023] = '\0';
        send_message(msg);
    } // if
}

