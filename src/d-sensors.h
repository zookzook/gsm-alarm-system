//
//  d-sensors.h
//  gsm-alarm
//
//  Created by Michael Maier on 19.07.19.
//

#ifndef d_sensors_h
#define d_sensors_h

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define LOCKER          0
#define STUGA_DOOR      1
#define KITCHEN_OUTSIDE 2
#define KITCHEN_INSIDE  3
#define LOFT            4
#define STOREROOM       5
#define MAX_SWITCHES    6

#define STUGA_PIR       0
#define KITCHEN_PIR_1   1
#define KITCHEN_PIR_2   2
#define MAX_PIRS        3

typedef struct SWITCH_STRUCT {

    bool value; // aktueller Wert
    time_t t;   // Zeitpunkt bei Änderungen für Cooldown-Verhalten
    
} SWITCH;

typedef struct SWITCHES_STRUCT {
    SWITCH switches[MAX_SWITCHES];
} SWITCHES;

typedef struct PIR_STRUCT {
    
    time_t t;   // Zeitpunkt bei Änderungen für Cooldown-Verhalten
    
} PIR;

typedef struct PIRS_STRUCT {
    PIR pirs[MAX_PIRS];
} PIRS;

extern SWITCHES gSwitches;
extern PIRS     gPIRs;

bool all_closed(void);
bool no_motions(void);

bool load_switches(void);
void init_pirs(void);

bool update_switches(time_t now, bool *changes);
bool update_pirs(time_t now, bool *changes);

#endif /* d_sensors_h */
