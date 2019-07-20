
#ifndef __INET_MODULEDEFS_H

   #define __INET_MODULEDEFS_H

   #include "owa4x/owcomdefs.h"
   #include "owa4x/owerrors.h"

   //*********************** DEFINITION SECTION
   //EVENT TYPES
   #define  INET_RELEASED              1
   //BEARER TYPES
   #define  INET_BEARER_GPRS           1
   #define  INET_BEARER_ENHANCED_GPRS  2
   //OWASYS Definition
   #define  MAX_USER_SIZE         256
   #define  MAX_PWD_SIZE          256
   #define  MAX_IP_SIZE           39      //Ready for IPv6-> XXXX:XXXX:XXXX:XXXX:XXXX:XXXX:XXXX:XXXX
   #define  MAX_APN_SIZE          63
   //*********************** End of DEFINITION SECTION

   //*********************** TYPEDEF SECTION
   //Events Section
   typedef struct _INET_Events{
      unsigned char evType;
      int           evHandled;
   }INET_Events;

   //Configuration Section
   typedef struct _TINET_MODULE_CONFIGURATION{
      unsigned char  wBearer;                   //Internet Bearer:
//      int   wSignal;
      void* wBearerParameters;
      void  (*inet_action)( INET_Events * );
   }TINET_MODULE_CONFIGURATION;
   //Bearers Configuration
   //GPRS
   typedef struct _GPRS_CONFIGURATION{
      unsigned char gprsUser[ 20];             //User defined in the GPRS network
      unsigned char gprsPass[ 20];             //Password defined in the GPRS network
      unsigned char gprsDNS1[ 20];             //DNS1 defined in the GPRS network, if exists
      unsigned char gprsDNS2[ 20];             //DNS2 defined in the GPRS network, if exists
      unsigned char gprsAPN [ 20];            //Access Point Name for iNet in the GPRS network
   }GPRS_CONFIGURATION;

   //NOTE: GPRS_ENHANCED_CONFIGURATION is related to INET_BEARER_ENHANCED_GPRS.
   typedef struct _GPRS_ENHANCED_CONFIGURATION{
      unsigned char gprsUser[ MAX_USER_SIZE];        //User defined in the GPRS/INET network
      unsigned char gprsPass[ MAX_PWD_SIZE];         //Password defined in the GPRS/INET network
      unsigned char gprsDNS1[ MAX_IP_SIZE + 1];      //DNS1 defined in the GPRS network, if exists
      unsigned char gprsDNS2[ MAX_IP_SIZE + 1];      //DNS2 defined in the GPRS network, if exists
      unsigned char gprsAPN [ MAX_APN_SIZE + 1];     //Access Point Name for iNet in the GPRS network
   }GPRS_ENHANCED_CONFIGURATION;


   int iNet_Initialize          ( void *wConfiguration);
   int iNet_Finalize            ( void);
   int iNet_IsActive            ( int *wActive);
   int iNet_Start               ( void);
   int iNet_GetVersion          ( unsigned char *wVersion);
   int iNet_GetIPAddress        ( char *wIPAddress);
   int iNet_GetDataCounters     ( long *wTxBytes, long *wRxBytes);

   //*********************** End of DEFINITION SECTION
#endif

