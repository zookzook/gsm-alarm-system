
#ifndef __IOS_MODULEDEFS_H

   #define __IOS_MODULEDEFS_H

   typedef struct {
      unsigned char InputNumber;
      unsigned char InputValue;
   } input_int_t;

   typedef struct {
      char scale;
      double x_axis;
      double y_axis;
      double z_axis;
   } move_int_t;

   int IO_Initialize( void );
   int IO_Start( void);
   int IO_Finalize( void);
   int IO_IsActive( int *wActive);
   int IO_GetVersion( char *wVersion);

   int DIGIO_Set_LED_SW0( unsigned char wValue );
   int DIGIO_Set_LED_SW0_Output( void );
   int DIGIO_Set_LED_SW0_Input( void );
   int DIGIO_Set_PPS_GPS( unsigned char wValue );
   int DIGIO_Set_PPS_GPS_Output( void );
   int DIGIO_Set_PPS_GPS_Input( void );

   int DIGIO_Set_LED_SW1( unsigned char wValue );
   int DIGIO_Set_LED_SW2( unsigned char wValue );

	int DIGIO_Set_GSM_ON( unsigned char wValue );
	int DIGIO_Set_DOUT( unsigned char wOutput, unsigned char wValue );
   int DIGIO_Set_All_DOUT( unsigned short int wOutput, unsigned short int wValue );
   int DIGIO_Set_FastShutDown(unsigned char wValue);
   int DIGIO_Get_PWR_IND( unsigned char *wValue );
	int DIGIO_Set_GSM_RST( unsigned char wValue );

   int DIGIO_Set_GPS_ON( unsigned char wValue );
   int DIGIO_Get_ANTENNA_OPEN( unsigned char *wValue );
   int DIGIO_Get_ANTENNA_SHORT( unsigned char *wValue );
   int DIGIO_Enable_Wifi(unsigned char wValue);
   int DIGIO_Enable_Bluetooth(unsigned char wValue);

	int DIGIO_Get_DIN( unsigned char wInput, unsigned char *wValue );
   int DIGIO_Get_All_DIN( unsigned short int *wValue );
   int DIGIO_ConfigureInterruptService( unsigned char wInput, unsigned char wEdge, void(*wHandler)(input_int_t), unsigned short int wNumInts);
   int DIGIO_GetNumberOfInterrupts( unsigned char wInput, unsigned long *pTotal);
   int DIGIO_RemoveInterruptService( unsigned char wInput);
   int DIGIO_Set_VOUT( unsigned char wValue );
   int DIGIO_Get_VOUT_STATUS( unsigned char *wValue );
   int DIGIO_Set_ADC_RANGE( unsigned char wRange, unsigned char wValue );
   int ANAGIO_GetAnalogIn( int anag_nbr, int *value );
   int DIGIO_Get_PWR_FAIL( unsigned char *wValue );

   int DIGIO_Set_Audio_Path( unsigned char wValue );

   int DIGIO_Enable_Can( char wValue);
	int DIGIO_Set_ETH_ON( unsigned char wValue );
   int DIGIO_Enable_RS485( char wValue );
   int DIGIO_Enable_KLINE( char wValue );

   // iButton
   int IBUTTON_Reset( void);
   int IBUTTON_ReadByte( unsigned char *pData);
   int IBUTTON_ReadData(unsigned short int wAddress, unsigned short int wSize, char *pData); 
   int IBUTTON_WriteByte( unsigned char Data);
   int IBUTTON_ReadID( unsigned char *pData);
   int IBUTTON_CfgInt( void(*wHandler)(unsigned char *));
   int IBUTTON_RemoveInt( void);
//   int OW_Discover(OneWireTable_t **OneWireROMList, unsigned char *OneWireROMListSize);
//	int OW_SetUpdate(void(*wHandler)(OneWireTable_t *, unsigned char, int), unsigned char);
//	int OW_ResetUpdate( void);

#endif /* __IOS_MODULEDEFS_H */

