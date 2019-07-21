//
//  owasys-rtu-module.c
//  fleetdevice
//
//  Created by Michael Maier on 25.10.17.
//

#include "owasys-rtu-module.h"
#include "logger.h"
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "watchdog.h"
#include "owa4x/owcomdefs.h"
#include "owa4x/owerrors.h"
#include "owa4x/RTUControlDefs.h"

static void *gRTULibHandle = NULL;

int (*FncRTUControl_Initialize)(void *);
int (*FncRTUControl_Start)(void);
int (*FncRTUControl_Finalize)(void);
int (*FncRTUGetAD_V_IN)(float *);
int (*FncRTUEnterStandby)(unsigned long, unsigned long);

static void load_rtu_functions( void ) {
    
    FncRTUControl_Initialize = ( int ( *) ( void *)) dlsym( gRTULibHandle, "RTUControl_Initialize");
    if( dlerror() != NULL)  {
        info("No RTUControl_Initialize() found");
    }
    
    FncRTUControl_Start = ( int ( *) ( void)) dlsym( gRTULibHandle, "RTUControl_Start");
    if( dlerror() != NULL)  {
        info("No RTUControl_Start() found");
    }
    
    FncRTUControl_Finalize = ( int ( *) ( void)) dlsym( gRTULibHandle, "RTUControl_Finalize");
    if( dlerror() != NULL)  {
        info("No RTUControl_Finalize() found");
    }
    
    FncRTUGetAD_V_IN = (int(*)(float*))dlsym( gRTULibHandle, "RTUGetAD_V_IN");
    if( dlerror() != NULL) {
        info( "No RTUGetAD_V_IN() found");
    }
    
    FncRTUEnterStandby = (int(*)(unsigned long, unsigned long))dlsym( gRTULibHandle, "RTUEnterStandby");
    if( dlerror() != NULL) {
        info( "No RTUEnterStandby() found");
    }
    
}

bool load_rtu_module( void ) {
    
    const char* libName= "/lib/libRTU_Module.so";
    gRTULibHandle = dlopen( libName, RTLD_LAZY );
    if( !gRTULibHandle ) {
        info("RTU: no shared library %s found", libName );
        info("RTU: %s", dlerror());
    } // if
    
    info( "RTU: loading rtu functions" );
    load_rtu_functions();

    int result = NO_ERROR;
    
    if( ( result = (*FncRTUControl_Initialize)(NULL)) != NO_ERROR) {
        info("RTU: error %d in FncRTUControl_Initialize()", result);
        return false;
    }
    
    if( ( result = (*FncRTUControl_Start)()) != NO_ERROR) {
        info("RTU: error %d in RTUControl_Start()", result);
        return false;
    }

    info( "RTU: started" );
    
    return true;
}

void unload_rtu_module( void ) {
    
    if(gRTULibHandle) {
        if( (dlclose( gRTULibHandle) ) != 0) {
            info( "RTU: unable to unload rtu module" );
        }
        
        info( "RTU: module unloaded" );
    } // if 
}

float rtu_get_vin( void ) {
    
    int ret= NO_ERROR;
    float result = 0.0;
    
    if( (ret= FncRTUGetAD_V_IN( &result ) ) != NO_ERROR ) {
        info( "RTU: unable to get vin %d", ret );
        result = -1.0;
    } // if
    
    return result;
}

void rtu_standby(void) {
    
    // gStandbyMode= true;
    
    info( "RTU: entering standby mode" );

    
    unsigned long mainWakeUp= (RTU_WKUP_DIN0 | RTU_WKUP_DIN2 | RTU_WKUP_DIN3 |
                               RTU_WKUP_DIN4 | RTU_WKUP_DIN5 | RTU_WKUP_DIN6 |
                               RTU_WKUP_DIN7 | RTU_WKUP_DIN8 | RTU_WKUP_DIN9); //  | RTU_WKUP_RTC); // RTU_WKUP_RXD0_WAKE |
    
    // io_dout_disable_CR();
    
    // rtu_set_rtc_wakeup( 60 ); // Jede Stunde gibt es einen Ping mit GPS-Koordinaten, wenn wir im Standby-Modus sind
    
    // io_switch_off_leds();
    
    // watchdog_restart();
    
    // info( "RTU: stopping gps" );
    // gps_stop();
    
    int ret= FncRTUEnterStandby( mainWakeUp, 0L );
    if( ret != NO_ERROR ) {
        info( "RTU: unable to enter the standby mode (%d)!", ret );
    }
    else {
        info( "RTU: woke up from standby mode" );
    } // else

    // resetting the watch dog
    // watchdog_restart();
    
    // unsigned long wakeUpReason= 0L;
    
    // gLastWakeupReason= WAKEUP_REASON_UNKNOWN;
    
    //int ret= FncRTUGetWakeUpReason( &wakeUpReason );
   
    
    // watchdog_init();
    //gStandbyMode= false;
}
