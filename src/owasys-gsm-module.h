//
//  owasys-gsm-module.h
//  agent
//
//  Created by Michael Maier on 12.01.18.
//

#ifndef owasys_gsm_module_h
#define owasys_gsm_module_h

#include <stdio.h>
#include <stdbool.h>

typedef struct GSM_STATUS_STRUCT {
    
    bool signal;                        // Signal liegt vor
    bool network;                       // Network liegt vor
    bool failure;                       // GSM failure

} GSM_STATUS;

extern GSM_STATUS gGSMStatus;

int gsm_init( void );
int gsm_start( void );
int gsm_stop( void );

bool gsm_load_module( void );
bool gsm_unload_module( void );

bool gsm_is_active( void );
int gsm_get_strength( void );

char* gsm_get_imei( void );

int gsm_send_sms(char* destination, char* message);

#endif /* owasys_gsm_module_h */
