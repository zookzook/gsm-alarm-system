//
//  owasys-rtu-module.h
//  fleetdevice
//
//  Created by Michael Maier on 25.10.17.
//

#ifndef owasys_rtu_module_h
#define owasys_rtu_module_h

#include <stdio.h>
#include <stdbool.h>

bool load_rtu_module( void );
void unload_rtu_module( void );

// void rtu_check_idle_mode( void );

// void rtu_set_time( TUTC_DATE_TIME* t );

float rtu_get_vin(void);
float rtu_get_vbat(void);

void rtu_standby(void);

#endif /* owasys_rtu_module_h */
