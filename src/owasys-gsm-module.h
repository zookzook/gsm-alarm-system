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
#include "owa4x/GSM_ModuleDefs.h"

int gsm_init( void );
bool gsm_start(void) ;
int gsm_stop( void );
void gsm_start_worker(void);

bool gsm_load_module( void );
bool gsm_unload_module( void );

bool gsm_is_active( void );
int gsm_get_strength( void );

char* gsm_get_imei( void );

int gsm_send_sms(char* destination, char* message);
int gsm_read_sms(int wSMSIndex, SMS_s* wReadSMS, unsigned char *wSMSSize);

#endif /* owasys_gsm_module_h */
