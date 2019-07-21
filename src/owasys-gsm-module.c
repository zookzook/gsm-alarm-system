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
#include "owa4x/GSM_ModuleDefs.h"

#include <dlfcn.h>
#include <string.h>

static void *gGSMLibHandle = NULL;

GSM_STATUS gGSMStatus;

int ( *FncGSM_Initialize)  ( void*);
int ( *FncGSM_IsActive)    ( int*);
int ( *FncGSM_Finalize)    ( void);
int ( *FncGSM_Start)       ( void);
int ( *FncGSM_GetVersion)  ( unsigned char*);
int ( *FncGSM_GetSignalStrength)( unsigned char *wSignalStrength );
int ( *FncGSM_GetIMEI)  ( char*, int);
int ( *FncGSM_SendSMS)(unsigned char*, unsigned char*, char);

static void gsm_status_network( bool network ) {
    
    if( network != gGSMStatus.network ) {
        gGSMStatus.network= network;
        info( "GSM: network = %s", gGSMStatus.network ? "yes" : "no" );
    } // if
}

static void gsm_status_signal( bool signal ) {
    
    if( signal != gGSMStatus.signal ) {
        gGSMStatus.signal= signal;
        info( "GSM: signal = %s", gGSMStatus.signal ? "yes" : "no" );
    } // if
    
}

static void gsm_status_failure( bool failure ) {
    
    if( failure != gGSMStatus.failure ) {
        gGSMStatus.failure= failure;
        info( "GSM: failure = %s\n", gGSMStatus.failure ? "yes" : "no" );
    } // if
    
}

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
        info( "No GSM_WriteSMSToMemory found...\n");
        result= false;
    }
    
    return result;
}

/**
 *
 * GSM_NO_SIGNAL = 0: NO event
 * GSM_RING_VOICE: Incoming Voice call
 * GSM_RING_DATA: Incoming Data Call
 * GSM_CALL_RELEASED: Call released
 * GSM_FAILURE: GSM module failure. Restart it!!!!
 *
 * - 0: NO_NETWORK
 * - 1: HOME_REGISTERED
 * - 2: ROAMING_REGISTERED( usually abroad)
 * - 3: SOS_ONLY
 *
 * - 0: GPRS_NO_NETWORK
 * - 1: GPRS_REGISTERED
 * - 2: GPRS_SEARCHING
 * - 4: UNKNOWN (No further information: Treat it as No Network)
 * - 5: GPRS_REGISTERED_ROAM
 *
 */
static void gsm_event_handler( gsmEvents_s *pToEvent) {
    
    switch( pToEvent->gsmEventType ) {
        
        case GSM_NO_SIGNAL:
            info( "GSM: no gsm signal" );
            gsm_status_signal( false );
            break;
        
        case GSM_FAILURE:
            info( "GSM: failure" );
            gsm_status_signal( false );
            break;
        
        case GSM_COVERAGE:
            switch( pToEvent->evBuffer[ 0 ] ) {
                    
                case 0:
                    info( "GSM: no gsm network" );
                    gsm_status_signal( false );
                    break;

                case 1:
                    info( "GSM: gsm registered" );
                    gsm_status_signal( true );
                    break;

                default:
                    info( "GSM: gsm coverage: %d", pToEvent->evBuffer[ 0] );
                    break;
            }
            break;
            
        case GSM_GPRS_COVERAGE:
            switch( pToEvent->evBuffer[ 0 ] ) {
                    
                case 0:
                    info( "GSM: no gprs network" );
                    gsm_status_network( false );
                    break;
                    
                case 1:
                    info( "GSM: gprs network registered" );
                    gsm_status_network( true );
                    break;

                case 2:
                    info( "GSM: gprs network searching" );
                    gsm_status_network( false );
                    break;

                case 4:
                    info( "GSM: gprs network unknown" );
                    gsm_status_network( false );
                    break;

                case 5:
                    info( "GSM: gprs network roaming registered" );
                    gsm_status_network( true );
                    break;
                    
                default:
                    info( "GSM: gprs coverage: %d", pToEvent->evBuffer[ 0] );
                    break;
            }
            
            break;
        case GSM_BOARD_TEMP:
            info( "GSM: board temperatur %d", pToEvent->evBuffer[ 0] );
            break;
            
        case GSM_HIGHER_TEMP:
            info( "GSM: higher temperatur %d", pToEvent->evBuffer[ 0] );
            break;

        default:
            info( "GSM: misc event :%d, %d", pToEvent->gsmEventType, pToEvent->evBuffer[ 0] );
            break;

    }
    
    // pToEvent->evHandled= true;
}

int gsm_init( void ) {

    TGSM_MODULE_CONFIGURATION config;
    
    memset( &config, 0, sizeof( TGSM_MODULE_CONFIGURATION ) );
    strcpy( (char*)( config.wCode), "" );
    config.gsm_action = gsm_event_handler;
    
    info( "GSM: calling FncGSM_Initialize" );
    return FncGSM_Initialize( &config );
}

int gsm_start( void ) {
    info( "GSM: calling FncGSM_Start" );
    return FncGSM_Start();
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


void gsm_dump_values( void ) {
    
    info( "gGSMStatus.signal  = %s", gGSMStatus.signal ? "true" : "false" );
    info( "gGSMStatus.network = %s", gGSMStatus.network ? "true" : "false" );
    info( "gGSMStatus.failure = %s", gGSMStatus.failure ? "true" : "false" );
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

