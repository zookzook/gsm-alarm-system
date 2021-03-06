#include "owasys-io-module.h"
#include <string.h>
#include <dlfcn.h>
#include "logger.h"
#include "owa4x/owcomdefs.h"
#include "owa4x/owerrors.h"
#include "owa4x/IOs_ModuleDefs.h"

static void *gIOLibHandle = NULL;

int (*FncIO_Initialize)(void);
int (*FncIO_Start)(void);
int (*FncIO_Finalize)( void);
int (*FncIO_IsActive)( int *);

int (*FncDIGIO_Get_DIN)(unsigned char, unsigned char *);
int (*FncDIGIO_Get_All_DIN)(unsigned short int *);
int (*FncDIGIO_Set_DOUT)(unsigned char,unsigned char);

static void load_io_generic_functions( void ) {
    
    FncIO_Initialize = ( int ( *) ( void )) dlsym( gIOLibHandle, "IO_Initialize");
    if( dlerror() != NULL)  {
        info("No IO_Initialize() found");
    }
    FncIO_Start = ( int ( *) ( void)) dlsym( gIOLibHandle, "IO_Start");
    if( dlerror() != NULL)  {
        info("No IO_Start() found");
    }
    FncIO_Finalize = ( int ( *) ( void)) dlsym( gIOLibHandle, "IO_Finalize");
    if( dlerror() != NULL)  {
        info("No IO_Finalize() found");
    }
    
    FncDIGIO_Get_All_DIN = (int(*)(unsigned short int *)) dlsym( gIOLibHandle, "DIGIO_Get_All_DIN");
    if( dlerror() != NULL)  {
        info("No DIGIO_Get_All_DIN found");
    }
    
    FncDIGIO_Set_DOUT = (int(*)(unsigned char,unsigned char)) dlsym( gIOLibHandle, "DIGIO_Set_DOUT");
    if( dlerror() != NULL)  {
        info("No DIGIO_Set_DOUT");
    }
    
}

static void load_io_functions( void ) {
    FncDIGIO_Get_DIN = ( int ( *) ( unsigned char, unsigned char *)) dlsym( gIOLibHandle, "DIGIO_Get_DIN");
    if( dlerror() != NULL)  {
        info("No DIGIO_Get_DIN found");
    }
}
bool load_io_module( void ) {
    
    const char* libName= "/lib/libIOs_Module.so";
    gIOLibHandle = dlopen( libName, RTLD_LAZY );
    if( !gIOLibHandle ) {
        info("No shared library %s found", libName );
        info("%s", dlerror());
    } // if
    
    info( "IO-Module loaded" );

    load_io_generic_functions();
    info( "IO generic functions loaded" );
    load_io_functions();
    info( "IO function loaded" );

    int result= 0;
    if( ( result = (*FncIO_Initialize)( )) != NO_ERROR) {
        info("Error %d in IO_Initialize()", result);
        return false;
    }
    if( ( result = (*FncIO_Start)()) != NO_ERROR) {
        info("Error %d in IO_Start()", result);
        (*FncIO_Finalize)();
        return false;
    }

    info( "IO Module intialized and started" );
    return true;
}

void unload_io_module() {
    
    if(gIOLibHandle) {
        if((dlclose(gIOLibHandle)) != 0) {
            info( "Unable to unload io module" );
        } // if
        else{
            info( "IO-Module unloaded" );
        } // else
    } // if
}

bool io_read_pin( unsigned char pin, bool *out ) {
    int result= 0;
    unsigned char pinResult;
    
    if( (result = (*FncDIGIO_Get_DIN)(pin, &pinResult)) == NO_ERROR) {
        *out= pinResult;
        return true;
    }
    else {
        info( "Unable to read pin %d, because of %d", pin, result );
        return false;
    }
    
}

bool io_read_all_pin(unsigned short int *out ) {
    
    int retVal = 0;
    
    if( (retVal = (*FncDIGIO_Get_All_DIN)(out)) == NO_ERROR) {
        return true;
    }
    else {
        info( "Unable to read all pins, because of %d", retVal );
        return false;
    }
}

void io_pir_on(void) {
    int ret = FncDIGIO_Set_DOUT(9, true);
    if(ret != NO_ERROR) {
        info("IO: Unable to set output of 9 to HIGH");
    }
}

void io_pir_off(void) {
    int ret = FncDIGIO_Set_DOUT(9, false);
    if(ret != NO_ERROR) {
        info("IO: Unable to set output of 9 to LOW");
    }
}
