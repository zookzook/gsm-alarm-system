
#ifndef __OWERRORS_H

   #define __OWERRORS_H

   #define NO_ERROR                                   0                          // All OK.
   #define ERROR_NOT_IMPLEMENTED                      1                          // Function not yet implemented.
   #define ERROR_IN_PARAMETERS                        2                          // Non-Valid Parameters
   //*************    RTU Section
   #define RTUCONTROL_ERROR_BASE                      3                          // Base error index for RTUControl error codes.
   #define ERROR_OPENING_PORT                         RTUCONTROL_ERROR_BASE + 0  // Error when opening port.
   #define ERROR_CLOSING_PORT                         RTUCONTROL_ERROR_BASE + 1  // Error chen closing port.
   #define ERROR_CREATING_NODE                        RTUCONTROL_ERROR_BASE + 2  // Insuficient memory for creating Port node.
   #define ERROR_UNDEFINED_NODE_STATUS                RTUCONTROL_ERROR_BASE + 3  // Invalid status of port.
   #define ERROR_INVALID_NODE                         RTUCONTROL_ERROR_BASE + 4  // No valid port node passed to function.
   #define ERROR_PORT_ALREADY_JOINED                  RTUCONTROL_ERROR_BASE + 5  // Port already inserted in Select list.
   #define ERROR_INSERTING_NODE                       RTUCONTROL_ERROR_BASE + 6  // Error when inserting Port node in Select list.
   #define ERROR_PORT_NOT_JOINED                      RTUCONTROL_ERROR_BASE + 7  // Port not inserted in Select list.
   #define ERROR_PORT_NOT_YET_CLOSED                  RTUCONTROL_ERROR_BASE + 8  // Port not closed when trying to delete from Select list.
   #define ERROR_RTUCONTROL_RESERVED                  RTUCONTROL_ERROR_BASE + 9  // Invalid parameter passed to function.
   #define ERROR_SELECT_ALREADY_RUNNING               RTUCONTROL_ERROR_BASE + 10 // Select Control loop already running.
   #define ERROR_SELECT_NOT_RUNNING                   RTUCONTROL_ERROR_BASE + 11 // Select control loop not running.
   #define ERROR_SELECT_LOOP_THREAD_CREATING          RTUCONTROL_ERROR_BASE + 12 // Impossible to create Select control loop thread.
   #define ERROR_SELECT_CLOSING_TIMEOUT               RTUCONTROL_ERROR_BASE + 13 // Timeout reached when closing Select control loop thread.
   #define ERROR_SELECT_LOOP_THREAD_CLOSING           RTUCONTROL_ERROR_BASE + 14 // Impossible to close Select control loop thread.
   #define ERROR_PORT_NOT_OPEN                        RTUCONTROL_ERROR_BASE + 15 // Port not open.
   #define ERROR_INVALID_FILE_DESCRIPTOR              RTUCONTROL_ERROR_BASE + 16 // Invalid file descriptor assigned to port.
   #define ERROR_INSUFICIENT_MEMORY                   RTUCONTROL_ERROR_BASE + 17 // No available memory for a reservation.
   #define ERROR_LAST_FREE_SIGNAL                     RTUCONTROL_ERROR_BASE + 18 // Last free signal obtained.
   #define ERROR_NO_FREE_SIGNALS_AVAILABLE            RTUCONTROL_ERROR_BASE + 19 // No free signals are available in the system.
   #define ERROR_RTUCONTROL_ALREADY_INITALIZED        RTUCONTROL_ERROR_BASE + 20 // RTU Control already initialized.
   #define ERROR_RTUCONTROL_NOT_INITALIZED            RTUCONTROL_ERROR_BASE + 21 // RTU Control not yet initialized.
   #define ERROR_RTUCONTROL_ALREADY_STARTED           RTUCONTROL_ERROR_BASE + 22 // RTU Control already started.
   #define ERROR_RTUCONTROL_NOT_STARTED               RTUCONTROL_ERROR_BASE + 23 // RTU Control not yet started.
   #define ERROR_OWA22XM_DRIVER_OPENING               RTUCONTROL_ERROR_BASE + 24 // Error when opening OWA22X_M driver.
   #define ERROR_OWA22XM_DRIVER_CLOSING               RTUCONTROL_ERROR_BASE + 25 // Error when closing OWA22X_M driver.
   #define ERROR_OWA22XM_DRIVER_ALREADY_OPENED        RTUCONTROL_ERROR_BASE + 26 // OWA22X_M driver already opened.
   #define ERROR_OWA22XM_DRIVER_NOT_OPENED            RTUCONTROL_ERROR_BASE + 27 // OWA22X_M driver not opened.
   #define ERROR_IN_COMMAND_CALL                      RTUCONTROL_ERROR_BASE + 28 // Error when executing a device driver IOCTL command.
   #define ERROR_PARTITION_NAME                       RTUCONTROL_ERROR_BASE + 29 // Error in file type
   #define ERROR_FILE_NAME                            RTUCONTROL_ERROR_BASE + 30 // Error in file name
   #define ERROR_BOOT_HEADER                          RTUCONTROL_ERROR_BASE + 31 // Error in BootLoader Header
   #define ERROR_OPENING_RTU_DRIVER                   RTUCONTROL_ERROR_BASE + 32 // Error Opening PM driver
   #define ERROR_CLOSING_RTU_DRIVER                   RTUCONTROL_ERROR_BASE + 33 // Error Closing PM driver
   #define ERROR_CALLING_RTU_DRIVER                   RTUCONTROL_ERROR_BASE + 34 // Error Calling PM driver
   #define ERROR_USECSLEEP_NOT_EXECUTED               RTUCONTROL_ERROR_BASE + 35 // Error calling usecsleep function. 
   #define ERROR_OWA3X_FD_DRIVER_OPENING              RTUCONTROL_ERROR_BASE + 36 // Error when opening owa3x_fd driver.
   #define ERROR_OWA3X_FD_DRIVER_CLOSING              RTUCONTROL_ERROR_BASE + 37 // Error when closing owa3x_fd driver.
   #define ERROR_OWA3X_FD_DRIVER_ALREADY_OPENED       RTUCONTROL_ERROR_BASE + 38 // owa3x_fd driver already opened.
   #define ERROR_OWA3X_FD_DRIVER_NOT_OPENED           RTUCONTROL_ERROR_BASE + 39 // owa3x_fd driver not opened.
   #define ERROR_POWER_MANAGEMENT_NOT_WORKING         RTUCONTROL_ERROR_BASE + 40 // Communication with the power managemnet unit not started.
   #define ERROR_POWER_MANAGEMENT_NOT_ANSWER          RTUCONTROL_ERROR_BASE + 41 // Not answer from power management unit.
   #define ERROR_OWA3X_PM_DRIVER_NOT_OPENED           RTUCONTROL_ERROR_BASE + 42 // owa3x_pm driver not opened.
   #define ERROR_OWA3X_DIGITAL_INPUT                  RTUCONTROL_ERROR_BASE + 43 // Impossible to read Digital Input.
   #define ERROR_OWA3X_DIGITAL_OUTPUT                 RTUCONTROL_ERROR_BASE + 44 // Impossible to set Digital Output.
   #define ERROR_OWA3X_CFG_INPUT_INT                  RTUCONTROL_ERROR_BASE + 45 // Impossible to config interrup for input.
   #define ERROR_OWA3X_BAD_INPUT_NUM                  RTUCONTROL_ERROR_BASE + 46 // Error in input number.
   #define ERROR_OWA3X_BAD_OUTPUT_NUM                 RTUCONTROL_ERROR_BASE + 47 // Error in Output number.
   #define ERROR_OWA3X_ALREADY_CFG                    RTUCONTROL_ERROR_BASE + 48 // Input already configured.
   #define ERROR_OWA3X_INT_NOT_ENABLED                RTUCONTROL_ERROR_BASE + 49 // Interrupt not enabled.
   #define ERROR_OWA3X_BAD_PD_SELECT                  RTUCONTROL_ERROR_BASE + 50 // Error in PD mask
   #define ERROR_OWA3X_BAD_OUTPUT_VAL                 RTUCONTROL_ERROR_BASE + 51 // Error in Output Value.
   #define ERROR_EXPANSION_BOARD_NOT_WORKING          RTUCONTROL_ERROR_BASE + 52 // Communication with the expansion board not possible.
   #define ERROR_EXPANSION_BOARD_NOT_ANSWER           RTUCONTROL_ERROR_BASE + 53 // Not answer from expansion board unit.
   #define ERROR_IBUTTON_NOT_DETECTED                 RTUCONTROL_ERROR_BASE + 54 // iButton not detected
   #define ERROR_UMOUNT_CMD                           RTUCONTROL_ERROR_BASE + 55 // error umount /home
   #define ERROR_MOUNT_CMD                            RTUCONTROL_ERROR_BASE + 56 // error mount /home
   #define ERROR_NOT_USED                             RTUCONTROL_ERROR_BASE + 57 // NOT_USED
   #define ERROR_OWA3X_ACCEL_NOT_READY                RTUCONTROL_ERROR_BASE + 58 // Acceleration not available.
   #define ERROR_ACCEL_ALREADY_STARTED                RTUCONTROL_ERROR_BASE + 59 // Accelerometer already started.

   //*************    IOs Section
   #define IOS_ERROR_BASE                             100
   #define ERROR_INVALID_OUTPUT_TYPE                  IOS_ERROR_BASE + 1  // Trying to use a Digital output as PWM, or viceverse.
   #define ERROR_INVALID_CALIBRATION_TYPE             IOS_ERROR_BASE + 2  // Invalid calibration type when configuring a AD input.
   #define ERROR_INVALID_END_ADVICE_TYPE              IOS_ERROR_BASE + 3  // Invalid end advice type when configuring a AD input.
   #define ERROR_INVALID_USAGE_TYPE                   IOS_ERROR_BASE + 4  // Invalid usage type when configuring a AD input.
   #define ERROR_INVALID_PWM_DUTY_CYCLE               IOS_ERROR_BASE + 5  // Invalid Duty Cycle value when configuring a PWM output.
   #define ERROR_INVALID_PWM_SOURCE_FREQ              IOS_ERROR_BASE + 6  // Invalid Source Frequency value when configuring a PWM output.
   #define ERROR_INVALID_PWM_CYCLE_TYPE               IOS_ERROR_BASE + 7  // Invalid Cycle type value when configuring a PWM output.
   #define ERROR_OPENING_DEVICE_DRIVER                IOS_ERROR_BASE + 8  // Problems when opening the device driver.
   #define ERROR_CLOSING_DEVICE_DRIVER                IOS_ERROR_BASE + 9  // Problems when closing the device driver.
   #define ERROR_IN_IOCTL_COMMAND                     IOS_ERROR_BASE + 10 // Error when executing a device driver IOCTL command.
   #define ERROR_TIMER_ALREADY_USED                   IOS_ERROR_BASE + 11 // Trying to use an already used timer.
   #define ERROR_TIMER_NOT_USED                       IOS_ERROR_BASE + 12 // Trying to disconnect a not used timer.
   #define ERROR_NO_FREE_TIMERS                       IOS_ERROR_BASE + 13 // There is no free timer available.
   #define ERROR_IOS_ALREADY_INITIALIZED              IOS_ERROR_BASE + 14 // IOs Module already initialized.
   #define ERROR_IOS_NOT_INITIALIZED                  IOS_ERROR_BASE + 15 // IOs Module not yet initialized.
   #define ERROR_IOS_ALREADY_STARTED                  IOS_ERROR_BASE + 16 // IOs Module already started.
   #define ERROR_IOS_NOT_STARTED                      IOS_ERROR_BASE + 17 // IOs Module not yet started.
   #define ERROR_READ_ANALOG_INPUT                    IOS_ERROR_BASE + 18 // Error reading analog input.
   #define ERROR_IBUTTON_SEARCHING                    IOS_ERROR_BASE + 19 // iButton searching in progress
	#define ERROR_OW_DISCOVERING                       IOS_ERROR_BASE + 20 // 1-WIRE automatic update in progress
	#define ERROR_OW_TOO_MANY_DEVICES                  IOS_ERROR_BASE + 21 // More than MAX_OW_DEVICES in 1-WIRE
   #define ERROR_IB_DATA_SIZE                         IOS_ERROR_BASE + 22 // iButton data size too big

   //*************    GSM Section
   #define GSM_ERROR_BASE                             200
   #define GSM_ERR_ME_FAILURE                         GSM_ERROR_BASE + 0  // GSM failure
   #define GSM_ERR_CONNECTION_FAILURE                 GSM_ERROR_BASE + 1  // Connection failure with the net.
   #define GSM_ERR_ME_PHONE_ADAPTOR_LINK_RESERVED     GSM_ERROR_BASE + 2
   #define GSM_ERR_OPERATION_NOT_ALLOWED              GSM_ERROR_BASE + 3  // Operation not allowed by the GSM
   #define GSM_ERR_OPERATION_NOT_SUPPORTED            GSM_ERROR_BASE + 4  // Operation not supported
   #define GSM_ERR_PH_SIM_PIN_REQUIRED                GSM_ERROR_BASE + 5  // Phone SIM PIN required. Phone Code Locked
   #define GSM_ERR_SIM_NOT_INSERTED                   GSM_ERROR_BASE + 6  // SIM not inserted.
   #define GSM_ERR_SIM_PIN_REQUIRED                   GSM_ERROR_BASE + 7  // SIM PIN required
   #define GSM_ERR_SIM_PUK_REQUIRED                   GSM_ERROR_BASE + 8  // SIM PUK required
   #define GSM_ERR_SIM_FAILURE                        GSM_ERROR_BASE + 9  // SIM failure. Contact operator
   #define GSM_ERR_SIM_BUSY                           GSM_ERROR_BASE + 10 // SIM is busy.
   #define GSM_ERR_SIM_WRONG                          GSM_ERROR_BASE + 11 // SIM operation wrong.
   #define GSM_ERR_INCORRECT_PASSWORD                 GSM_ERROR_BASE + 12 // SIM incorrect password, change.
   #define GSM_ERR_SIM_PIN2_REQUIRED                  GSM_ERROR_BASE + 13 // SIM PIN2 required
   #define GSM_ERR_SIM_PUK2_REQUIRED                  GSM_ERROR_BASE + 14 // SIM PUK2 required
   #define GSM_ERR_MEMORY_FULL                        GSM_ERROR_BASE + 15 // GSM folder full( PhoneBook / SIM)
   #define GSM_ERR_INVALID_INDEX                      GSM_ERROR_BASE + 16 // Index non used or major than max index.(SMS/PB)
   #define GSM_ERR_NOT_FOUND                          GSM_ERROR_BASE + 17
   #define GSM_ERR_MEMORY_FAILURE                     GSM_ERROR_BASE + 18 // There is a memory failure (SIM/ME)
   #define GSM_ERR_TEXT_STRING_TOO_LONG               GSM_ERROR_BASE + 19
   #define GSM_ERR_INVALID_CHARACTERS_IN_TEXT_STRING  GSM_ERROR_BASE + 20
   #define GSM_ERR_DIAL_STRING_TOO_LONG               GSM_ERROR_BASE + 21 // The dial string is too long
   #define GSM_ERR_INVALID_CHARACTERS_IN_DIAL_STRING  GSM_ERROR_BASE + 22 // Dial String has invalid characters
   #define GSM_ERR_NO_NETWORK_SERVICE                 GSM_ERROR_BASE + 23 // There is no GSM network service
   #define GSM_ERR_NETWORK_TIMEOUT                    GSM_ERROR_BASE + 24 // GSM Network returns timeout.
   #define GSM_ERR_UNKNOWN                            GSM_ERROR_BASE + 25 // Unknown SMS error on the function
      //SMS FAILURES
   #define GSM_ERR_SMS_ME_FAILURE                     GSM_ERROR_BASE + 26 // Failure on sending a SMS
   #define GSM_ERR_SMS_SERVICE_OF_ME_RESERVED         GSM_ERROR_BASE + 27
   #define GSM_ERR_SMS_OPERATION_NOT_ALLOWED          GSM_ERROR_BASE + 28 // SMS Operation not allowed
   #define GSM_ERR_SMS_OPERATION_NOT_SUPPORTED        GSM_ERROR_BASE + 29 // SMS Operation not supported.
   #define GSM_ERR_SMS_INVALID_PDU_MODE_PARAMETER     GSM_ERROR_BASE + 30 // Invalid PDU sending SMS
   #define GSM_ERR_SMS_SMSC_ADDRESS_UNKNOWN           GSM_ERROR_BASE + 31 // SMSC Unknown
   #define GSM_ERR_SMS_NO_CNMA_ACK_EXPECTED           GSM_ERROR_BASE + 32 // CNMA ACK not received
   #define GSM_ERR_SMS_UNKNOWN                        GSM_ERROR_BASE + 33 // Unknown Error on SMSs
   #define GSM_ERR_BUSY                               GSM_ERROR_BASE + 34 // Remote side is busy
   #define GSM_ERR_NO_ANSWER                          GSM_ERROR_BASE + 35 // No answer at the peer side.
   #define GSM_ERR_NO_CARRIER                         GSM_ERROR_BASE + 36 // Network has released the current call.
   #define GSM_ERR_DIALING                            GSM_ERROR_BASE + 37 // Error if trying to dial when it is on conversation or other
   #define GSM_ERR_INIT_FAILURE                       GSM_ERROR_BASE + 38 // GSM Initialization Failure: Due to communication lack
   #define GSM_ERR_TIMEOUT                            GSM_ERROR_BASE + 39 // GSM Function securety timeout
   #define GSM_ERR_DATA_MODE                          GSM_ERROR_BASE + 40 // GSM is in data mode.
   #define GSM_ERR_GENERAL_FAILURE                    GSM_ERROR_BASE + 41 // GSM communication lost.
   #define GSM_ERR_INIT_IN_PROGRESS                   GSM_ERROR_BASE + 42 // GSM is being initialized
   #define GSM_ERR_IN_GPRS_PARAM                      GSM_ERROR_BASE + 43 // Non-valid GPRS parameters
   #define GSM_ERR_ALREADY_INITIALIZED                GSM_ERROR_BASE + 44 // GSM Module already initialized.
   #define GSM_ERR_NOT_INITIALIZED                    GSM_ERROR_BASE + 45 // GSM Module not yet initialized.
   #define GSM_ERR_ALREADY_STARTED                    GSM_ERROR_BASE + 46 // GSM Module already started.
   #define GSM_ERR_NOT_STARTED                        GSM_ERROR_BASE + 47 // GSM Module not yet started.
   #define GSM_ERR_INVALID_DATA                       GSM_ERROR_BASE + 48 // Error due to Failure on Data.
   #define GSM_ERR_NETWORK_LOCK                       GSM_ERROR_BASE + 49 // Network Lock
   #define GSM_ERR_SMS_TYPE                           GSM_ERROR_BASE + 50 // Unknown SMS format
   #define GSM_ERR_AUDIO_PARAMETER                    GSM_ERROR_BASE + 51 // Error on the Audio file.
   #define GSM_ERR_NOT_SWITCHED_ON                    GSM_ERROR_BASE + 52 // GSM HW has an error and does not switch on.
   #define GSM_ERR_PLMN_SELECT_FAILURE                GSM_ERROR_BASE + 53 // PLMN selection failure
   #define GSM_ERR_NO_DIALTONE                        GSM_ERROR_BASE + 54 // NO DIALTONE present
   #define GSM_ERR_OPEN_AUDIO                         GSM_ERROR_BASE + 55 // Error opening digital audio system
   #define GSM_ERR_AUDIO_ALLOC_HW                     GSM_ERROR_BASE + 56 // Error allocating HW structure
   #define GSM_ERR_AUDIO_INIT_HW                      GSM_ERROR_BASE + 57 // Error initializing HW structure
   #define GSM_ERR_AUDIO_SET_ACTYPE                   GSM_ERROR_BASE + 58 // Error setting access type
   #define GSM_ERR_AUDIO_SAMP_FORM                    GSM_ERROR_BASE + 59 // Error setting sample format
   #define GSM_ERR_AUDIO_SAMP_RATE                    GSM_ERROR_BASE + 60 // Error setting sample rate
   #define GSM_ERR_AUDIO_CHAN_COUNT                   GSM_ERROR_BASE + 61 // Error setting channel count
   #define GSM_ERR_AUDIO_SET_PARAMS                   GSM_ERROR_BASE + 62 // Error setting HW parameters
   #define GSM_ERR_AUDIO_PCM_PREPARE                  GSM_ERROR_BASE + 63 // Error in PCM prepare
   #define GSM_ERR_AUDIO_PCM_LINK                     GSM_ERROR_BASE + 64 // Error in PCM link
   #define GSM_ERR_AUDIO_NOT_ALLOWED                  GSM_ERROR_BASE + 65 // Digital audio not allowed
   #define GSM_ERR_PS_BUSY                            GSM_ERROR_BASE + 66 // PS Busy
   #define GSM_ERR_SMS_SIM_NOT_READY                  GSM_ERROR_BASE + 67 // SIM not ready
   #define GSM_ERR_AUDIO_ALREADY_OPENED               GSM_ERROR_BASE + 68 // Digital audio already opened
   #define GSM_ERR_REJECTED_BUSY                      GSM_ERROR_BASE + 69 // Remote side rejects call (busy)
   #define GSM_ERR_NOT_TIME_AVAILABLE                 GSM_ERROR_BASE + 70 // None connection time available
   #define GSM_ERR_NO_LCP_TIME                        GSM_ERROR_BASE + 71 // No LCP time available
   #define GSM_ERR_NO_IP_TIME                         GSM_ERROR_BASE + 72 // No IP time available
   #define GSM_ERR_LINK_CREATE                        GSM_ERROR_BASE + 73 // Not possible to create link

   //..
   //Reserved ranges for GSM_ERR:                     GSM_ERROR_BASE + 100

   //*************    GPS Section
   #define GPS_ERROR_BASE                             400
   #define ERROR_IN_GPS_TYPE                          GPS_ERROR_BASE + 1
   #define ERROR_NO_VALID_BAUDRATE                    GPS_ERROR_BASE + 2
   #define ERROR_NO_VALID_PARITY                      GPS_ERROR_BASE + 3
   #define ERROR_NO_VALID_BYTE_LENGTH                 GPS_ERROR_BASE + 4
   #define ERROR_NO_VALID_STOPBITS                    GPS_ERROR_BASE + 5
   #define ERROR_NO_VALID_PROTOCOL                    GPS_ERROR_BASE + 6
   #define ERROR_PROTOCOL_NOT_IMPLEMENTED             GPS_ERROR_BASE + 7
   #define ERROR_NO_VALID_PORT                        GPS_ERROR_BASE + 8
   #define ERROR_GPS_NOT_STARTED                      GPS_ERROR_BASE + 9
   #define ERROR_MSG_NOT_SENT_TO_GPS                  GPS_ERROR_BASE + 10
   #define ERROR_NO_DATA_FROM_GPS                     GPS_ERROR_BASE + 11
   #define ERROR_GPS_MSG_WITH_BAD_CHK                 GPS_ERROR_BASE + 12
   #define ERROR_GPS_PORT_NOT_OPENED                  GPS_ERROR_BASE + 13
   #define ERROR_GPS_NOT_POWER_ON                     GPS_ERROR_BASE + 14
   #define ERROR_UNLINKPORT_IN_FINALIZE               GPS_ERROR_BASE + 15
   #define ERROR_UNLOAD_LIBRARY_IN_FINALIZE           GPS_ERROR_BASE + 16
   #define ERROR_MSG_NOT_ALLOWED                      GPS_ERROR_BASE + 17
   #define ERROR_GPS_ALREADY_INITIALIZED              GPS_ERROR_BASE + 18
   #define ERROR_GPS_NOT_INITIALIZED                  GPS_ERROR_BASE + 19
   #define ERROR_GPS_ALREADY_STARTED                  GPS_ERROR_BASE + 20
   #define ERROR_GPS_BINARY_TIMEOUT                   GPS_ERROR_BASE + 21
   #define ERROR_GPS_BINARY_NACK                      GPS_ERROR_BASE + 22
   #define ERROR_FUNCTION_NOT_ALLOWED_IN_NMEA         GPS_ERROR_BASE + 23
   #define ERROR_FUNCTION_NOT_ALLOWED_IN_BINARY       GPS_ERROR_BASE + 24
   #define ERROR_NO_MEMORY_IN_GPS_FUNCTION            GPS_ERROR_BASE + 25
   #define ERROR_FUNCTION_NOT_ALLOWED_ON_GPS          GPS_ERROR_BASE + 26
   #define ERROR_GPS_BINARY_TX                        GPS_ERROR_BASE + 27
   #define ERROR_GPS_BINARY_WAIT                      GPS_ERROR_BASE + 28
   #define ERROR_GPS_BINARY_RX_NACK                   GPS_ERROR_BASE + 29
   #define ERROR_GPS_NOT_NEW_MSG                      GPS_ERROR_BASE + 30
   #define ERROR_GPS_RX_WAIT                          GPS_ERROR_BASE + 31
   #define ERROR_GPS_BIN_CHK                          GPS_ERROR_BASE + 32
   #define ERROR_NO_VALID_MEAS_RATE                   GPS_ERROR_BASE + 33

   // ****************** TEST_ORION Section

   #define TEST_ERROR_BASE                            500
   #define ERROR_TEST_IO                              TEST_ERROR_BASE + 1
   #define ERROR_TEST_RTU                             TEST_ERROR_BASE + 2
   #define ERROR_TEST_GSM                             TEST_ERROR_BASE + 3
   #define ERROR_TEST_UART                            TEST_ERROR_BASE + 4
   #define ERROR_TEST_LED                             TEST_ERROR_BASE + 5

   //****************** INET ERROR Section
   
   #define INET_ERROR_BASE                            600
   #define ERROR_INET_ALREADY_RUNNING                 INET_ERROR_BASE + 0
   #define ERROR_INET_NOT_INITIALIZED                 INET_ERROR_BASE + 1
   #define ERROR_INET_NOT_STARTED                     INET_ERROR_BASE + 2
   #define ERROR_INET_IP_IF_NOT_READY                 INET_ERROR_BASE + 3   //IF error by the kernel on IPget
   #define ERROR_INET_IP_NOT_AVAILABLE                INET_ERROR_BASE + 4   //No IP availble. Lack of Connection
   #define ERROR_INET_GSM_ON_VOICE                    INET_ERROR_BASE + 5   //GSM on Voice, inet stop not available
   #define ERROR_INET_GSM_ON_CALL                     INET_ERROR_BASE + 6   //GSM on Call, inet stop not available

   // ****************** SERIAL PORT SECTION:

   #define SERIAL_ERROR_BASE                          700
   #define ERROR_SERIAL_OPENING_PORT                  SERIAL_ERROR_BASE + 0  // Error opening serial port.
   #define ERROR_SERIAL_CLOSING_PORT                  SERIAL_ERROR_BASE + 1  // Error closing serial port.
   #define ERROR_SERIAL_SET_PARAMETERS                SERIAL_ERROR_BASE + 2  // Error setting parameters of serial port.
   #define ERROR_SERIAL_GET_PARAMETERS                SERIAL_ERROR_BASE + 3  // Error getting parameters of serial port.
   #define ERROR_SERIAL_SET_TIMEOUTS                  SERIAL_ERROR_BASE + 4  // Error setting timeouts of serial port.
   #define ERROR_SERIAL_BUFFER_NOT_ALLOCATED          SERIAL_ERROR_BASE + 5  // Not space allocated for In/Out buffers.
   #define ERROR_SERIAL_WRITE_ERROR                   SERIAL_ERROR_BASE + 6  // Error writting in serial port.
   #define ERROR_SERIAL_READ_ERROR                    SERIAL_ERROR_BASE + 7  // Error reading from serial port.
   #define ERROR_SERIAL_RX_TIMEOUT                    SERIAL_ERROR_BASE + 8  // Timeout overpassed reading from serial port.
   #define ERROR_SERIAL_INVALID_BAUD_SPEED            SERIAL_ERROR_BASE + 9  // Invalid value for Baud Speed.
   #define ERROR_SERIAL_INVALID_DATABITS              SERIAL_ERROR_BASE + 10 // Invalid value for Data Bits.
   #define ERROR_SERIAL_INVALID_PARITY                SERIAL_ERROR_BASE + 11 // Invalid value for Parity.
   #define ERROR_SERIAL_INVALID_STOPBITS              SERIAL_ERROR_BASE + 12 // Invalid value for Stop bits.
   #define ERROR_SERIAL_INVALID_FLOWCONTROL           SERIAL_ERROR_BASE + 13 // Invalid value for Flow Control.
   #define ERROR_SERIAL_IN_PARAMETER                  SERIAL_ERROR_BASE + 14 // Invalid parameter passed to function.
   #define ERROR_SERIAL_ALREADY_INITIALIZED           SERIAL_ERROR_BASE + 15 // Port already initialized.
   #define ERROR_SERIAL_NOT_INITIALIZED               SERIAL_ERROR_BASE + 16 // Port not yet initialized.
   #define ERROR_SERIAL_ALREADY_STARTED               SERIAL_ERROR_BASE + 17 // Port already started.
   #define ERROR_SERIAL_NOT_STARTED                   SERIAL_ERROR_BASE + 18 // Port not yet started.
   #define ERROR_SERIAL_INVALID_TYPE                  SERIAL_ERROR_BASE + 19 // Invalid type of serial Port.


   #define ERROR_SERIAL_INVALID_NUM_OF_PORTS          SERIAL_ERROR_BASE + 20 // Invalid number of serial ports.
   #define ERROR_SERIAL_CREATING_NODE                 SERIAL_ERROR_BASE + 21 // Error when creating port node for list.
   #define ERROR_SERIAL_INSERTING_NODE                SERIAL_ERROR_BASE + 22 // Error when inserting port node in list.
   #define ERROR_SERIAL_INVALID_COM_PORT              SERIAL_ERROR_BASE + 23 // Invalid COM port number.
   #define ERROR_SERIAL_PORT_OCCUPIED                 SERIAL_ERROR_BASE + 24 // Port already assigned.
   #define ERROR_SERIAL_PORT_SELECT_LINKED            SERIAL_ERROR_BASE + 25 // Port already linked to Select Port.
   #define ERROR_SERIAL_PORT_NOT_OCCUPIED             SERIAL_ERROR_BASE + 26 // Port not assigned.
   #define ERROR_SERIAL_PORT_NOT_SELECT_LINKED        SERIAL_ERROR_BASE + 27 // Port not linked to Select Port.
   #define ERROR_SERIAL_INVALID_OPERATION             SERIAL_ERROR_BASE + 28 // This operation does not work with this Serial port.

   // OWASYS Reserved Error Range:
   // ERROR_BASE        800

   // Sound
   #define SOUND_ERROR_BASE                     900

   #define ERROR_SOUND_DRV_ALREADY_OPENED       SOUND_ERROR_BASE + 10
   #define ERROR_SOUND_DRV_OPEN                 SOUND_ERROR_BASE + 11
   #define ERROR_SOUND_DRV_INVALID_DESCRIPTOR   SOUND_ERROR_BASE + 12
   #define ERROR_SOUND_DRV_IOCTL                SOUND_ERROR_BASE + 13
   #define ERROR_SOUND_CONFIG_NOT_VALID         SOUND_ERROR_BASE + 14

   #define ERROR_SOUND_NOT_INITIALIZED          SOUND_ERROR_BASE + 40
   #define ERROR_SOUND_NOT_STARTED              SOUND_ERROR_BASE + 41
   #define ERROR_SOUND_ALREADY_INITIALIZED      SOUND_ERROR_BASE + 42
   #define ERROR_SOUND_ALREADY_STARTED          SOUND_ERROR_BASE + 43

   #define ERROR_PLAY_NOT_INITIALIZED           SOUND_ERROR_BASE + 80
   #define ERROR_PLAY_NOT_STARTED               SOUND_ERROR_BASE + 81
   #define ERROR_PLAY_ALREADY_INITIALIZED       SOUND_ERROR_BASE + 82
   #define ERROR_PLAY_ALREADY_STARTED           SOUND_ERROR_BASE + 83
   #define ERROR_PLAY_CONVERSION_THREAD         SOUND_ERROR_BASE + 84
   #define ERROR_PLAY_THREAD_NOT_CANCEL         SOUND_ERROR_BASE + 85
   #define ERROR_PLAY_MEMORY_FAULT              SOUND_ERROR_BASE + 86
   #define ERROR_PLAY_BUSY                      SOUND_ERROR_BASE + 87
   #define ERROR_PLAY_NO_FILE                   SOUND_ERROR_BASE + 88
   #define ERROR_PLAY_CONFIG_NOT_VALID          SOUND_ERROR_BASE + 89
   #define ERROR_PLAY_INVALID_VALUE             SOUND_ERROR_BASE + 90
   #define ERROR_PLAY_FILENAME_ERROR            SOUND_ERROR_BASE + 91

   // OWASYS Reserved Error Range:
   // ERROR_BASE        1000

   //****************** BT ERROR Section

   #define BT_ERROR_BASE			                     1100
   #define ERROR_BT_NO_ERROR                          BT_ERROR_BASE     + 0
   #define ERROR_BT_UNKNOWN_HCI_COMMAND               BT_ERROR_BASE     + 1
   #define ERROR_BT_NO_CONNECTION                     BT_ERROR_BASE     + 2
   #define ERROR_BT_HARDWARE_FAILURE                  BT_ERROR_BASE     + 3
   #define ERROR_BT_PAGE_TIMEOUT                      BT_ERROR_BASE     + 4
   #define ERROR_BT_AUTHENTICATION_FAILURE            BT_ERROR_BASE     + 5
   #define ERROR_BT_KEY_MISSING                       BT_ERROR_BASE     + 6
   #define ERROR_BT_MEMORY_FULL                       BT_ERROR_BASE     + 7
   #define ERROR_BT_CONNECTION_TIMEOUT                BT_ERROR_BASE     + 8
   #define ERROR_BT_MAX_NUMBER_OF_CONNECTIONS         BT_ERROR_BASE     + 9
   #define ERROR_BT_MAX_NUMBER OF_SCO_CONNECTIONS     BT_ERROR_BASE     + 10
   #define ERROR_BT_ACL_CONNECTION_ALREADY_EXIST      BT_ERROR_BASE     + 11
   #define ERROR_BT_OMMAND_DISALLOWED                 BT_ERROR_BASE     + 12
   #define ERROR_BT_HOST_REJECTED_LIMITED_RESORCES    BT_ERROR_BASE     + 13
   #define ERROR_BT_HOST_REJECTED_SECURITY_REASON     BT_ERROR_BASE     + 14
   #define ERROR_BT_HOST_REJ_REM_DEV_PERSONAL_DEV     BT_ERROR_BASE     + 15
   #define ERROR_BT_HOST_TIMEOUT                      BT_ERROR_BASE     + 16
   #define ERROR_BT_UNSUPPORTED_FEATURE_OR_PARAM_VAL  BT_ERROR_BASE     + 17
   #define ERROR_BT_HCI_COMMAND_PARAMETERS            BT_ERROR_BASE     + 18
   #define ERROR_BT_USER_ENDED_CONNECTION             BT_ERROR_BASE     + 19
   #define ERROR_BT_LOW_RESORCES                      BT_ERROR_BASE     + 20
   #define ERROR_BT_ABOUT_TO_POWER_OF                 BT_ERROR_BASE     + 21
   #define ERROR_BT_CONN_TERMINATED_BY_LOCAL_HOST     BT_ERROR_BASE     + 22
   #define ERROR_BT_REPEATED_ATTEMPTS                 BT_ERROR_BASE     + 23
   #define ERROR_BT_PAIRING_NOT_ALLOWED               BT_ERROR_BASE     + 24
   #define ERROR_BT_UNKNOWN_LMP_PDU                   BT_ERROR_BASE     + 25
   #define ERROR_BT_UNSUPPORTED_REMOTE_FEATURE        BT_ERROR_BASE     + 26
   #define ERROR_BT_SCO_OFFSET_REJECTED               BT_ERROR_BASE     + 27
   #define ERROR_BT_SCO_INTERVAL_REJECTED             BT_ERROR_BASE     + 28
   #define ERROR_BT_SCO_AIRMODE_REJECTED              BT_ERROR_BASE     + 29
   #define ERROR_BT_INVALID_LMP_PARAMETERS            BT_ERROR_BASE     + 30
   #define ERROR_BT_UNSPECIFIED_ERROR                 BT_ERROR_BASE     + 31
   #define ERROR_BT_UNSUPPORTED_LMP_PARAMETERS_VALUE  BT_ERROR_BASE     + 32
   #define ERROR_BT_ROLE_CHANGE_NOT_ALLOWED           BT_ERROR_BASE     + 33
   #define ERROR_BT_LMP_RESPONSE_TIME_OUT             BT_ERROR_BASE     + 34
   #define ERROR_BT_LMP_TRANSACTION_COLLISION         BT_ERROR_BASE     + 35
   #define ERROR_BT_LMP_PDU_NOT_ALLOWED               BT_ERROR_BASE     + 36
   #define ERROR_BT_BTSTACK_INITIALIZATION_FAILED     BT_ERROR_BASE     + 37
   #define ERROR_BT_BLUETOOTH_PORT_ALREADY_IN_USE     BT_ERROR_BASE     + 38
   #define ERROR_BT_DEVICE_UNKNOWN	              BT_ERROR_BASE     + 39
   #define ERROR_BT_UNABLE_TO_GET_DEV_ATTR            BT_ERROR_BASE     + 40
   #define ERROR_BT_DEVICE_IS_DOWN                    BT_ERROR_BASE     + 41
   #define ERROR_BT_UNABLE_TO_OPEN_DEVICE             BT_ERROR_BASE     + 42
   #define ERROR_BT_INCORRECT_ADDRESS_GIVEN           BT_ERROR_BASE     + 43
   #define ERROR_BT_UNABLE_TO_CREATE_BT_SOCKET        BT_ERROR_BASE     + 44
   #define ERROR_BT_UNABLE_TO_CREATE_CONNECTION       BT_ERROR_BASE     + 45
   #define ERROR_BT_CONNECTION_NOT_FOUND              BT_ERROR_BASE     + 46
   #define ERROR_BT_UNABLE_TO_CREATE_DIR              BT_ERROR_BASE     + 47
   #define ERROR_BT_FORMAT_ERROR                      BT_ERROR_BASE     + 48
   #define ERROR_BT_BAD_ARGUMENTS                     BT_ERROR_BASE     + 49
   #define ERROR_BT_UNABLE_TO_CREATE_RFCOMM_SOCKET    BT_ERROR_BASE     + 50
   #define ERROR_BT_UNABLE_TO_CONNECT_TO_REM_SIDE     BT_ERROR_BASE     + 51
   #define ERROR_BT_PING_ERROR                        BT_ERROR_BASE     + 52
   #define ERROR_BT_UNABLE_TO_GET_PORT_INFO	      BT_ERROR_BASE	   + 53
   #define ERROR_BT_UNABLE_SET_RF_IFACE_TYPE_TO_TTY   BT_ERROR_BASE	   + 54
   #define ERROR_BT_UNABLE_TO_BIND_PORT_TO_SOCK	      BT_ERROR_BASE	   + 55
   #define ERROR_BT_UNABLE_TO_DISCONNECT_SERVICE      BT_ERROR_BASE	   + 56
   #define ERROR_BT_MESSAGE_LOOP_ALREADY_RUNNING      BT_ERROR_BASE	   + 57		
   #define ERROR_BT_MESSAGE_LOOP_THREAD_CREATING      BT_ERROR_BASE	   + 58
   #define ERROR_BT_MESSAGE_LOOP_NOT_RUNNING          BT_ERROR_BASE	   + 59	
   #define ERROR_BT_SERVICE_NAME_INCORRECT	         BT_ERROR_BASE	   + 60
   #define ERROR_BT_UUID_NO_MATCH_WITH_SERVICE        BT_ERROR_BASE     + 61
   #define ERROR_BT_UUID_NOT_CORRECT_NO_SERVICE       BT_ERROR_BASE     + 62
   #define ERROR_BT_UNABLE_DOWN_DEVICE		            BT_ERROR_BASE	   + 63		
   #define ERROR_BT_NO_SUCH_DEVICE		               BT_ERROR_BASE	   + 64	
   #define ERROR_BT_NO_CONNECTION_WITH_SUCH_ADDRESS   BT_ERROR_BASE	   + 65
   #define ERROR_BT_INVALID_OPTION		               BT_ERROR_BASE	   + 66	
   #define ERROR_BT_CANNOT_INIT_UART		            BT_ERROR_BASE	   + 67	
   #define ERROR_BT_INVALID_PARAMETER		            BT_ERROR_BASE     + 68
   #define ERROR_BT_CONNECTION_ALREADY_EXISTS	      BT_ERROR_BASE	   + 69	
   #define ERROR_BT_CREATING_SCO		                  BT_ERROR_BASE	   + 70	
   #define ERROR_BT_CACHE_LOAD			               BT_ERROR_BASE     + 71
   #define ERROR_BT_CANT_SETUP_UART                   BT_ERROR_BASE     + 72
   #define ERROR_BT_MAP_SCO_PCM                       BT_ERROR_BASE     + 73
   #define ERROR_BT_ERROR_IN_INQUIRING                BT_ERROR_BASE     + 74
   #define ERROR_BT_ERROR_IN_DISCOVERING              BT_ERROR_BASE     + 75
   #define ERROR_BT_ERROR_READING_CHANGING_NAME       BT_ERROR_BASE     + 76
   #define ERROR_BT_CONNECTION_TO_SDPSERVER_FAILED    BT_ERROR_BASE	   + 77
   #define ERROR_BT_ERROR_READING_NAME    	         BT_ERROR_BASE	   + 78
   #define ERROR_BT_ERROR_CHANGING_NAME               BT_ERROR_BASE	   + 79
   #define ERROR_BT_SCO_DISCONNECTION_ERROR	         BT_ERROR_BASE     + 80	
   #define ERROR_BT_NOT_INITIALIZED	                  BT_ERROR_BASE     + 81
   #define ERROR_BT_NOT_STARTED	                     BT_ERROR_BASE     + 82
   #define ERROR_BT_NO_CONNECTIONS_AVAILABLE          BT_ERROR_BASE     + 83
   #define ERROR_BT_NO_MEMORY_AVAILABLE               BT_ERROR_BASE     + 84
   #define ERROR_BT_INTERNAL_ERROR                    BT_ERROR_BASE     + 85
   #define ERROR_BT_UNKNOWN_SERVICE                   BT_ERROR_BASE     + 86
   #define ERROR_BT_SERVICE_NOT_FOUND                 BT_ERROR_BASE     + 87
   #define ERROR_BT_SERVICE_NOT_AVAILABLE             BT_ERROR_BASE     + 88
   #define ERROR_BT_GETTING_CHANNEL                   BT_ERROR_BASE     + 89
   #define ERROR_BT_DISCONNECTING_LINE                BT_ERROR_BASE     + 90
   #define ERROR_BT_WRITE_PCM_SET                     BT_ERROR_BASE     + 91
   #define ERROR_BT_SCO_NOT_CREATED                   BT_ERROR_BASE     + 92
   #define ERROR_BT_OTHER_SCO_EXIST                   BT_ERROR_BASE     + 93
   #define ERROR_BT_ADDR_NOT_PAIRED                   BT_ERROR_BASE     + 94

   //****************** TETRA ERROR Section
   #define TETRA_ERROR_BASE			                  1400
   #define ERROR_TETRA_LOAD_LIB                       TETRA_ERROR_BASE + 0
   #define ERROR_TETRA_LIB_NOT_FOUND                  TETRA_ERROR_BASE + 1
   #define ERROR_TETRA_FUNC_NOT_FOUND                 TETRA_ERROR_BASE + 2
   #define TETRA_ERR_ALREADY_INITIALIZED              TETRA_ERROR_BASE + 3
   #define TETRA_ERR_INITIALIZING                     TETRA_ERROR_BASE + 4
   #define TETRA_ERR_NOT_STARTED                      TETRA_ERROR_BASE + 5
   #define TETRA_ERR_NOT_INITIALIZED                  TETRA_ERROR_BASE + 6
   #define TETRA_ERR_ALREADY_STARTED                  TETRA_ERROR_BASE + 7
   #define TETRA_ERR_OPEN_PORT                        TETRA_ERROR_BASE + 8
   #define TETRA_ERR_CLOSE_PORT                       TETRA_ERROR_BASE + 9
   #define TETRA_ERR_START                            TETRA_ERROR_BASE + 10
   #define TETRA_ERR_INIT_FAILURE                     TETRA_ERROR_BASE + 11
   #define TETRA_ERR_UNKNOWN                          TETRA_ERROR_BASE + 12
   #define TETRA_ERR_GENERAL_FAILURE                  TETRA_ERROR_BASE + 13
   #define TETRA_ERR_TIMEOUT                          TETRA_ERROR_BASE + 14
   #define TETRA_MODEM_FAILURE                        TETRA_ERROR_BASE + 15
   #define TETRA_OPERATION_NOT_ALLOWED                TETRA_ERROR_BASE + 16
   #define TETRA_OPERATION_NOT_SUPPORTED              TETRA_ERROR_BASE + 17
   #define TETRA_INCORRECT_MS_PUK							TETRA_ERROR_BASE + 18
	#define TETRA_SIM_NOT_INSERTED							TETRA_ERROR_BASE + 19 
	#define TETRA_MS_PIN_REQUIRED								TETRA_ERROR_BASE + 20
	#define TETRA_MS_PUK_REQUIRED								TETRA_ERROR_BASE + 21
	#define TETRA_SIM_FAILURE									TETRA_ERROR_BASE + 22
	#define TETRA_SIM_BUSY										TETRA_ERROR_BASE + 23
	#define TETRA_SIM_WRONG										TETRA_ERROR_BASE + 24
	#define TETRA_MS_INCORRECT_PIN							TETRA_ERROR_BASE + 25
	#define TETRA_SIM_BLOCKED									TETRA_ERROR_BASE + 26
	#define TETRA_MEMORY_FULL									TETRA_ERROR_BASE + 27
   #define TETRA_TEXT_STRING_TOO_LONG                 TETRA_ERROR_BASE + 28
   #define TETRA_INVALID_CHARACTERS_IN_TEXT_STRING    TETRA_ERROR_BASE + 29
   #define TETRA_DIAL_STRING_TOO_LONG                 TETRA_ERROR_BASE + 30
   #define TETRA_INVALID_CHARACTERS_IN_DIAL_STRING    TETRA_ERROR_BASE + 32
	#define TETRA_NO_NETWORK_SERVICE                   TETRA_ERROR_BASE + 32
	#define TETRA_NETWORK_TIMEOUT								TETRA_ERROR_BASE + 33
	#define TETRA_PARAM_WRONG_TYPE							TETRA_ERROR_BASE + 34
	#define TETRA_PARAM_VAL_OUT_OF_RANGE					TETRA_ERROR_BASE + 35
	#define TETRA_SYNTAX_ERROR									TETRA_ERROR_BASE + 36
	#define TETRA_TIMEOUT_WAITING_DATA						TETRA_ERROR_BASE + 37
	#define TETRA_NOT_SUPPORTED_IN_DMO						TETRA_ERROR_BASE + 38
	#define TETRA_TRANSMISSIONS_INHIBITED					TETRA_ERROR_BASE + 39
	#define TETRA_SERVICE_TEMP_UNAVAILABLE					TETRA_ERROR_BASE + 40
	#define TETRA_NOT_SUPPORTED_IN_TMO						TETRA_ERROR_BASE + 41
	#define TETRA_SERVICE_TEMP_UNAVAILABLE_1				TETRA_ERROR_BASE + 42
	#define TETRA_RC_PIN_REQUIRED								TETRA_ERROR_BASE + 43
	#define TETRA_INCORRECT_RC_PIN							TETRA_ERROR_BASE + 44
	#define TETRA_INVALID_PDU_MODE							TETRA_ERROR_BASE + 45
	#define TETRA_INVALID_TEXT_MODE_PARAM					TETRA_ERROR_BASE + 46
	#define TETRA_M_SYNTAX_ERROR								TETRA_ERROR_BASE + 47
	#define TETRA_DATA_WITHOUT_REQUEST						TETRA_ERROR_BASE + 48
	#define TETRA_DATA_TIMEOUT									TETRA_ERROR_BASE + 49
	#define TETRA_REGISTRATION_TIMEOUT						TETRA_ERROR_BASE + 50
	#define TETRA_DEREGISTRATION_TIMEOUT					TETRA_ERROR_BASE + 51
	#define TETRA_APPLICATION_REGISTERED					TETRA_ERROR_BASE + 52
	#define TETRA_REGISTRATION_TABLE_FULL					TETRA_ERROR_BASE + 53
	#define TETRA_REGISTRATION_DISABLED						TETRA_ERROR_BASE + 54
	#define TETRA_REGISTRATION_ILLEGAL						TETRA_ERROR_BASE + 55
	#define TETRA_DEREGISTRATION_NOT_POSSIBLE				TETRA_ERROR_BASE + 56
	#define TETRA_UNKNOWN_EERROR								TETRA_ERROR_BASE + 57


   //****************** FMS ERROR Section
	#define FMS_ERROR_BASE			                  	1500
   #define ERROR_FMS_ALREADY_INITIALIZED					FMS_ERROR_BASE + 1
	#define ERROR_FMS_NOT_INITIALIZED						FMS_ERROR_BASE + 2
	#define ERROR_FMS_ALREADY_STARTED						FMS_ERROR_BASE + 3
	#define ERROR_STARTING_FMS									FMS_ERROR_BASE + 4
	#define ERROR_FMS_CREATE_SOCKET							FMS_ERROR_BASE + 5
	#define ERROR_FMS_CFG_SOCKET								FMS_ERROR_BASE + 6
	#define ERROR_FMS_BIND_SOCKET								FMS_ERROR_BASE + 7
	#define ERROR_FMS_THREAD_INIT								FMS_ERROR_BASE + 8
	#define ERROR_FMS_NOT_STARTED								FMS_ERROR_BASE + 9
	#define ERROR_FMS_LOAD_LIBRARY							FMS_ERROR_BASE + 10
	#define ERROR_FMS_UNLOAD_LIBRARY							FMS_ERROR_BASE + 11
	#define ERROR_FMS_LOAD_FUNCTION							FMS_ERROR_BASE + 12
	#define ERROR_FMS_OPTION_NOT_ENABLED					FMS_ERROR_BASE + 13
	#define ERROR_FMS_ENABLE_CAN								FMS_ERROR_BASE + 14
	#define ERROR_FMS_GET_OPTION								FMS_ERROR_BASE + 15
	#define ERROR_FMS_TIRE_NOT_FOUND							FMS_ERROR_BASE + 16
	#define ERROR_FMS_SRV_CONF									FMS_ERROR_BASE + 17

#endif

