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
#include <stdint.h>
#include <stdbool.h>

#define SENSOR1 0
#define SENSOR2 1
#define SENSOR3 2
#define SENSOR4 3
#define SENSOR5 4
#define SENSOR6 5
#define PIR1 6
#define PIR2 7
#define PIR3 8
#define VIN_ALERT 9
#define SMS_LENGTH 10

typedef struct SMS_INFO_STRUCT {
    
    time_t last_send;      // Zeitpunkt
    uint8_t counter;       // Zähler
    
} SMS_INFO;

void sms_init(void);
bool sms_update_counter(uint8_t index);
void sms_cleanup(void);

void sms_check_counter(time_t now);

void sms_init_pirs(void);

#endif /* sms_h */
