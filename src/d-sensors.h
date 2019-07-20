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

typedef struct D_SENSORS_STRUCT {
    
    bool sensor_1;
    bool sensor_2;
    bool sensor_3;
    bool sensor_4;
    bool sensor_5;
    bool sensor_6;
    bool sensor_7;
    bool sensor_8;
    bool sensor_9;
    
} D_SENSORS;

extern D_SENSORS gDSensors;

void sensors_init( void );
void sensors_send( void );
void sensors_dump(D_SENSORS *s);

void sensors_update_values(D_SENSORS* out);

int sensors_running_loop(void);


#endif /* d_sensors_h */
