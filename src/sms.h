//
//  sms.h
//  gsm-alarm
//
//  Created by Michael Maier on 19.07.19.
//

#ifndef sms_h
#define sms_h

#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "d-sensors.h"
// SMS-Type

#define VIN_ALERT_TYPE     0x01
#define REBOOT_TYPE        0x02
#define CHANGES_ALERT_TYPE 0x03
#define PING_TYPE          0x04

typedef struct SMS_INFO_STRUCT {
    
    time_t last_send;       // letzte Nachricht
    u_int8_t counter;       // Zähler
    u_int16_t mask;         // optionale Maske für die
    u_int16_t limit;        // Ruhephase in Sekunden
    
} SMS_INFO;

bool sms_send(u_int8_t type, u_int16_t mask, u_int16_t *counter);

void sms_send_ping(void);
void sms_send_reboot_message(void);
void sms_send_vin_alert_message(float vin);
void sms_send_changes_alert_message(D_SENSORS *in);

#endif /* sms_h */
