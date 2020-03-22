//
//  owasys-gsm-module.c
//  agent
//
//  Created by Michael Maier on 12.01.18.
//

#include "owasys-gsm-module.h"
#include "logger.h"
#include "owa4x/owcomdefs.h"
#include "owa4x/owerrors.h"
#include "commands.h"

#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_EVENTS 50

static gsmEvents_s buffer[MAX_EVENTS];
static int         writeIndex = 0;
static int         readIndex = 0;
static sem_t       sem;
static bool        keepRunning = true;
static pthread_t   workerThread;

static void *gGSMLibHandle = NULL;

int ( *FncGSM_Initialize)   ( void*);
int ( *FncGSM_IsActive)     ( int*);
int ( *FncGSM_Finalize)     ( void);
int ( *FncGSM_Start)        ( void);
int ( *FncGSM_GetVersion)   ( unsigned char*);
int ( *FncGSM_GetSignalStrength)( unsigned char *wSignalStrength );
int ( *FncGSM_GetIMEI)      (char*, int);
int ( *FncGSM_SendSMS)      (unsigned char*, unsigned char*, char);
int (*FncGSM_ReadSMS)       (SMS_s *, unsigned char *,char,char);
int (*FncGSM_DeleteSMS)     (char, char);
int (*FncGSM_SMSIndications)(int);


static bool gsm_load_generic_functions( void ) {
    
    bool result= true;
    
    FncGSM_Initialize = ( int ( *) ( void *)) dlsym( gGSMLibHandle, "GSM_Initialize");
    if( dlerror() != NULL) {
        info( "No GSM_Initialize found...\n");
        result= false;
    }
    FncGSM_Start = ( int ( *) ( void)) dlsym( gGSMLibHandle, "GSM_Start");
    if( dlerror() != NULL) {
        info( "No GSM_Start found...\n");
        result= false;
    }
    FncGSM_IsActive = ( int ( *) ( int *)) dlsym( gGSMLibHandle, "GSM_IsActive");
    if( dlerror() != NULL) {
        info( "No GSM_IsActive found...\n");
        result= false;
    }
    FncGSM_Finalize = ( int ( *) ( void)) dlsym( gGSMLibHandle, "GSM_Finalize");
    if( dlerror() != NULL) {
        info( "No GSM_Finalize found...\n");
        result= false;
    }
    FncGSM_GetVersion = ( int ( *) ( unsigned char *)) dlsym( gGSMLibHandle, "GSM_GetVersion");
    if( dlerror() != NULL) {
        info( "No GSM_GetVersion found...\n");
        result= false;
    }

    FncGSM_GetSignalStrength = ( int ( *) (  unsigned char *)) dlsym( gGSMLibHandle, "GSM_GetSignalStrength");
    if( dlerror() != NULL) {
        info( "No GSM_GetSignalStrength found...\n");
        result= false;
    }
    
    FncGSM_GetIMEI = ( int ( *) ( char *, int)) dlsym( gGSMLibHandle, "GSM_GetIMEI");
    if( dlerror() != NULL) {
        info( "No GSM_GetIMEI found...\n");
        result= false;
    }
    
    FncGSM_SendSMS = (int(*)(unsigned char*, unsigned char*, char)) dlsym( gGSMLibHandle, "GSM_SendSMS");
    if( dlerror() != NULL) {
        info( "No GSM_SendSMS found...\n");
        result= false;
    }
    
    FncGSM_ReadSMS = (int(*)(SMS_s *, unsigned char *,char,char)) dlsym( gGSMLibHandle, "GSM_ReadSMS");
    if( dlerror() != NULL) {
        info( "No GSM_ReadSMS found...\n");
        result= false;
    }
    
    FncGSM_DeleteSMS = (int(*)(char,char)) dlsym( gGSMLibHandle, "GSM_DeleteSMS");
    if( dlerror() != NULL) {
        info( "No GSM_DeleteSMS found...\n");
        result= false;
    }
    
    
    FncGSM_SMSIndications = (int(*)(int)) dlsym( gGSMLibHandle, "GSM_SMSIndications");
    if( dlerror() != NULL) {
        info( "No GSM_SMSIndications found...\n");
        result= false;
    }
    
    return result;
}


static void gsm_event_handler(gsmEvents_s *pToEvent) {
    
    int auxi = writeIndex + 1;
    
    buffer[writeIndex] = *pToEvent;
    if( writeIndex == readIndex) {
        writeIndex = auxi;
    } else {
        if( auxi >= MAX_EVENTS) {
            auxi = 0;
        }
        if( auxi != readIndex) {
            writeIndex = auxi;
        }
    }
    
    if( writeIndex >= MAX_EVENTS) {
        writeIndex = 0;
    }
    
    sem_post(&sem);
}

bool is_add_admin(char* sender, char* payload) {
    
    char user[80];
    uint8_t n = sscanf(payload, "admin-add %s", user);
    if( n == 1) {
        cmd_add_admin(sender, user);
    } // if
    
    return n == 1;
}

bool is_remove_admin_cmd(char* sender, char* payload) {
    
    char user[80];
    uint8_t n = sscanf(payload, "admin-remove %s", user);
    if( n == 1) {
        cmd_remove_admin(sender, user);
    } // if
    
    return n == 1;
}

bool is_add_recipient_cmd(char* sender, char* payload) {
    
    char user[80];
    uint8_t n = sscanf(payload, "add %s", user);
    if( n == 1) {
        cmd_add_recipient(sender, user);
    } // if
    
    return n == 1;
}

bool is_remove_recipient_cmd(char* sender, char* payload) {
    
    char user[80];
    uint8_t n = sscanf(payload, "remove %s", user);
    if( n == 1) {
        cmd_remove_recipient(sender, user);
    } // if
    
    return n == 1;
}

void dispatch_sms(SMS_s sms) {
    info("GSM: SMS(%d): Received %s @:%02d/%02d/%02d,%02d:%02d\n",
         sms.owIndex, sms.owSA_DA,
         sms.owSCDateTime.day,sms.owSCDateTime.month,
         sms.owSCDateTime.year, sms.owSCDateTime.hour,
         sms.owSCDateTime.minute);


    char *p = (char*)sms.owBody;
    for (; *p; ++p) {
        *p = tolower(*p);
    }
    char *sender = (char*)sms.owSA_DA;
    
    p = (char*)sms.owBody;
    info("GSM: message '%s'", p);
    if(strcmp(p, "lock") == 0) {
        cmd_lock(sender);
    }
    else if(strcmp(p, "unlock") == 0) {
        cmd_unlock(sender);
    }
    else  if(strcmp(p, "ping") == 0) {
        cmd_ping(sender);
    } // if
    else  if(strcmp(p, "reset") == 0) {
        cmd_reset(sender);
    } // if
    else if(is_add_admin(sender, p)) {
        info("Adding new admin");
    }    
    else if(is_remove_admin_cmd(sender, p)) {
        info("Removing admin");
    }
    else if(is_add_recipient_cmd(sender, p)) {
        info("Adding new recipient");
    }
    else if(is_remove_recipient_cmd(sender, p)) {
        info("Removing recipient");
    }

}

void* workerFnc(void *arg) {
    
    gsmEvents_s *owEvents;
    gsmEvents_s LocalEvent;
    //User Vars.
    int   retVal;

    //SMS
    int      index;
    SMS_s    incomingSMS;
    unsigned char SMSSize;
    
    while(keepRunning){
        sem_wait(&sem);
        if( readIndex == writeIndex) {
            continue;
        } // if
        
        LocalEvent = buffer[readIndex++];
        owEvents = &LocalEvent;
        if( readIndex >= MAX_EVENTS) {
            readIndex = 0;
        } // if
        switch (owEvents->gsmEventType){
            case GSM_NO_SIGNAL:
                break;
            case GSM_RING_VOICE:
            case GSM_RING_DATA:
                // ringTimes ++;
                if( owEvents->gsmEventType == GSM_RING_DATA){
                    info( "OWASYS--> GSM RING DATA signal Phone Number: %s \n", owEvents->evBuffer);
                } else {
                    info( "OWASYS--> GSM RING VOICE signal Phone Number: %s \n", owEvents->evBuffer);
                }
                break;
            case GSM_NEW_SMS:
                index = atoi(owEvents->evBuffer);
                info( "----------- EVENT: SMS index(%d) received ------------\n", index);
                retVal = gsm_read_sms(index, &incomingSMS, &SMSSize);
                if( retVal == NO_ERROR){
                    dispatch_sms(incomingSMS);
                }
                
                retVal = FncGSM_DeleteSMS(index, 0);
                if(retVal != NO_ERROR) {
                    info("GSM: unable to delete sms %d, because of %d", index, retVal);
                } // if
                
                break;
            case GSM_CALL_RELEASED:
                // callEnd = TRUE;
                info( "----------- EVENT: Call Finalized by the peer ------------");
                info(" \n>>");
                break;
            case GSM_RECEIVED_DATA:
                //gsmReceiveData(fileToReceive);
                break;
            case GSM_FAILURE:
                info( "----------- GSM ERROR ------------");
                // gsmError = TRUE;
                break;
            case GSM_COVERAGE:
                info( "GSM EVENT--> GSM COVERAGE INFO: %d\n", owEvents->evBuffer[ 0]);
                break;
            case GSM_HIGHER_TEMP:
                info( "GSM EVENT--> GSM HIGHER TEMP. Recommended GSM switch off\n");
                break;
            case GSM_STOP_SENDING_DATA:
                info( "GSM EVENT--> Stop Sending Data.\n");
                // sendingData = FALSE;
                break;
            case GSM_START_SENDING_DATA:
                info( "GSM EVENT--> Start Sending Data.\n");
                // sendingData = TRUE;
                break;
            case GSM_USSD_INFO:
                info( "GSM EVENT--> USSD Info --> %s\n", owEvents->evBuffer);
                break;
            case GSM_USSD_REPLY:
                info( "GSM EVENT--> USSD Reply Needed --> %s\n", owEvents->evBuffer);
                break;
            case GSM_USSD_ERROR:
                info( "GSM EVENT--> USSD ERROR --> %s\n", owEvents->evBuffer);
                break;
            case GSM_CALL_WAITING:
                info( "GSM EVENT--> Call Waiting from: %s\n", owEvents->evBuffer);
                break;
            case GSM_CONNECTED_LINE:
                info( "GSM EVENT--> Connected line id %s\n", owEvents->evBuffer);
                break;
            case GSM_GPRS_COVERAGE:
                info( "GSM EVENT--> GPRS COVERAGE INFO: %d\n", owEvents->evBuffer[ 0]);
                break;
            case GSM_RING_END:
                info( "GSM EVENT--> GSM RING END: Call cancelled at the peer\n");
                break;
            case GSM_MEM_SMS_FULL:
                info( "GSM EVENT--> SMS MEMORY IS FULL\n");
                break;
            case GSM_MEM_SMS_AVAI:
                info( "GSM EVENT--> SMS MEMORY IS AVAILABLE\n");
                break;
            case GSM_BOARD_TEMP:
                info( "GSM EVENT--> BOARD TEMPERATURE WARNING!!\n");
                switch ( owEvents->evBuffer[ 0]){
                    case 0:
                        info( "Below lowest temperature limit (immediate GSM switch-off)\n");
                        break;
                    case 1:
                        info( "Below low temperature alert limit\n");
                        break;
                    case 2:
                        info( "Normal operating temperature\n");
                        break;
                    case 3:
                        info( "Above upper temperature alert limit\n");
                        break;
                    case 4:
                        info( "Above uppermost temperature limit (immediate GSM switch-off)\n");
                        break;
                    default:
                        info( "Unknown temperature status\n");
                        break;
                }
                break;
            default:
                info( "OWASYS--> Signal Event not found ...%d \n", owEvents->gsmEventType);
        }
    }
    return NULL;
}

int gsm_init( void ) {

    TGSM_MODULE_CONFIGURATION config;
    
    memset( &config, 0, sizeof( TGSM_MODULE_CONFIGURATION ) );
    strcpy( (char*)( config.wCode), "" );
    config.gsm_action = gsm_event_handler;
    
    info( "GSM: calling FncGSM_Initialize" );
    return FncGSM_Initialize( &config );
}

static void clean_sms_memory(void) {
    
    uint8_t i = 0;
    while(i < 20) {
        int ret = FncGSM_DeleteSMS(i, 0);
        if(ret == NO_ERROR) {
            info("GSM: delete sms %d", i);
        } // if
        else {
            info("GSM: unable to delete sms at pos %d", i);
        } // else
        
        i += 1;
    }
}

bool gsm_start(void) {
    
    bool result = false;
    
    info( "GSM: calling FncGSM_Start" );
    int ret = FncGSM_Start();
    if(ret == NO_ERROR) {
        ret = FncGSM_SMSIndications(1);
        if(ret != NO_ERROR) {
            info("GSM: unable to set sms indications, because %d", ret);
        } // if
        else {
            clean_sms_memory();
            result = true;
        } // else
        
    } // if
    else {
        info("GSM: unable to start gsm");
    } // else
    
    return result;
}

bool gsm_load_module( void ) {
    
    const char* libName= "/lib/libGSM_Module.so";

    info( "GSM: Loading %s", libName );

    gGSMLibHandle = dlopen( libName, RTLD_LAZY );
    
    if( !gGSMLibHandle ) {
        info("GSM: No shared library %s found", libName );
        info("%s", dlerror());
        return false;
    } // if
    
    info( "GSM: Loading generic functions" );
    
    gsm_load_generic_functions();
    
    return true;
}

int gsm_stop( void ) {
    info( "GSM: calling FncGSM_Finalize" );
    return FncGSM_Finalize();
}

bool gsm_is_active( void ) {
    
    int state= 0;
    int ret= FncGSM_IsActive( &state );
    if( ret != NO_ERROR ) {
        info( "GSM: unable to get gsm active state %d", ret );
    } // if
    
    return state;
}

bool gsm_unload_module( void ) {
    
    if(gGSMLibHandle) {
        
        if(gsm_is_active()) {
            gsm_stop();
        } // if
        
        if( (dlclose( gGSMLibHandle) ) != 0) {
            info( "GSM: Unable to unload gsm module" );
        } // if
        else {
            info( "GSM: module unloaded" );
        } // else
        
        gGSMLibHandle = NULL;
    } // if
    
    return true;
}

int gsm_get_strength( void ) {
    
    unsigned char result= 99;
    int ret= FncGSM_GetSignalStrength( &result );
    if( ret != NO_ERROR ) {
        
        info( "GSM: unable to get signal strength %d", ret );
    }
    
    return result;
}

char* gsm_get_imei( void ) {
    
    static char result[100]= "";
    
    if( result[0] == '\0' ) {
        
        int ret= FncGSM_GetIMEI( result, 99 );
        if( ret == NO_ERROR ) {
            // everything is okay
        }
        else {
            // info( "GSM unable to get IMEI %d", ret );
            result[0]= '\0';
        }

    }
    
    return result;
}

int gsm_send_sms( char* destination, char* message) {
    
    int result = NO_ERROR;
    
    if((result = FncGSM_SendSMS((unsigned char*)message, (unsigned char*)destination, 0)) == NO_ERROR){
        info("SMS '%s' was sent to '%s' ", message, destination);
    } // iof
    else {
        info( "%d Error while sending message '%s' to '%s'", message, destination);
    } // else
    
    return result;
}

int gsm_read_sms(int wSMSIndex, SMS_s* wReadSMS, unsigned char *wSMSSize) {
    return FncGSM_ReadSMS(wReadSMS, wSMSSize, wSMSIndex, 0);
}

void gsm_start_worker(void) {
    
    memset(&buffer, 0x00, sizeof(buffer));
    writeIndex = 0;
    readIndex = 0;
    sem_init(&sem, 0, 0);

    pthread_create(&workerThread, NULL, workerFnc, NULL);
}
