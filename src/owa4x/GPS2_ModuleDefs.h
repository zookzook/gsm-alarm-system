
#ifndef __GPS2_MODULEDEFS_H

   #define __GPS2_MODULEDEFS_H

//-----------------------------------------------------------------------//
//System Includes
//-----------------------------------------------------------------------//
	#include "owa4x/owcomdefs.h"
   #include <dlfcn.h>
	#include <termios.h>


//-----------------------------------------------------------------------//
//Defines
//-----------------------------------------------------------------------//
   #define		COM1  	0
   #define		COM2  	1
   #define		COM3  	2
   #define		COM4  	3
   #define		COM5  	4
   #define		COM6  	5
 
   #define		MAX_RECEIVER_NAME	20
   #define		MAX_PROTOCOL_NAME	10

   //ANTARIS Acquisition and Tracking sensitivity settings
   #define     NORMAL_ACQUISITION            0
   #define     FAST_ACQUISITION              1
   #define     HIGH_SENSITIVITY_ACQUISITION  2

   //Fixing Position mask flags
   #define FLAG_NONE     0x0000
   #define FLAG_NF       0x0001  // NF No Fix
   #define FLAG_DR       0x0002  // DR Dead reckoning only solution
   #define FLAG_G2       0x0004  // G2 Stand alone 2D solution
   #define FLAG_G3       0x0008  // G3 Stand alone 3D solution
   #define FLAG_D2       0x0010  // D2 Differential 2D solution
   #define FLAG_D3       0x0020  // D3 Differential 3D solution
   #define FLAG_RK       0x0040  // RK Combined GPS + dead reckoning solution
   #define FLAG_TT       0x0080  // TT Time only solution

   #define ALL_FIX_FLAGS (FLAG_NF | FLAG_DR | FLAG_G2 | FLAG_G3 | FLAG_D2 | FLAG_D3 | FLAG_RK | FLAG_TT)

   //Fix Status
   #define STATUS_NF       0  // NF No Fix
   #define STATUS_DR       1  // DR Dead reckoning only solution
   #define STATUS_G2       2  // G2 Stand alone 2D solution
   #define STATUS_G3       3  // G3 Stand alone 3D solution
   #define STATUS_D2       4  // D2 Differential 2D solution
   #define STATUS_D3       5  // D3 Differential 3D solution
   #define STATUS_RK       6  // RK Combined GPS + dead reckoning solution
   #define STATUS_TT       7  // TT Time only solution

//-----------------------------------------------------------------------//
//Type definitions
//-----------------------------------------------------------------------//

   typedef enum {
      GGA=0,
      GLL=1, 
      GSA=2,
      GSV=3,
      RMC=4,
      VTG=5,
      ZDA=7,
      PSRF161=9
   }MSGNMEA;

   typedef struct {
      unsigned short Degrees;
      unsigned char  Minutes;
      double         Seconds;
      char           Dir;
   }TGPS_COORD;

   typedef struct {   //Geodetic position type
      TGPS_COORD  Latitude,
                  Longitude;
      int         DataValid;
   }TGPS_POS;

   typedef struct {   //Speed and course type
      float  speed_in_knots;
      float  speed_in_mph;
      float  speed_in_kmh;	
      float  course_over_ground;
   }TGPS_SPEED;

   typedef enum {
      RATE_NO_MSG,
      RATE_POSITION,
      RATE_SPEED,
      RATE_GGA,
      RATE_GLL,
      RATE_GSA,
      RATE_GSV,
      RATE_RMC,
      RATE_VTG,
      RATE_ZDA,
      RATE_PSRF161,
      RATE_MSS
   }rateMsgType_e;

   typedef struct {
      rateMsgType_e   rateMsgType;
      TGPS_POS        Coordenates;
      TGPS_SPEED      Speed;
      char            Message[256];
   }TRATE_MESSAGE;

   typedef struct {   //GPS module configuration type
      char          DeviceReceiverName[MAX_RECEIVER_NAME];
      speed_t       ParamBaud;	
      int           ParamParity;
      unsigned char ParamLength;
      char          ProtocolName[MAX_PROTOCOL_NAME];
      unsigned char GPSPort;
   } TGPS_MODULE_CONFIGURATION;

   typedef enum {     //antenna status possible values for TIM gps
      ANTENNA_ON_OK = 0,
      OPEN_CIRCUIT,
      SHORT_CIRCUIT,
      ANTENNA_OFF,
      PASSIVE_ANTENNA,
      VALUE_NOT_VALID
   }AntennaStatusValue;

   typedef	struct {    //TIM antenna status type
      AntennaStatusValue Status;
      unsigned char      AGC;
   }TANTENNA_STATUS;

   typedef enum {       //antenna status possible values for new Antaris gps
      INIT = 0,
      STATUS_DONTKNOW,  //active antenna supervisor is not configured and deactivated
      OK,               //active antenna connected and powered
      SHORTCIRCUIT,     //antenna short
      OPEN              //antenna not connected or antenna defective
   }tAntennaStatusValue;

   typedef enum {       //antenna power state possible values for new Antaris gps
      OFF = 0,
      ON,
      POWER_DONTKNOW    
   }tAntennaPowerValue;
	
   typedef struct {      //ANTARIS antenna status type
      tAntennaStatusValue  A_Status;
      tAntennaPowerValue   A_Power;
   }tANTENNA_NEW_STATUS;

   typedef enum {
      HOT_START = 1,
      WARM_START,
      WARM_START_WITH_INIT,
      COLD_START,
      CLEAR_MEMORY = 8		
   }START_TYPE;

   typedef struct {   //UTC date and time type
      unsigned char Hours;     // 00...23
      unsigned char Minutes;   // 00...59
      float         Seconds;   // 00.00...59.99
      unsigned char Day;       // 01...31
      unsigned char Month;     // 01...12
      int           Year;      // 4 digit year
   }TUTC_DATE_TIME;

   typedef struct {  //ECEF coordinates type, only for ANTARIS gps
      int    Px;         // X position in centimeters
      int    Py;         // Y position in centimeters
      int    Pz;         // Z position in centimeters
      int    Vx;         // X velocity in cm/sec
      int    Vy;         // Y velocity in cm/sec
      int    Vz;         // Z velocity in cm/sec
   }tECEF_COORDINATES;

   typedef struct { //ESF Measurement data for Dead Reckoning Ublox6R
      int    Odom;     // Odometer speed value
      double Gyro;     // Gyroscope value
      double Temp;     // Temperature value
   }tESF_MEAS;

   typedef struct {    //UTM coordinates type, only for ANTARIS gps
      double        East;         // UTM easting in cm
      unsigned char LongitudeDir; // Longitude direction ('E'=East, 'W'=West)
      double        North;        // UTM northing in cm
      unsigned char Hemisphere;   // Hemisphere indicator ('N'=north, 'S'=south)
      unsigned char Zone;         // UTM zone number
      double        Altitude;     // Altitude in meters
      char          NavStatus[3]; // Navigation status
   }tUTM_COORDINATES;

   typedef struct {    //Geodetic coordinates type, only for ANTARIS gps
      TGPS_COORD  Latitude,        // Latitude
                  Longitude;       // Longitude
      double      Altitude;        // Altitude in meters
      char        NavStatus[3];    // Navigation status
   }tGEODETIC_COORDINATES;

   typedef struct {   //GNSS DOP type
      unsigned char PosFixMode;  // Position fix mode (1=fix not available, 2=2D position fix, 3=3D position fix)
      float         PDOP;        // Position dilution of precision
      float         HDOP;        // Horizontal dilution of precision
      float         VDOP;        // Vertical dilution of precision
   }tGNSS_DOP_SV;

   typedef struct {
      unsigned char SV_Id;
      unsigned char SV_Elevation;  //SV elevation in degrees
      short int     SV_Azimuth;    //SV azimuth in degrees
      char          SV_SNR;        //C/No ratio, range 0 to 99, null when no tracking
   }tSV_Data;

   typedef struct {   //GNSS SV in view type
      unsigned char SV_InView;
      tSV_Data      SV[16];
   }tGSV_Data;

   typedef struct {  //Datum parameters
         short   datumNum; 
         char    datumName[6];
         double  majA;
         double  flat;
         float    dX;
         float    dY;
         float    dZ; 
         float    rotX;
         float    rotY;
         float    rotZ;
         float    scale;
      }tDATUM;

	typedef struct {    //Geodetic coordinates type, only for ANTARIS gps
      unsigned char  PosValid;         // Valid Fix (according to configuration)
		unsigned char	OldValue;			// Data not updated
		TGPS_COORD 		Latitude,			// Latitude
							Longitude;			// Longitude
		double 			Altitude;			// Altitude in meters
		char				NavStatus[3];		// Navigation status
		double			HorizAccu;			// Horizontal Accuracy
		double			VertiAccu;			// Vertical Accuracy
		double			Speed;				// Speed over ground
		double			Course;				// Course over ground
		double			HDOP;					// Horizontal dilution of precision
		double			VDOP;					// Vertical dilution of precision
		double			TDOP;					// Time dilution of precision
		unsigned char	numSvs;				// Number of satellites used in the navigation solution
      double         LatDecimal;       // Latitude     negative degrees means South
      double         LonDecimal;       // Longitude    negative degrees means East
	}tPOSITION_DATA;

	typedef struct {    //Survey-in data
      unsigned int TimeOfWeek;      //GPS time of week in msecs
      char SurveyStatus;            //Survey-in status: 1->"In progress" otherwise 0
      char MeanPosValid;            //Survey-in position valid: 1->"Yes"
      unsigned int ObservationTime; //Observation time in seconds
      unsigned int PositionsUsed;   //Number of position observations
      double MeanPosAcc;            //Current survey-in mean position accuracy in meters
      double meanX;                 //Current survey-in mean position ECEF X coordinate in meters
      double meanY;                 //Current survey-in mean position ECEF Y coordinate in meters
      double meanZ;                 //Current survey-in mean position ECEF Z coordinate in meters
   }tNAV_SVIN_DATA;

	typedef struct {           //TMODE3 data
      unsigned char  mode;          //Receiver mode: 0 Disable, 1 Survey In, 2 Fixed Mode, 3-255 Reserved
      char           units;         //Position is given in ECEF(0) or LAT/LON/ALT(1)
      double         ecefX;         //ECEF X coorinate in meters
      double         ecefY;         //ECEF Y coorinate in meters
      double         ecefZ;         //ECEF Z coorinate in meters
      double         FixPosAccu;    //Fixed position accuracy in meters
      unsigned int   svinMinDur;    //Survey In minimum duration
      double         SurveyPosAccu; //Survey In position accuracy in meters
   }t_TMODE3_DATA;

	typedef struct {    //UBX-NAV-SOL data
		unsigned char	OldValue;      //Data is not updated
      double         TimeOfWeek;    //GPS time of week in seconds
      short int      WeekNumber;    //GPS week number
      unsigned char  gpsFix;        //GPSFix. 0: NoFix, 1: DR only, 2: 2D-Fix, 3: 3D-Fix, 4: GPS+DR, 5: Time only fix
      char           flags;         //Fix status flags. 0x01: Fix within limits, 0x02: DGPS used, 
                                    //                  0x04: Valid GPS week number, 0x08: Valid GPS time of week.
      double         ecefX;         //ECEF X coorinate in meters
      double         ecefY;         //ECEF Y coorinate in meters
      double         ecefZ;         //ECEF Z coorinate in meters
      double         PosAccu;       //3D Position Accurate Estimate
      double         ecefVX;        //ECEF X velocity in m/s
      double         ecefVY;        //ECEF Y velocity in m/s
      double         ecefVZ;        //ECEF Z velocity in m/s
      double         SpeedAccu;     //Speed Accuracy Estimate in m/s
      int            PositionDOP;   //Position DOP (Scaling 0.01)
      unsigned char  numSV;         //Number of SVs used in Nav Solution
   }tNAV_SOL_DATA;

   int GPS_Initialize( void *wConfiguration );
   int GPS_Start( void );
   int GPS_IsActive( int *wActive );
   int GPS_Finalize( void );
   int GPS_GetVersion( unsigned char *wVersion );

   int GPS_GetAllPositionData( tPOSITION_DATA *pCurCoords );
   int GPS_GetPosition_Polling( TGPS_POS *pCurCoords );
   int GPS_GetSpeedCourse_Polling( TGPS_SPEED *pCurSpeed );
   int GPS_GetUTCDateTime( TUTC_DATE_TIME *pDateTime );
   int GPS_GetStatusAntenna( tANTENNA_NEW_STATUS *pStatus );
   int GPS_GetGeodetic_Coordinates( tGEODETIC_COORDINATES *pGEODETIC_Coord );
   int GPS_GetSV_inView( tGSV_Data *pData );
   int GPS_Get_Software_Version( char *pData );
   int GPS_Configure_ITFM( char mode, char bbthres, char cwthres );
   int GPS_GetStatusJamming( char *pStatus );
   int GPS_SetNavigationConfig( unsigned char MinSV, unsigned char MinEle, short int PDOP );
   int GPS_SetFixConfig( short int wMask, unsigned int wHAccu);
   int GPS_GetFixConfig( short int *pMask, unsigned int *pHAccu);
   int GPS_Get_Model( char *pBuffer );
   int GPS_GetRELPOSNED_Data( char *pBuffer, int *pLen ); // ****
   int GPS_Send_DGPS_Message( char *pMessage, int Len );
   int GPS_GetCFG_NAV( char *pBuffer, int *pLen ); // ****
   int GPS_GetNAVX5_Data( char *pBuffer, int *pLen ); // ****
   int GPS_SetANA( char mode);
   int GPS_SetGpsMode( char GpsMode );
   int GPS_SetDynamicModel( char DynamicModel );
   int GPS_SetStaticThreshold( unsigned char Threshold );
   int GPS_GetDOP_FixMode( tGNSS_DOP_SV *pDOP_SV ); // ****
   int GPS_GetECEF_Coordinates( tECEF_COORDINATES *pECEF_Coord );
   int GPS_SetMeasurementRate( char measRate);
   int GPS_GetMeasurementRate( char *measRate);
   int GPS_EnableRTCM3( char mask, void(*wHandler)( char *, int) );
   int GPS_SetTMODE3_Fix( double ecefx, double ecefy, double ecefz, double accuracy ); // ****
   int GPS_SetTMODE3_Survey( unsigned int seconds, double accuracy ); // ****
   int GPS_SetTMODE3_Disable( void ); // ****
   int GPS_GetNAV_SVIN( tNAV_SVIN_DATA *pData );
   int GPS_Get_TMODE3( t_TMODE3_DATA *pData );
   int GPS_GetNAV_SOL( tNAV_SOL_DATA *pData );
//#ifdef OWA4X
   int GPS_Set_Led_Mode( unsigned char wMode );
//#endif

#endif
