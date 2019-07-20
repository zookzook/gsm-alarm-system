
#ifndef __RTUControlDefs_H

   #define __RTUControlDefs_H

   #include "owcomdefs.h"
   #include <dlfcn.h>
   #include <termios.h>

   #define MAX_PORT_NAME    16            // Name of the port
   typedef struct {                       // Select function configuration structure
      char     PortName[ MAX_PORT_NAME];  // Port name.
      int      FileDescriptor;            // File Descriptor
      void     *Object;                   // In case of SDK instead of API
      struct   termios  NewConfig;        // New configuration of the port to be opened
      struct   termios  OldConfig;        // Old Port configuration to be restaured before close the port.
      int      ToOpen;                    // Flag to open the port in the port list.
      int      ToClose;                   // Flag to close the port in the port list.
      int      ToEliminate;               // Flag to erase node from Select list.
   } TCONF_SELECT;

   #define ONE_TICK        0
   #define MULTIPLE_TICK   1

   typedef struct {
      unsigned char Release;
      unsigned char Version;
      unsigned char SubV;
   } StructVersion;

   typedef struct {
      unsigned long     Year;
      unsigned char     Month;
      unsigned char     Day;
      unsigned short    DayInYear;
      unsigned char     DayInWeek;
      unsigned char     Hour;
      unsigned char     Minute;
      unsigned char     Second;
   } TSYSTEM_TIME;

   typedef struct
   {
      unsigned char sec;
      unsigned char min;
      unsigned char hour;
      unsigned char day;
      unsigned char month;
      unsigned short year;
   } THW_TIME_DATE;

   typedef struct
   {
		unsigned char wEnable;			// Accelerometer Enabled(1) or Disabled(0). Only used when reading configuration 
		unsigned char wScale;			// Configures the operational range of the accelerometer(0...3).
		unsigned char wLimit;			// Threshold of the accelerometer(0...127). Bumps surpassing the threshold value will
												// send an interruption. Each step is equivalent to [scale] / 127
		unsigned char wTime;				// Time value(0...127) that the sensor must be moving before sending the interruption.
												// Each step is equivalent to 10 ms. 
		void(*wHandler)(int);	// Function handler to execute with a moving interruption.
		unsigned short int wMinTimeMovement;		// Minimun time detecting interrupts (0,2....900)
		unsigned short int wMaxTimeBetweenInts;	// Max time between interrupts to detect movement (0,1....300)
	} CONFIG_MOVEMENT_DETECT;

	#define TIMER_DISABLED		0

	#define MIN_TIME_MOVE		2
	#define MAX_TIME_MOVE		900

	#define MIN_TIME_INTS		1
	#define MAX_TIME_INTS		300
	


   // Power Management: defines with the mask of the return conditions
   #define LP_MODE_STANDBY      1
   #define LP_MODE_OFF          2
   

   // Bitmasks for comming back from  Power Management modes
   #define RTU_WKUP_MOVING     (1 << 0)
   #define RTU_WKUP_PWRFAIL    (1 << 1)
   #define RTU_WKUP_RXD2       (1 << 2)
   #define RTU_WKUP_RXD0_WAKE  (1 << 3)
   #define RTU_WKUP_RTC        (1 << 6)
   #define RTU_WKUP_DIN0       (1 << 7)
   #define RTU_WKUP_DIN1       (1 << 8)
   #define RTU_WKUP_DIN2       (1 << 9)
   #define RTU_WKUP_DIN3       (1 << 10)
   #define RTU_WKUP_DIN4       (1 << 11)
   #define RTU_WKUP_DIN5       (1 << 12)
   #define RTU_WKUP_DIN6       (1 << 13)
   #define RTU_WKUP_DIN7       (1 << 14)
   #define RTU_WKUP_DIN8       (1 << 15)
   #define RTU_WKUP_DIN9       (1 << 16)
   
   #define WKUP_ALL        (RTU_WKUP_MOVING | RTU_WKUP_PWRFAIL | RTU_WKUP_RXD2 | RTU_WKUP_RXD0_WAKE\
                           | RTU_WKUP_RTC | RTU_WKUP_DIN0 | RTU_WKUP_DIN1\
                           | RTU_WKUP_DIN2 | RTU_WKUP_DIN3 | RTU_WKUP_DIN4 | RTU_WKUP_DIN5 | RTU_WKUP_DIN6\
                           | RTU_WKUP_DIN7 | RTU_WKUP_DIN8 | RTU_WKUP_DIN9)

    #define IB_ID_LENGTH 8


   int RTUControl_Initialize( void *wConfiguration);
   int RTUControl_Start( void);
   int RTUControl_Finalize( void);
   int RTUControl_IsActive( int *wActive);
   int RTUControl_GetVersion( unsigned char *wVersion);

   int GetSystemTime( TSYSTEM_TIME *wSystemTime);
   int SetSystemTime( TSYSTEM_TIME wSystemTime);
   int usecsleep( int secs, int usecs);

   int OWASYS_GetTimer( unsigned char *wTimer, void ( *wHandler) ( unsigned char), unsigned long wSeconds, unsigned long wMicroSeconds );
   int OWASYS_StartTimer( unsigned char wTimer, unsigned char wMode );
   int OWASYS_FreeTimer( unsigned char wTimer);
   int OWASYS_StopTimer( unsigned char wTimer );
   int OWASYS_RestartTimer( unsigned char wTimer );

   int RTUGetHWTime(THW_TIME_DATE *CurrentTime);
   int RTUSetHWTime(THW_TIME_DATE CurrentTime);
   int RTUSetWakeUpTime(THW_TIME_DATE CurrentTime);
   int RTUSetIncrementalWakeUpTime(int secs);
   int RTUGetMoved(unsigned char *MovedValue);
   int RTUResetMoved(void);
//   int RTU_CfgMovementSensor( unsigned char wScale, unsigned char wLimit, unsigned char wTime, void(*wHandler)(move_int_t));
   int RTU_RemoveMovementSensor( void);
//   int RTU_GetMovementSensor( move_int_t *pData);
	int RTU_CfgMovementDetection( CONFIG_MOVEMENT_DETECT *wMovementCfg);
	int RTU_GetCfgMovement( CONFIG_MOVEMENT_DETECT *wMovementCfg);
//   int RTU_GetRawAcceleration( move_int_t *pData);

   int RTUEnterStandby(unsigned long wMainWakeup, unsigned long wExpWakeup); //Not yet implemented
   int RTUEnterStop(unsigned long wMainWakeup, unsigned long wExpWakeup);
   int RTUGetWakeUpReason(unsigned long *WakeUpReason);

   int RTUGetBatteryState(unsigned char *BattState);
   int RTUGetAD_VBAT_MAIN(float *ad_vbat_main);
   int RTUGetAD_V_IN(float *ad_v_in);
   int RTUGetAD_TEMP(int *ad_temp);

   int GetSerialNumber( unsigned char *wSerialNumber);
   int RTU_Get_Board_Version( unsigned char *pVersion);

#endif
