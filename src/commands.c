//
//  subscriber.c
//  gsm-alarm
//
//  Created by Michael Maier on 21.07.19.
//

#include "commands.h"
#include "owasys-gsm-module.h"
#include "owasys-rtu-module.h"
#include "owa4x/owcomdefs.h"
#include "owa4x/owerrors.h"
#include "logger.h"
#include "d-sensors.h"
#include "user.h"
#include "loop.h"
#include "sms.h"

/**
 * Boot: liefert den aktuellen Status zurück und meldet einen Boot-Vorgang
 */
void cmd_boot(void) {
    
    uint8_t i = 0;
    while(i < admins.size) {
        char msg[1024];
        snprintf(msg, 1023, "Neustart\n\nStatus: %s\n\nSchrank: %s\nStuga: %s\nKueche-A: %s\nKueche-I: %s\nDach: %s\nMagazin: %s\n\nBat: %.2f V",
                 gIsLocked ? "scharf" : "nicht scharf",
                 gSwitches.switches[0].value ? "zu" : "OFFEN",
                 gSwitches.switches[1].value ? "zu" : "OFFEN",
                 gSwitches.switches[2].value ? "zu" : "OFFEN",
                 gSwitches.switches[3].value ? "zu" : "OFFEN",
                 gSwitches.switches[4].value ? "zu" : "OFFEN",
                 gSwitches.switches[5].value ? "zu" : "OFFEN",
                 rtu_get_vin()
                 );
        msg[1023] = '\0';
        
        gsm_send_sms(admins.users[i].number, msg);
        i += 1;
        
    } // while
}

/**
 *
 Ping
 
 Status: nicht scharf
 
 Schrank: OFFEN
 Stuga  : OFFEN
 Küche-A: OFFEN
 Küche-I: OFFEN
 Dach   : OFFEN
 Magazin: OFFEN
 
 Bat    : 12.23
 */
void cmd_ping(char *sender) {
    
    if(user_isAdmin(sender)) {
        char msg[1024];
        snprintf(msg, 1023, "Ping\n\nStatus: %s\n\nSchrank: %s\nStuga: %s\nKueche-A: %s\nKueche-I: %s\nDach: %s\nMagazin: %s\n\nBat: %.2f V",
                 gIsLocked ? "scharf" : "nicht scharf",
                 gSwitches.switches[0].value ? "zu" : "OFFEN",
                 gSwitches.switches[1].value ? "zu" : "OFFEN",
                 gSwitches.switches[2].value ? "zu" : "OFFEN",
                 gSwitches.switches[3].value ? "zu" : "OFFEN",
                 gSwitches.switches[4].value ? "zu" : "OFFEN",
                 gSwitches.switches[5].value ? "zu" : "OFFEN",
                 rtu_get_vin()
                 );
        msg[1023] = '\0';
        
        gsm_send_sms(sender, msg);
    } // if
}

void cmd_lock(char *sender) {
    
    if(user_isAdmin(sender)) {
        gIsLocked = true;
        loop_save_state();
        uint8_t i = 0;
        while(i < admins.size) {
            
            char msg[1024];
            snprintf(msg, 1023, "Scharf geschaltet von\n\n%s\n\nSchrank: %s\nStuga: %s\nKueche-A: %s\nKueche-I: %s\nDach: %s\nMagazin: %s",
                     sender,
                     gSwitches.switches[0].value ? "zu" : "OFFEN",
                     gSwitches.switches[1].value ? "zu" : "OFFEN",
                     gSwitches.switches[2].value ? "zu" : "OFFEN",
                     gSwitches.switches[3].value ? "zu" : "OFFEN",
                     gSwitches.switches[4].value ? "zu" : "OFFEN",
                     gSwitches.switches[5].value ? "zu" : "OFFEN"
                     );
            msg[1023] = '\0';
            
            gsm_send_sms(admins.users[i].number, msg);
            i += 1;
        } // 
    }
}

void cmd_unlock(char *sender) {
    if(user_isAdmin(sender)) {
        gIsLocked = false;
        loop_save_state();
        uint8_t i = 0;
        while(i < admins.size) {
            
            char msg[1024];
            snprintf(msg, 1023, "Ausgeschaltet von\n\n%s\n\nSchrank: %s\nStuga: %s\nKueche-A: %s\nKueche-I: %s\nDach: %s\nMagazin: %s",
                     sender,
                     gSwitches.switches[0].value ? "zu" : "OFFEN",
                     gSwitches.switches[1].value ? "zu" : "OFFEN",
                     gSwitches.switches[2].value ? "zu" : "OFFEN",
                     gSwitches.switches[3].value ? "zu" : "OFFEN",
                     gSwitches.switches[4].value ? "zu" : "OFFEN",
                     gSwitches.switches[5].value ? "zu" : "OFFEN"
                     );
            msg[1023] = '\0';
            
            gsm_send_sms(admins.users[i].number, msg);
            i += 1;
        } //
    }
}

static char* sensor_description(uint8_t sensorIndex) {
    
    switch(sensorIndex) {
        case 0: return "Schrank";
        case 1: return "Stuga";
        case 2: return "Kueche-A";
        case 3: return "Kueche-I";
        case 4: return "Dach";
        case 5: return "Magazin";
        default: return "Unbekannt";
    }
    
    return "Unbekannt";
}

static char* pir_description(uint8_t pirIndex) {
    switch(pirIndex) {
        case STUGA_PIR: return "Stuga";
        case KITCHEN_PIR_1: return "Kueche 1";
        case KITCHEN_PIR_2: return "Kueche 2";
        default: return "Unbekannt";
    }
}

void cmd_sensor_change(uint8_t sensorIndex, bool newValue) {

    if(sms_update_counter(sensorIndex)) {
        uint8_t i = 0;
        while(i < admins.size) {
            
            char msg[1024];
            snprintf(msg, 1023, "Aenderung festgestellt:\n\n%s = %s",
                     sensor_description(sensorIndex),
                     newValue ? "zu" : "OFFEN");
            msg[1023] = '\0';
            
            gsm_send_sms(admins.users[i].number, msg);
            i += 1;
        } //
        
        i = 0;
        while(i < recipients.size) {
            
            char msg[1024];
            snprintf(msg, 1023, "Aenderung festgestellt:\n\n%s = %s",
                     sensor_description(sensorIndex),
                     newValue ? "zu" : "AUF");
            msg[1023] = '\0';
            
            gsm_send_sms(recipients.users[i].number, msg);
            i += 1;
        } //

    } // if

}

void cmd_pir_detected(uint8_t pirIndex) {
    
     if(sms_update_counter((PIR1 + pirIndex))) {
        uint8_t i = 0;
        while(i < admins.size) {
            
            char msg[1024];
            snprintf(msg, 1023, "Bewegung in '%s' festgestellt!", pir_description(pirIndex));
            msg[1023] = '\0';
            
            gsm_send_sms(admins.users[i].number, msg);
            i += 1;
        } //
        
        i = 0;
        while(i < recipients.size) {
            
            char msg[1024];
            snprintf(msg, 1023, "Bewegung in '%s' festgestellt!", pir_description(pirIndex));
                     msg[1023] = '\0';
            
            gsm_send_sms(recipients.users[i].number, msg);
            i += 1;
        } //
        
    } // if
    
}

void cmd_add_admin(char *sender, char *admin) {    
    if(user_isAdmin(sender)) {
        user_add_admin(admin);
    } // if
} // if

void cmd_remove_admin(char *sender, char *admin) {
    if(user_isAdmin(sender)) {
        user_remove_admin(admin);
    } // if
} // if

void cmd_add_recipient(char *sender, char *recipient) {
    if(user_isAdmin(sender)) {
        user_add_recipient(recipient);
    } // if
} // if

void cmd_remove_recipient(char *sender, char *recipient) {
    if(user_isAdmin(sender)) {
        user_remove_recipient(recipient);
    } // if
} // if

/**
 * Stellt die Zähler für SMS-Sender zurück
 */
void cmd_reset(char *sender) {
    if(user_isAdmin(sender)) {
        sms_init();
        gsm_send_sms(sender, "Zaehler wurden auf 0 gesetzt.");
    } // if
}
