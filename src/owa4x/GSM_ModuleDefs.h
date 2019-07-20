/**
 * @file GSM_ModuleDefs.h
 * @author Owasys
 * @date 03 Aug 2017
 * @brief File containing definitions for Owasys GSM API.
 *
 */

#ifndef __GSM_MODULEDEFS_H

   #define __GSM_MODULEDEFS_H

   #include <owa4x/owcomdefs.h>
   #include <owa4x/owerrors.h>

   //Call Control Section
   #define CALL_TYPE_VOICE    1
   #define CALL_TYPE_USSD     2
   #define CALL_TYPE_DATA     3
   #define CALL_TYPE_GPRS     4
   #define CALL_TYPE_SOS      5

   //SMS Section
   #define MAX_BODY_SIZE      160
   #define MAX_PHONE_SIZE     20

   #define REC_UNREAD         0
   #define REC_READ           1
   #define STO_UNSENT         2
   #define STO_SENT           3

   typedef struct _DATETIME{
      unsigned char   year;
      unsigned char   month;
      unsigned char   day;
      unsigned char   hour;
      unsigned char   minute;
      unsigned char   second;
      unsigned char   timeZone;
   }DATETIME;

   typedef struct _SMS_t{  //SMS Text type.
      unsigned char owIndex;
      unsigned char owBody[MAX_BODY_SIZE + 1];
      unsigned char owBodySize;
      unsigned char owSMSType;
      unsigned char owSA_DA[ MAX_PHONE_SIZE];
      DATETIME      owSCDateTime;
   }SMS_s;

	typedef struct _SMSExtended_t{  //SMS Text type.
      unsigned int  owIndex;
      unsigned char owBody[MAX_BODY_SIZE + 1];
      unsigned char owBodySize;
      unsigned char owSMSType;
      unsigned char owSA_DA[ MAX_PHONE_SIZE];
      DATETIME      owSCDateTime;
   }SMSExtended_s;
   //PhoneBook
   #define PB_SIM          1
   #define PB_ME           2
   #define PB_REC_CALLS    3
   #define PB_MIS_CALLS    4
   #define PB_LAST_CALLS   5
   #define PB_OWN_NUMBERS  6
   #define PB_FIXED_NUMS   7
   #define PB_SERVICE_NUM  8

   #define PB_INIT_AT_RESET      0
   #define PB_NO_INIT_AT_RESET   1

   //OWN NUMBERS
   #define OWN_VOICE       1
   #define OWN_FAX         2
   #define OWN_DATA        3
   
   #define MAX_NAME_SIZE   20
   #define MAX_PHONE_SIZE  20
   
   typedef struct _GSM_PhoneBook_t{
      unsigned char  owFolder;
      unsigned short owPos;
      unsigned char  owPhone[ MAX_PHONE_SIZE];
      unsigned char  owName [ MAX_NAME_SIZE];
   }GSM_PhoneBook_t;

   //Call Information
   typedef struct _GSM_CallEntry_t{
      unsigned char owPos;
      unsigned char owPhone[ 20];
      DATETIME      owCallDate;
   }GSM_CallEntry_t;

   typedef unsigned char* Phone_t;
   //GSM Services
   //RESTRICTED CALLS - TO EXPORT
   #define  ALL_OUT           1
   #define  ALL_INOUT         2
   #define  ALL_INOUT_ABROAD  3
   #define  ALL_IN            4
   #define  IN_ABROAD         5
   #define  ALL_CALLS         6     //Only for Deactivation
   //DIVERT CALLS --> TO EXPORT
      //Type
   #define  DV_ALL                  0
   #define  DV_BUSY                 1
   #define  DV_NO_REPLY             2
   #define  DV_NO_REACHABLE         3
   #define  DV_ALL_FORWARD          4  //(includes 0,1,2 and 3)
   #define  DV_ALL_COND_FORWARD     5  //(includes 1,2 and 3)
   //Classes
   //class> is a sum of integers each representing a class of information
   //(default 7=voice&data&fax):
   #define  CLASS_VOICE             1
   #define  CLASS_DATA              2
   #define  CLASS_FAX               4
   #define  CLASS_SMS               8
   #define  CLASS_DATA_SYNC        16
   #define  CLASS_DATA_ASYNC       32

   typedef struct _GSM_DivertCall_t{
      unsigned char owStatus;
      unsigned char owPhone[ 20];
   }GSM_DivertCall_t;
   //Operators
   //Deprecated structure. Don't use it! GSM_OperatorExtended_t instead.
   typedef struct _GSM_Operator_t{
      unsigned char  owStatus;        //Status of the Operator within GSM terminal
      unsigned char  owOperName[ 20]; //Operator Name
      unsigned short owPLMN;          //Operator Identification MCC+MNC -> PLMN  
   }GSM_Operator_t;

   typedef struct _GSM_OperatorExtended_t{
      unsigned char owStatus;        //Status of the Operator within GSM terminal
      unsigned char owOperName[ 20]; //Operator Name
      unsigned long owPLMN;          //Operator Identification MCC+MNC -> PLMN
   }GSM_OperatorExtended_t;

   typedef struct _GSM_Operator3G_t{
      unsigned char owStatus;        //Status of the Operator within GSM terminal
      unsigned char owOperName[ 20]; //Operator Name
      unsigned long owPLMN;          //Operator Identification MCC+MNC -> PLMN
      unsigned char owNetwork;       //Radio Access Technology (RAT)
   }GSM_Operator3G_t;

   //owStatus Possible Values
   #define  OP_UNKNOWN              0
   #define  OP_AVAILABLE            1
   #define  OP_CURRENT              2
   #define  OP_FORBIDDEN            3
   //OPERATOR Selection:
   #define  OP_AUTOSEL              0
   #define  OP_MANUALSEL            1 //Tries to make a Manual Net Selection,
                                      //if fails remains automatic.
   #define  OP_ONLYMANUAL           2 //Tries to make a Manual Net Selection,
	//Radio Access Technology(RAT)
	#define  RAT_GSM                 0   //GSM
	#define  RAT_DEFAULT             1   //Default
	#define  RAT_UMTS                2   //UMTS
	#define  RAT_GSM_EGPRS           3   //GSM w/EGPRS (only read value)
	#define  RAT_UMTS_HSDPA          4   //UMTS w/HSDPA (only read value)
	#define  RAT_UMTS_HSDPA_HSUPA    6   //UMTS w/HSDPA and HSUPA (only read value)
	#define  RAT_E_UMTS              7   //E-UMTS

   //Cell Position
   typedef struct _GSM_Cell_t{
      unsigned short owLac;         //GSM Location Area
      unsigned short owCellId;      //GSM Cell ID
   }GSM_Cell_t;        

   typedef struct _GSM_CellExtended_t{
      int     owLac;         //GSM Location Area
      int     owCellId;      //GSM Cell ID
   }GSM_CellExtended_t;        
   //Events Section

   typedef enum _gsmEvent_e{
      GSM_NO_SIGNAL = 0,
      GSM_RING_VOICE,
      GSM_RING_DATA,
      GSM_NEW_SMS,
      GSM_CALL_RELEASED,
      GSM_RECEIVED_DATA,
      GSM_FAILURE,
      GSM_COVERAGE,
      GSM_HIGHER_TEMP,
      GSM_STOP_SENDING_DATA,
      GSM_START_SENDING_DATA,
      GSM_CALL_WAITING,
      GSM_USSD_INFO,
      GSM_USSD_ERROR,
      GSM_USSD_REPLY,
//      GSM_AOC,
//      GSM_SS_INDICATION,
      GSM_CONNECTED_LINE,
      GSM_GPRS_COVERAGE,
      GSM_RING_END,
      GSM_MEM_SMS_FULL,
      GSM_MEM_SMS_AVAI,
      GSM_BOARD_TEMP,
		GSM_POSSIBLE_JAMMING,
		GSM_JAMMING_INDICATION,
		GSM_SMS_SENT_INDEX,
		GSM_SMS_DELIVER_REPORT
   }gsmEvent_e;
   //COVERAGE DEFINITIONS
   #define NO_NETWORK            0
   #define REGISTERED            1
   #define REGISTER_BUT_ROAMING  2
   #define SOS_ONLY              3
   #define NETWORK_SEARCH        4

   #define GPRS_NO_NETWORK       0
   #define GPRS_REGISTERED       1
   #define GPRS_SEARCHING        2
   #define GPRS_REGISTERED_ROAM  5


   //EVENT BUFFER
   #define EVENTS_BUFFER_SIZE    1024

   typedef struct _gsmEvents_s{
      gsmEvent_e  gsmEventType;
      char        evBuffer[ EVENTS_BUFFER_SIZE];
      int         evHandled;
   }gsmEvents_s;

   typedef struct _TGSM_MODULE_CONFIGURATION{
      unsigned char wCode    [ 9];
      unsigned char wMECode  [ 9];
      void  (*gsm_action)( gsmEvents_s * );
   }TGSM_MODULE_CONFIGURATION;

   typedef struct _GSM_CurrentCall_t{
      unsigned char owPhone     [ MAX_PHONE_SIZE];
      unsigned char owAlphaTag  [ MAX_PHONE_SIZE];
      unsigned char  owCallDir;
      unsigned char  owCallIndex;
      unsigned char  owCallStatus;
      unsigned char  owCallClass;
      unsigned char  owMpty;
      unsigned char  owType;
   }GSM_CurrentCall_t;

   //Miscellaneous
   #define CALL_ON_VOICE      0
   #define CALL_ON_CALL       1 
   #define CALL_ON_GPRS       2

/**
 * @brief Configures the GSM library module to work. 
 * 
 * After initializing library module, function GSM_Start must be called which in fact
 * switch ON the GSM module and initializes it. 
 *
 * @param *wConfiguration Pointer to configuration data to start GSM API
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_Initialize( void *wConfiguration);

/**
 * @brief Switches OFF the GSM module and ends all GSM communication
 *
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_Finalize( void);

/**
 * @brief Checks if the GSM module is switched ON and active. 
 *
 * @param *wActive 0: Not active, 1: Active.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_IsActive( int *wActive);

/**
 * @brief Initialization of the GSM terminal.
 *
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_Start( void);

/**
 * @brief Return the GSM library version. 
 *
 * @param *wVersion Contains the returned version code. Format "CYA 999 9999, x.x.x"
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_GetVersion( unsigned char *wVersion);

/**
 * @brief Sends an AT Command to the internal GSM module.
 *
 * @param *gsmCommand Command to be sent, exactly as it should be written to the GSM module.
 *    After returning from the function, gsmCommand will contain the answer (if any)
 *    returned from the GSM module.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SendCommand( char* gsmCommand);

/**
 * @brief Send Data (CSD) from wBuffer string to the GSM module. 
 *
 * @param *wBuffer Buffer where the data to send is stored
 * @param wSize Size of the buffer to send.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SendData( unsigned char* wBuffer, int wSize);
   
/**
 * @brief Return received data (CSD). 
 * 
 * wBuffer is string whose size is wSize. The returning value is the amount of data
 * on wBuffer, maximum wSize.
 *
 * @param *wBuffer Buffer to write the Received Data. NULL if no data available
 * @param wSize Size of the buffer to write the received data. wSize should be kept 
 *    bigger than the number of bytes of data received so that the limit was the 
 *    amount of received bytes.
 * @return NO_ERROR or Number of Bytes on wBuffer.
 */
   int GSM_ReceiveData( unsigned char* wBuffer, int wSize);

/**
 * @brief This function should be used to initiate a call. 
 * 
 * Parameter sets the type of call (Voice, Data, USSD) and called number (B-party) 
 * either directly or "call from SIM" mode. 
 *
 * @param wType Type of call to perform. 1: CALL_TYPE_VOICE, 2: CALL_TYPE_USSD, 3: CALL_TYPE_DATA
 * @param *wBuffer Number to call to (B-party number). Minimum 3 digits.
 *    If number has 2 digits it is interpreted as a CALL FROM SIM, being the wBuffer the index,
 *    referred to the SIM storage.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_Dial( char wType, unsigned char* wBuffer);

/**
 * @brief Hang up the current Call
 *
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_HangUp( void );

/**
 * @brief Answer to an incoming call
 *
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_AnswerCall( void );

/**
 * @brief Adjust the speaker loudness of the received GSM audio.
 *
 * @param wSense Sound loudness in % of full volume. 0% will be minimum volume and 100% maximum volume.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SetVolume( unsigned char wSense);

/**
 * @brief Adjust the speaker loudness of the incoming call RING tone.
 * 
 * Not implemented
 *
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SetRingVolume( unsigned char wTone, unsigned char wVolume);

/**
 * @brief Adjust the microphone audio gain in a voice call.
 *
 * Not implemented
 * 
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SetTxGain( unsigned char wGain, unsigned int wAtten);

/**
 * @brief Mute/UnMute the microphone
 *
 * @param wMute 0: Disable Microphone Mute, 1: Enable Microphone Mute

 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SetMicroMute( unsigned char wMute);

/**
 * @brief Sends a DTMF tone to the peer side through the GSM network. 
 * 
 * According to the GSM standard this is transmitted as a message and played by the
 * interconnection of the PLMN and other network. ( i.e. another PLMN, PSTN…. ) 
 *
 * @param wTone DTMF to be sent to the peer side. These values could be *, # and 0-9
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_PlayDTMF( unsigned char wTone);

/**
 * @brief Enable GSM coverage unsolicited code.
 * 
 * If enabled the GSM library can send corresponding events. 
 *
 * @param wRegistration 0: DISABLE, 1: ENABLE
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_ActivateRegistration( char wRegistration);

/**
 * @brief Return the Strength of the GSM signal to which the GSM is locked. 
 * 
 * Please note that the GSM signal received may not be that of the "HOME" network
 * provider. As a GSM mobile station should be always able to place an emergency call,
 * is still posible to "see" a strong GSM signal strenght in case of no coverage from
 * the current provider, or even no SIM inserted. To determine which is the case use 
 * also function GSM_GetRegistration()
 *
 * @param *wSignalStrength Stores the received Signal Strength value. 
 *    Lower values (<12 means a weak signal)
 *    0: <= -113 dBm,
 *    1: -111 dBm,
 *    2...30: -109...-53dBm,
 *    ....
 *    31: >= -51 dBm,
 *    99: Unknown.
 *   Good values are those greater than 8 to start a Data call, although it is 
 *   recommended 12 value.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_GetSignalStrength( unsigned char* wSignalStrength);

/**
 * @brief Return the quality of the GSM signal, giving the BER.
 *
 * As in the case of GSM_GetSignalStrength() it should be noted that the GSM signal
 * received may not be that of the "HOME" network provider. As a GSM mobile station
 * should be always able to place an emergency call, is still posible to "see" a
 * strong GSM signal strenght in case of no coverage from the current provider,
 * or even no SIM inserted. To determine which is the case use also function
 * GSM_GetRegistration()
 *
 * @param *wSignalQuality Stores the received Signal Quality value.
 *    0: No error
 *    1...7 - Lower values means less errors.
 *    99: Unknown
 *    0 is the normal value but it is possible to see greater values due to signal
 *    degradation, because of distance or other elements (rain,snow,fog, etc…)
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_GetSignalQuality( unsigned char* wSignalQuality);

/**
 * @brief Get GSM cell information
 * 
 * Each GSM network provider splits its coverage area into cells, each one having
 * a unique identifier or Cell Id Code (CellID). Besides this, the Location Area
 * Code (LAC) is used to keep track of the Mobile Station position, mainly for
 * "paging". The LAC may be as small as a cell, or may be a group of adjacent cells.
 * Thus, using this function it is possible to get a non-accurate position of the
 * GSM terminal. It could be also useful to check whether the GSM terminal is
 * moving between adjacent areas.
 *
 * @param *wCellPosition Received Cell identifier.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_GetCellPosition( GSM_Cell_t* wCellPosition);

/**
 * @brief Gets the current network status.
 *
 * @param *wRegistration Network Status:
 *    0 -> NO_NETWORK
 *    1 -> REGISTERED
 *    2 -> REGISTER_BUT_ROAMING
 *    3 -> SOS_ONLY
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_GetRegistration( char* wRegistration);

/**
 * @brief Control the attachment to the GPRS network
 *
 * @param wEnable 0: Unattach from GPRS 1: Attach to GPRS 
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_AttachGPRS( char wEnable);

/**
 * @brief Returns if the GSM mobile phone is registered on the GPRS network. 
 * 
 * Please note that the module does not attach to GPRS automatically during 
 * GSM initialization and this function will always return 0 until either attaching
 * explicitly with function GSM_AttachGPRS() or starting a iNet session.
 *
 * @param *wRegistration Registration status
 *    0: GPRS not registered
 *    1: GPRS Registered
 *    2: GPRS Searching
 *    3: GPRS Registration denied
 *    4: GPRS Registration Unknown
 *    5: GPRS Registered, but roaming
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_GetGPRSRegistration( unsigned char* wRegistration);

/**
 * @brief Return how the GSM terminal is locked to the network, if it searches 
 *    automatically an available network or it is locked to a specific PLMN 
 *
 * @param *wMode Mode that is currently used for the Network Selection Mode:
 *    0: OP_AUTOSEL --> Autometic Selection
 *    1: OP_ONLYMANUAL --> Manual Selection. 
 * @param *wOper  PLMN of the operator to which the GSM terminal is locked.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_GetNetworkSelectionModeExtended( unsigned char* wMode, unsigned long* wOper);

/**
 * @brief Return the GSM available network list in the air interface.
 *
 * This does not mean that all of them are available to operate with. 
 *
 * @param **wOperatorListInfo Array of the available operators. 
 * @param *wSize Size of wOperatorListInfo array
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_GetNetworksListExtended( GSM_OperatorExtended_t** wOperatorListInfo, unsigned char* wSize);

/**
 * @brief Set the way the GSM terminal is going to be locked to the network, automatically or manually, where a specific PLMN is needed. 
 *
 * @param wMode Mode of the desired Network Selection Mode:
 *    0: OP_AUTOSEL --> Automatic Selection
 *    1: OP_MANUALSEL --> Manual/Automatic Selection to the operator given
 *    in *wOper parameter. If selected operator not available it changes to 
 *    Automatic mode.
 *    2: OP_ONLYMANUAL --> Only manual Selection of the the operator given
 *    in *wOper parameter. If not available it will attach to no other operator.
 * @param wOper PLMN identification of the operator to which the GSM terminal
 *    shall be locked. This is only applicable if the wMode is OP_MANUALSEL
 *    or OP_ONLYMANUAL
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SetNetworkSelectionExtended( unsigned char wMode, unsigned long wOper);

/**
 * @brief Retrieve a contact in the PhoneBook. It will look up in the SIM PhoneBook. 
 *
 * @param *wBuffer Reserved buffer space to return the required contact from the SIM card. 
 * @param wPos Position of the entry to read, according to its storage in 
 *    the SIM or ME (Mobile Equipment) phonebook.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_FindContact( GSM_PhoneBook_t* wBuffer, unsigned short wPos);

/**
 * @brief Write or modifie an entry in the Phonebook. 
 *
 * @param wBuffer Contact information to write.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_WriteContact( GSM_PhoneBook_t wBuffer);

/**
 * @brief Deletes an entry from the specified folder storage. 
 *
 * @param wPos Position of the entry in the folder 
 * @param wPBStorage Folder. 0: SIM CARD, 1: ME (Mobile Equipment)
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_DeleteContact( unsigned short wPos, unsigned char wPBStorage);

/**
 * @brief Read the Mynumber info .
 *
 * @param *wBuffer Reserved space buffer to store Phonebook "MyNumber" info.
 * @param *wSize Size of the wBuffer (number of Bytes)
 * @param wNumberType Number to be read.1: OWN_VOICE, 2: OWN_FAX, 3: OWN_DATA
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_ReadMyNumber( unsigned char* wBuffer, unsigned char* wSize, unsigned char wNumberType);

/**
 * @brief Modifies Mynumber info in Phonebook
 *
 * @param *wBuffer Reserved space buffer to store Phonebook "Mynumber" info.
 * @param wNumberType Number to be changed.1: OWN_VOICE, 2: OWN_FAX, 3: OWN_DATA
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_ChangeMyNumber( unsigned char* wBuffer, unsigned char wNumberType);

/**
 * @brief Return the whole SIM phonebook where the wBuffer is an array of 
 *    GSM_PhoneBook_t structures. 
 *
 * @param **wBuffer Reserved space buffer for storing Phonebook entries, if exist.
 *    wBuffer is the first node for the list of phonebook entries if the wPos = 0,
 *    otherwise is the first and unique phonebook entry
 * @param *wSize Size, in PhoneBook nodes, of wBuffer. 
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_ReadSIMPhoneBook( GSM_PhoneBook_t** wBuffer, unsigned short* wSize);

/**
 * @brief Return the whole ME phonebook where the wBuffer is an array of 
 *    GSM_PhoneBook_t structures. 
 *
 * @param **wBuffer Reserved space buffer for storing Phonebook entries, if exist.
 *    wBuffer if the first node for the list of phonebook entries if the wPos = 0,
 *    otherwise is the first and unique phonebook entry
 * @param *wSize Size, in PhoneBook nodes, of wBuffer. 
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_ReadMEPhoneBook( GSM_PhoneBook_t** wBuffer, unsigned short* wSize);

/**
 * @brief Read one or all the Last Dialled calls. 
 * 
 * All of the calls will be ordered on an array of GSM_CallEntry_t structures. 
 *
 * @param **wBuffer Array of the CallEnty_t struct belonged to the Last Dialled Calls.
 *    The size of the array is given by *wSize.
 * @param *wSize Size, in number of CALL ENTRIES, of input buffer. 
 * @param wPos If 0, reads all Last Dialled calls and store in the wPos parameter.
 *    If != 0, reads the Last Dialled Call specified by wPos parameter.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_ReadLastDialledCall( GSM_CallEntry_t** wBuffer, unsigned char* wSize, unsigned char wPos);

/**
 * @brief Read one or all the Missed calls. 
 * 
 * All of the calls will be ordered on an array of GSM_CallEntry_t structures. 
 *
 * @param **wBuffer Array of the CallEnty_t struct belonged to the Missed Calls.
 *    The size of the array is given by *wSize.
 * @param *wSize Size, in number of CALL ENTRIES, of input buffer. 
 * @param wPos If 0, reads all Last Dialled calls and store in the wPos parameter.
 *    If != 0, reads the Missed Call specified by wPos parameter.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_ReadMissedCall( GSM_CallEntry_t** wBuffer, unsigned char* wSize, unsigned char wPos);

/**
 * @brief Read one or all the Received calls. 
 * 
 * All of the calls will be ordered on an array of GSM_CallEntry_t structures. 
 *
 * @param **wBuffer Array of the CallEnty_t struct belonged to the Received Calls.
 *    The size of the array is given by *wSize.
 * @param *wSize Size, in number of CALL ENTRIES, of input buffer. 
 * @param wPos If 0, reads all Last Dialled calls and store in the wPos parameter.
 *    If != 0, reads the Received Call specified by wPos parameter.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_ReadReceivedCall( GSM_CallEntry_t** wBuffer, unsigned char* wSize, unsigned char wPos);

/**
 * @brief Read all messages, or a specific one, from an specified folder.
 *
 * @param *wBuffer Reserved space buffer for storing messages, if exist.
 * @param *wSize Size of the SMS message body being read
 * @param wPos Position of the message to read. If 0, reads all of them.( Not yet Implemented )
 * @param wFolder Identifier of folder to read messages:
 *    0: SMS_REC_UNREAD
 *    1: SMS_REC_READ
 *    2: SMS_STO_UNSENT
 *    3: SMS_STO_SENT
 *    4: SMS_ALL 
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_ReadSMS( SMS_s* wBuffer, unsigned char* wSize, char wPos, char wFolder);

/**
 * @brief Read a message from a particular index position. 
 *
 * @param *wBuffer Reserved space buffer for storing messages, if exist. 
 * @param *wSize Size, in bytes, of input buffer. If not enough space, return
 *    necessary size in bytes. If enough space, indicates the size in bytes of
 *    returned wBuffer parameter. 
 * @param wPos Position of the message to read. 
 * @param wFolder Always 0. 
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_ReadSMSExtended( SMSExtended_s* wBuffer, unsigned char* wSize, int wPos, char wFolder);

/**
 * @brief Delete a message from the selected position.
 *
 * @param wPos Position of the message to delete. 
 * @param wFolder Always 0
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_DeleteSMS( char wPos, char wFolder );

/**
 * @brief Delete a message from the selected position.
 *
 * @param wPos Position of the message to delete. 
 * @param wFolder Always 0
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_DeleteSMSExtended( int wPos, char wFolder );

/**
 * @brief Send message to specified phone number. 
 *
 * @param *wBuffer Buffer with message body contents. This will be in ASCII Format. 
 * @param *wDestination Destination Phone number to send the SMS to. 
 * @param wIndex Index of the message to SEND:
 *    If wIndex != 0 this must be sent from storage.
 *    If 0, the SMS will be sent from the *wBuffer. 
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SendSMS( unsigned char* wBuffer,unsigned char* wDestination, char wIndex);

/**
 * @brief Send message to specified phone number. 
 *
 * @param *wBuffer Buffer with message body contents. This will be in ASCII Format. 
 * @param *wDestination Destination Phone number to send the SMS to. 
 * @param wIndex Index of the message to SEND:
 *    If wIndex != 0 this must be sent from storage.
 *    If 0, the SMS will be sent from the *wBuffer. 
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SendSMSExtended( unsigned char* wBuffer,unsigned char* wDestination, int wIndex);

/**
 * @brief Send message to specified phone number indicating the size of the message sent. 
 *
 * @param *wBuffer Buffer with message body contents. This will be in ASCII Format. 
 * @param wSize The size of the message, if it is less than 0 the size is calculated
 *    from the wBuffer size the same as it is done with function GSM_SendSMS. 
 * @param *wDestination Destination Phone number to send the SMS to. 
 * @param wIndex Index of the message to SEND:
 *    If wIndex != 0 this must be sent from storage.
 *    If 0, the SMS will be sent from the *wBuffer. 
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SendSMSBySize( unsigned char* wBuffer,int wSize,unsigned char* wDestination, char wIndex);

/**
 * @brief Send message to specified phone number indicating the size of the message sent. 
 *
 * @param *wBuffer Buffer with message body contents. This will be in ASCII Format. 
 * @param wSize The size of the message, if it is less than 0 the size is calculated
 *    from the wBuffer size the same as it is done with function GSM_SendSMS. 
 * @param *wDestination Destination Phone number to send the SMS to. 
 * @param wIndex Index of the message to SEND:
 *    If wIndex != 0 this must be sent from storage.
 *    If 0, the SMS will be sent from the *wBuffer. 
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SendSMSExtendedBySize( unsigned char* wBuffer,int wSize,unsigned char* wDestination, int wIndex);

/**
 * @brief Write a message to memory. 
 *
 * @param *wBuffer Buffer with message body contents. This will be in ASCII Format.
 * @param *wDestination Destination Phone number to send the SMS to once the message
 *    has been stored. 
 * @param *wIndex Index returned of the SMS stored position.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_WriteSMSToMemory( unsigned char* wBuffer,unsigned char* wDestination, unsigned char* wIndex );

/**
 * @brief Write a message to memory. 
 *
 * @param *wBuffer Buffer with message body contents. This will be in ASCII Format.
 * @param *wDestination Destination Phone number to send the SMS to once the message
 *    has been stored. 
 * @param *wIndex Index returned of the SMS stored position.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_WriteSMSToMemoryExtended( unsigned char* wBuffer,unsigned char* wDestination, int* wIndex );

/**
 * @brief Get the SMS Centre Address that it is equal to a phone number
 *
 * @param *wBuffer Reserved space buffer to store the Centre Address.
 * @param *wSize Size, in bytes, of input buffer. If not enough space, return 
 *    necessary size in bytes. If enough space, indicates the size in bytes of 
 *    returned wBuffer parameter.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_ReadSMSCentreAddress( unsigned char* wBuffer, unsigned char *wSize);

/**
 * @brief Write the SMS Center Address, which is equal to a phone number
 *
 * @param *wBuffer Buffer where the SMS Centre Address is configured.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_WriteSMSCentreAddress( unsigned char* wBuffer);

/**
 * @brief Enable/Disable the Automatic Reception of SMSs.
 *
 * It configures GSM to receive the GSM signal on happening an incoming SMS event.
 *
 * @param wStatus 0: Disable, 1: Enable
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SMSIndications( char wStatus);

/**
 * @brief Give the SMS storages capacity and the busy space.
 *
 * @param *wSMSBusy Memory occupied by stored SMSs.
 * @param *wSMSTotal TOTAL amount of memory reserved to store SMSs.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SMSStatus( int* wSMSBusy, int* wSMSTotal);

/**
 * @brief Read a SMS in PDU format.
 *
 * @param *wBuffer Reserved space buffer for message contents in PDU format. 
 * @param *wSize Size, in bytes, of input buffer. 
 * @param *wStatus SMS status. 0: REC_UNREAD, 1: REC_READ, 2: STO_UNSENT, 3: STO_SENT
 * @param wPos Position of message to read. This value must be > 0. 
 * @param wFolder Identifier of folder to read messages: This must be always 0. 
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_ReadPDUSMS( unsigned char *wBuffer, unsigned char *wSize, unsigned char *wStatus, unsigned char  wPos, unsigned char wFolder);

/**
 * @brief Read a SMS in PDU format.
 *
 * @param *wBuffer Reserved space buffer for message contents in PDU format. 
 * @param *wSize Size, in bytes, of input buffer. 
 * @param *wStatus SMS status. 0: REC_UNREAD, 1: REC_READ, 2: STO_UNSENT, 3: STO_SENT
 * @param wPos Position of message to read. This value must be > 0. 
 * @param wFolder Identifier of folder to read messages: This must be always 0. 
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_ReadPDUSMSExtended( unsigned char *wBuffer, unsigned char *wSize, unsigned char *wStatus, int  wPos, unsigned char wFolder);

/**
 * @brief end message in PDU format.
 *
 * Phone number, Service Centre, etc must be included within the Data
 *
 * @param *wBuffer Reserved space buffer for message body contents.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SendPDUSMS( unsigned char *wBuffer);

/**
 * @brief Send message to specified phone number indicating the size of the message sent.
 *
 * @param *wBuffer Reserved space buffer for message contents. 
 * @param *wIndex Index that will be returned where the SMS has been stored.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_WritePDUSMSToMemory( unsigned char *wBuffer, unsigned char *wIndex);

/**
 * @brief Send message to specified phone number indicating the size of the message sent.
 *
 * @param *wBuffer Reserved space buffer for message contents. 
 * @param *wIndex Index that will be returned where the SMS has been stored.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_WritePDUSMSToMemoryExtended( unsigned char *wBuffer, int *wIndex);

/**
 * @brief Enable/Disable the USSD notifications to the application.
 *
 * If the user wants to receive these notifications, the user must enable the
 * feature on starting GSM, as it is done with the SMSIndications.
 *
 * @param wStatus 0: DISABLE, 1: ENABLE --> Enables the USSD notification
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SetUSSD( unsigned char wStatus);

/**
 * @brief Used to reply to a USSD request from the network sid
 *
 * @param *wReply String that answers the network request.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_ReplyUSSD( unsigned char* wReply);

/**
 * @brief Get the date and time maintained in the GSM terminal.
 *
 * There is an independent RTC in the GSM terminal, so that it can maintain
 * the date and time even in switch OFF condition. (continuously running) 
 *
 * @param *wDateTime Date/Time stored at GSM module
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_GetDateTime( DATETIME* wDateTime);

/**
 * @brief Set the date and time in the GSM terminal.
 *
 * This is written to the independent RTC in the GSM terminal, so that it can 
 * maintain the date and time even in switch OFF condition. (continuously running) 
 *
 * @param *wDateTime Date/Time to store at GSM module
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SetDateTime( DATETIME* wDateTime);

/**
 * @brief This function will get the IMEI from the GSM module
 *
 * @param *wImei String which returns the IMEI of the GSM transceiver.
 * @param wSize Size of the wImei variable
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_GetIMEI( char* wImei, int wSize);

/**
 * @brief This function will get the IMSI from the GSM module
 *
 * @param *wImsi String which returns the IMSI of the GSM transceiver. 
 * @param wSize Size of the wImsi variable
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_GetIMSI ( char* wImsi, int wSize);

/**
 * @brief Get the audio model 
 *
 * @return Audio model. Sould be 4 (CINTERION)
 */
   int GSM_GetAudioModel( void);

/**
 * @brief Activate/Deactivate card security codes. (PIN Enables)
 *
 * @param *wCode Code buffer. 4-char for all of the codes but PUK, PUK2, which have 8-char size
 * @param wStatus 0: DISABLE,1: ENABLE
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_ActivateCardCodes( unsigned char* wCode, unsigned char wStatus);

/**
 * @brief Modifie the PIN security code
 *
 * @param *wOldCode Buffer with old PIN.
 * @param *wNewCode Buffer with new PIN.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_ModifyPINCode( unsigned char* wOldCode, unsigned char* wNewCode);

/**
 * @brief Activate/Deactivate phone security codes.
 *
 * @param *wCode Buffer with code for activation.
 * @param wStatus 0: DISABLE, 1: ENABLE
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_ActivatePhoneCodes( unsigned char* wCode, unsigned char wStatus);

/**
 * @brief Modifie the phone security code
 *
 * @param *wOldCode Buffer with old Code, if exist.
 * @param *wNewCode Buffer with new Code, if exist.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_ModifyPhoneCode( unsigned char* wOldCode, unsigned char* wNewCode);

/**
 * @brief Check if the SIM card is protected with the PIN code.
 *
 * @param *wStatus State of card PIN code returned by the GSM Library:
 *    0: DISABLE, 1: ENABLE
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_CheckPINProtection( unsigned char* wStatus);

/**
 * @brief Check if the Mobile Station is protected with the Phone code. 
 *
 * @param *wStatus State of card ME code returned by the GSM Library:
 *    0: DISABLE, 1: ENABLE
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_CheckPhoneProtection( unsigned char* wStatus);

/**
 * @brief Modify the Code of a facility within the GSM module.
 *
 * @param wFacility Possible Facility Numbers:
 *    1 - All Outgoing
 *    2 - All Outgoing international
 *    3 - All Outgoing international-ex Home PLM
 *    4 - All Incoming
 *    5 - All Incoming Abroad
 *    6 - All Barring Services
 *    7 - All Outgoing Barring
 *    8 - All Incoming Barring
 * @param *wOldCode Buffer with old PASSWORD. This value is 4 digits long.
 * @param *wNewCode Buffer with new PASSWORD. This value is 4 digits long.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_ModifyBarringCode( unsigned char wFacility, unsigned char* wOldCode, unsigned char* wNewCode);

/**
 * @brief Show or hide the own number at next call. 
 *
 * @param wShow 0: DISABLE. Show your number, 1: ENABLE. Hide your number. 
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_ShowNumberAtNextCall( unsigned char wShow);

/**
 * @brief Get if the Number is shown at the next call. 
 *
 * @param *wShow 0: DISABLE, 1: ENABLE
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_GetShowNumberAtNextCall( unsigned char *wShow);

/**
 * @brief Enable the divert for incoming call, depending on the type.
 *
 * This a GSM supplementary service. If an error occurs could be caused
 * by the GSM network.
 *
 * @param wType Type of call for diverting:
 *    0: DV_ALL
 *    1: DV_BUSY
 *    2: DV_NO_REPLY
 *    3: DV_NO_REACHABLE
 *    4: DV_ALL_FORWARD (includes 0,1,2 and 3)
 *    5: DV_ALL_COND_FORWARD (includes 1,2 and 3)
 * @param *wNumber Phone number to divert to.
 * @param wStatus 0:DISABLE, 1:ENABLE
 * @param wClass is a sum of integers each representing a class of information
 *    (default 7=voice&data&fax). 1:CLASS_VOICE, 2:CLASS_DATA, 4: CLASS_FAX 
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SetDivertCall( unsigned char wType, unsigned char* wNumber, unsigned char wStatus, unsigned char wClass);

/**
 * @brief Get the divert options for incoming call, depending on the type.( VOICE, DATA, FAX...) 
 * 
 * This a GSM supplementary service, so the network must support it and if an 
 * error occurs could be caused by the GSM network.
 *
 * @param **wDivert Struct Containing the Class and the status of this Divert Class
 *    and the number to Divert To. 
 * @param *wSize Size in GSM_DivertCall_t structs of the wDivert.
 * @param wReason Reason to retrieve the DivertCall information for it:
 *    0: DV_ALL
 *    1: DV_BUSY
 *    2: DV_NO_REPLY
 *    3: DV_NO_REACHABLE
 *    4: DV_ALL_FORWARD (includes 0,1,2 and 3)
 *    5: DV_ALL_COND_FORWARD (includes 1,2 and 3)
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_GetDivertCall( GSM_DivertCall_t** wDivert, unsigned char* wSize, unsigned char wReason);

/**
 * @brief Enable the type and status for restricted call type.
 *
 * @param wType Type of call to be barred:
 *    1: ALL_OUT : All Outgoing calls.
 *    2: ALL_INOUT : All Outgoing international.
 *    3: ALL_INOUT_ABROAD : All Outgoing international-except to Home Country (HPLM).
 *    4: ALL_IN: All incoming calls.
 *    5. IN_ABROAD : All incoming calls abroad.
 *    6. ALL_CALLS : All calls (only for deactivating).
 * @param wStatus 0: DISABLE, 1: ENABLE
 * @param *wPassword Password for restricting.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SetRestrictedCall( unsigned char wType, unsigned char wStatus, unsigned char* wPassword);

/**
 * @brief Get status for a specific restricted call type.( Outgoing calls, 
 *    Incoming calls, Incoming on abroad...)
 *
 * @param **wRestricted Array of Integer values, telling if the calls are restricted.
 *    Every position means: 0 VOICE, 1 DATA, 2 FAX
 * @param *wSize Size of the wRestricted Array.
 * @param wRestrictedType Type of call to be barred:
 *    0: ALL_OUT : All out calls.
 *    1: ALL_INOUT : All in and out calls.
 *    2: ALL_INOUT_ABROAD : All in and out calls abroad.
 *    3: ALL_IN: All incoming calls.
 *    4. IN_ABROAD : All incoming calls abroad.
 *    5. ALL_CALLS : All calls (only for deactivating).
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_GetRestrictedCall( int** wRestricted, unsigned char* wSize, unsigned char wRestrictedType);

/**
 * @brief Enable/Disables the waiting call Service in the GSM network.
 *
 * @param wStatus Enable/Disable the Waiting Call presentation. This means that the
 *    waiting call signal is sent to application. 0: DISABLE, 1: ENABLE
 * @param wMode Operation Mode for the Waiting call Service on the GSM network.
 *    0: DISABLE, 1: ENABLE
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SetWaitingCall( unsigned char wStatus, unsigned char wMode);

/**
 * @brief Get status for the waiting call Service
 *
 * @param *wStatus Get how the Waiting Call service is.0: DISABLE, 1: ENABLE
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_GetWaitingCall( unsigned char* wStatus);

/**
 * @brief Enable/Disable the Connected Line notifications to the application
 *
 * @param wStatus 0: DISABLE, 1: ENABLE --> Enables the COLP notification
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SetConnectedLinePresentation( unsigned char wStatus);

/**
 * @brief Enable/disable the jamming events. 
 *
 * @param wValue 0: No jamming events reported.1: Jamming events reported. 
 * @return NO_ERROR if success. Specific error number if fails.
 */
	int GSM_SetJamming( unsigned char wValue);

/**
 * @brief Get cell information.
 * 
 * Each GSM network provider splits its coverage area into cells, each one having
 * a unique identifier or Cell Id Code (CellID). Besides this, the Location Area
 * Code (LAC) is used to keep track of the Mobile Station position, mainly for
 * "paging". The LAC may be as small as a cell, or may be a group of adjacent cells.
 * Thus, using this function it is possible to get a non-accurate position of the GSM
 * terminal. It could be also useful to check whether the GSM terminal is moving
 * between adjacent areas. 
 *
 * @param *wCellPosition Stores the received Cell identifier. 
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_GetCellPositionExtended( GSM_CellExtended_t* wCellPosition);

/**
 * @brief Get the operator and the Radio Access Technology used by the GSM/UMTS module. 
 *
 * @param *wMode Mode that is currently used for the Network Selection Mode:
 *    0: OP_AUTOSEL --> Autometic Selection, 1: OP_ONLYMANUAL --> Manual Selection. 
 * @param *wOper PLMN identification of the operator to which the GSM terminal is currently locked.
 * @param *wNet Radio Access Technology(RAT)
 *    0: RAT_GSM --> GSM
 *    2: RAT_UMTS --> UMTS
 *    3: RAT_GSM_EGPRS --> GSM w/EGPRS (only read value)
 *    4: RAT_UMTS_HSDPA --> UMTS w/HSDPA (only read value)
 *    6: RAT_UMTS_HSDPA_HSUPA --> UMTS w/HSDPA and HSUPA
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_GetNetworkSelectionMode3G( unsigned char* wMode, unsigned long* wOper, unsigned char* wNet);

/**
 * @brief Set the way the GSM terminal is going to be locked to the network,
 *    automatically or manually, where a specific PLMN is needed. 
 *
 * @param wMode Mode of the desired Network Selection Mode:
 *    0: OP_AUTOSEL --> Automatic Selection
 *    1: OP_MANUALSEL --> Manual/Automatic Selection to the operator given in *wOper
 *     parameter. If selected operator not available it changes to Automatic mode.
 *    2: OP_ONLYMANUAL --> Only manual Selection of the the operator given in *wOper
 *    parameter. If not available it will attach to no other operator.
 * @param wOper PLMN identification of the operator to which the GSM terminal shall
 *    be locked. This is only applicable if the wMode is OP_MANUALSEL or OP_ONLYMANUAL 
 * @param wNet Radio Access Technology(RAT)
 *    0: RAT_GSM --> GSM
 *    2: RAT_UMTS --> UMTS
 *    3: RAT_GSM_EGPRS --> GSM w/EGPRS (only read value)
 *    4: RAT_UMTS_HSDPA --> UMTS w/HSDPA (only read value)
 *    6: RAT_UMTS_HSDPA_HSUPA --> UMTS w/HSDPA and HSUPA
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_SetNetworkSelection3G( unsigned char wMode, unsigned long wOper, unsigned char wNet);

/**
 * @brief Return the list of available operators after scanning for GSM/UMTS nets. 
 *
 * @param **wOperatorListInfo Array of the available operators. 
 * @param *wSize Size of wOperatorListInfo array 
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_GetNetworksList3G( GSM_Operator3G_t** wOperatorListInfo, unsigned char* wSize);

/**
 * @brief Set control path for GSM LED
 *
 * @param wMode 0: GSM module control, 1: user control.
 * @return NO_ERROR if success. Specific error number if fails.
 */
   int GSM_Set_Led_Mode( unsigned char wMode); 

#endif


