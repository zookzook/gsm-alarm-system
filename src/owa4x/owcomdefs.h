//*********************************************************************
//*************  Copyright (C) 2002        OWASYS  ********************
//*********************************************************************
//**
//** The copyright to the computer programs here in is the property of
//** OWASYS The programs may be used and/or copied only with the
//** written permission from OWASYS or in accordance with the terms and
//** conditions stipulated in the agreement/contract under which the
//** programs have been supplied.
//**
//*********************************************************************
//******************** Module information *****************************
//**
//** Project:       GSM_Module (CYA 000 0007)
//** Description:   Libreria API de modulo GSM
//**
//** Filename:      $FILENAME$
//** Owner:         $OWNER$
//** Creation date:  13/12/2002
//**
//*********************************************************************
//******************** Revision history *******************************
//** Revision date       Comments                           Responsible
//** -------- ---------- ---------------------------------- -----------
//** P1A       13/12/2002 First release                      $OWNER$
//*********************************************************************

#ifndef __OWCOMDEFS_H

   #define __OWCOMDEFS_H

/******************************************************************************/
/*                                                                         	*/
/*	1.	Values of a specific size                                          	 	*/
/*                                                                          	*/
/*		These should be used when an exact number of bits is required.        	*/
/*                                                                          	*/
/*		A very good example is in structures for messages between different   	*/
/*		computers (i.e., compilers).                                          	*/
/*                                                                          	*/
/*		NOTE:	You will still need to deal with big endian / small endian!     	*/
/*                                                                          	*/
/******************************************************************************/
/*                                                                          	*/
/*	INT32		:	signed value exactly 32 bits long.                           	*/
/*                                                                          	*/
/*	UINT32	:	unsigned value exactly 32 bits long.                         	*/
/*                                                                          	*/
/*	BOOL32	:	a TRUE/FALSE value exactly 32 bits long.                     	*/
/*                                                                          	*/
/*	INT16		:	signed value exactly 16 bits long.                           	*/
/*                                                                          	*/
/*	UINT16	:	unsigned value exactly 16 bits long.                         	*/
/*                                                                          	*/
/*	BOOL16	:	a TRUE/FALSE value exactly 16 bits long.                     	*/
/*                                                                          	*/
/******************************************************************************/


/******************************************************************************/
/*                                                                          	*/
/*	2.	Values of a non-specific (or at least not-too-specific size)       	 	*/
/*                                                                          	*/
/*		These should be used when an exact number of bits is not important,   	*/
/*		although some minimum number of bits may be required.                	*/
/*                                                                          	*/
/*		An example is local (stack) variables, such as an index counter       	*/
/*		like:		INT i;                                                       	*/
/*                                                                         	*/
/*		NOTE:	The types of choice are 'INT' and 'UINT'.  But remember,        	*/
/*				if you really need more than 16 bits, you should use LONG        	*/
/*				and ULONG!  If you are writing portable code, you can NOT depend  */
/*				on the size of int, although is is likely to be at least 16 bits.	*/
/*                                                                         	*/
/******************************************************************************/
/*                                                                          	*/
/*	LONG		:	signed value that is at least 32 bits long.                   	*/
/*                                                                          	*/
/*	ULONG		:	unsigned value that is at least 32 bits long.                 	*/
/*                                                                          	*/
/*	SHORT		:	signed value that is at least 16 bits long.                   	*/
/*                                                                          	*/
/*	USHORT	:	unsigned value that is at least 16 bits long.                 	*/
/*                                                                         	*/
/*	INT		:	signed value at least 16 bits long.  Can be longer and         */
/*					should be defined as the 'natural size' of integers used       */
/*					by the compiler.  This will make it at least as large as       */
/*					a SHORT and no larger than a LONG.                             */
/*                                                                          	*/
/*	UINT		:	unsigned value at least 16 bits long.  Can be longer and      	*/
/*					should be defined as the 'natural size' of integers used       */
/*					by the compiler. This will make it at least as large as a      */
/*					USHORT and no larger than a ULONG.                             */
/*                                                                          	*/
/******************************************************************************/


/******************************************************************************/
/*                                                                          	*/
/*	3.	More values of a specific size                                      	 	*/
/*                                                                          	*/
/*		These are a kind of special case, and may be used either commonly     	*/
/*		or in structures passed between different compilers.                  	*/
/*                                                                          	*/
/******************************************************************************/
/*                                                                         	*/
/*	CHAR		:	value that holds the 'natural size' of a character on         	*/
/*					the compiler being used.  This typedef should be used when     */
/*					working with character data only, and shouldn't be             */
/*					considered ALWAYS to be an 8-bit value.  Text strings,         */
/*					user input, and other 'all text, always' data should use       */
/*					this typedef.  Numeric 8-bit values that are promoted and      */
/*					used as characters should be defined with TINY or UTINY.       */
/*                                                                          	*/
/*	BYTE		:	unsigned value that is exactly 8 bits long (0 to 255).        	*/
/*                                                                          	*/
/*	UBYTE		:	unsigned value that is exactly 8 bits long (0 to 255).         */
/*                                                                          	*/
/*				NOTE: Yes, the above two types are BOTH unsigned!  This is to be  */
/*						compatible with:                                            */
/*							(a) current SiRF usage (UBYTE), and                      */
/*							(b) traditional Microsoft usage (BYTE) for               */
/*						8-bit unsigned values.                                      */
/*						If you want to do 8-bit arithmetic, use TINY and UTINY.     */
/*                                                                          	*/
/*	TINY		:	signed value that is exactly 8 bits long (-128 to +127).       */
/*                                                                         	*/
/*	UTINY		:	unsigned value that is exactly 8 bits long (0 to 255).         */
/*                                                                          	*/
/*	VOID		:	refers to an object of unknown size.  For data, this is,       */
/*					by convention, assumed to be 0 bytes long.                     */
/*                                                                          	*/
/******************************************************************************/


/******************************************************************************/
/*                                                                          	*/
/*	4.	Floating point Types                                                		*/
/*                                                                          	*/
/*		These are a specific number of bytes long for two reasons.            	*/
/*		First, memory and disk storage space may be controlled.               	*/
/*		Second, processing time may be controlled (particularly useful        	*/
/*		for emulation software).                                              	*/
/*                                                                          	*/
/*		NOTE: On many computers, such as Intel with floating point            	*/
/*				processors, it is essentially the same processing time to         */
/*				use 64-bit double as 32-bit float since all calculations are      */
/*				done in 80-bit registers.  In fact, it takes a tiny bit longer    */
/*				for float, since it must first be converted to double.            */
/*                                                                         	*/
/*		NOTE:	You will still need to deal with big endian / small endian!     	*/
/*                                                                          	*/
/*		NOTE: Dangerous to put in structures shared between different         	*/
/*				computers (compilers), because the format of the 32 or 64 bits    */
/*				may be a bit different.                                           */
/*                                                                          	*/
/******************************************************************************/
/*                                                                          	*/
/*	FLOAT		:	signed floating point value exactly 32 bits long.              */
/*                                                                          	*/
/*	DOUBLE	:	signed floating point value exactly 64 bits long.              */
/*                                                                          	*/
/******************************************************************************/


/******************************************************************************/
/*                                                                          	*/
/*	5.	Derived Types                                                       		*/
/*                                                                          	*/
/*		These should be used when an exact number of bits is not important,   	*/
/*		although some minimum number of bits may be required.                 	*/
/*                                                                          	*/
/*		An example is procedure return types.                                 	*/
/*                                                                          	*/
/******************************************************************************/
/*                                                                          	*/
/*	BOOL		:	a TRUE/FALSE value.  Could be as small as 1 bit, if the       	*/
/*					compiler can support it.  Normally, since one tends not to     */
/*					have a zillion of these and thus speed is more important,      */
/*					it's defined as the natural integer size.                      */
/*                                                                          	*/
/*				BOOL fVarName;						|                                   */
/*														|                                   */
/*				fVarName = i < j;					|                                   */
/*														|                                   */
/*				if(fVarName)						|	<- Good                          */
/*					...								|                                   */
/*														|                                   */
/*				if(!fVarName)						|                                   */
/*					...								|                                   */
/*                                                                            */
/*				if(fVarName == TRUE)				|                                   */
/*					...								|                                   */
/*														|                                   */
/*				if(fVarName != TRUE)				|                                   */
/*					...								|                                   */
/*														|	<- Bad                           */
/*				if(fVarName == FALSE)			|                                   */
/*					...								|                                   */
/*														|                                   */
/*				if(fVarName != FALSE)			|                                   */
/*					...								|                                   */
/*                                                                          	*/
/*	WERR		:	SUCCESS / FAILURE.  Make understanding function return values 	*/
/*					(in the source code) much easier than TRUE / FALSE or 0 / 1.   */
/*                                                                          	*/
/*				WERR ProcName(INT iVal)			|                                   */
/*				{										|                                   */
/*					if(iVal < LIMIT)				|                                   */
/*						return SUCCESS;			|                                   */
/*					else								|                                   */
/*						return FAILURE;			|                                   */
/*				}										|	<- Good                          */
/*														|                                   */
/*				if(ProcName(i) == SUCCESS)		|                                   */
/*					...								|                                   */
/*														|                                   */
/*				if(ProcName(i) != SUCCESS)		|                                   */
/*					...								|                                   */
/*                                                                          	*/
/*				if(ProcName(i) == FAILURE)		|                                   */
/*					...								|                                   */
/*														|	<- Bad                           */
/*				if(ProcName(i) != FAILURE)		|                                   */
/*					...								|                                   */
/*                                                                          	*/
/*			Don't test for FAILURE explicitly because actually any other         */
/*			non-zero values may be returned as 'failure' (i.e., not              */
/*			SUCCESS.  For example, error codes 1, 2, 3 ...                       */
/*                                                                          	*/
/******************************************************************************/


/*****************************************/
/***	ARM compiler for ARM7TM (32-bit)	 **/
/*****************************************/
#if 0
   #ifdef __OWASYS_ARM

      typedef long int					INT32;	
      typedef unsigned long int		UINT32;	
      typedef long int					BOOL32;	
      typedef short int					INT16;	
      typedef unsigned short int		UINT16;	
      typedef short int					BOOL16;	
      typedef unsigned char         UCHAR;

      #define REGISTER  	register		

      #define PACKSTRUCT	__packed

      #define memclr(what, size) 	memset(what, 0, size)

      #define CAST_TO_UINT32(x)    (INT32)(fmod( x, (double)MAX_INT32))

   #else
      typedef long int              INT32;	
      typedef unsigned long int     UINT32;
      typedef long int              BOOL32;
      typedef short int             INT16;
      typedef unsigned short int    UINT16;
      typedef short int             BOOL16;
   #endif
//*******************************************
//**		Compiler-independent typedefs	    **
//*******************************************

   typedef long                     LONG;
   typedef unsigned long      	   ULONG;
   typedef short int          	   SHORT;
   typedef unsigned short int 	   USHORT;
   typedef int                	   INT;
   typedef unsigned int       	   UINT;

   typedef char               	   CHAR;
   typedef unsigned char      	   BYTE;
   typedef unsigned char      	   UBYTE;
   typedef signed char        	   TINY;
   typedef unsigned char      	   UTINY;
   #define VOID               	   void
   typedef unsigned char            UCHAR;

   typedef float              	   FLOAT;
   typedef double             	   DOUBLE;

   typedef int                	   WERR;

   typedef unsigned short           WORD;
   typedef unsigned long            DWORD;

   typedef int                	   BOOL;
#endif
/*******************************************/
/**		Compiler-independent defines		**/
/*******************************************/

   #ifndef NULL
      #define NULL					0
   #endif

   #ifndef EOF
      #define EOF						(-1)
   #endif

   #ifndef FALSE
      #define FALSE					0
   #endif

   #ifndef TRUE
      #define TRUE					(!FALSE)
   #endif

   #define  DISABLE            0
   #define  ENABLE             1

/****************************************/
/** 	Compiler-independent macros      **/
/****************************************/

   #define ABS(a)			(((a) < 0) ? (-(a)) : (a))

   #define SIGN(a,b)		(((b) <   0) ? (-ABS(a)) : (ABS(a)))

   #ifndef MIN
      #define MIN(a,b)		(((a) < (b)) ? (a) : (b))
   #endif

   #ifndef MAX
      #define MAX(a,b)		(((a) > (b)) ? (a) : (b))
   #endif

   #define MINMAX(a,b,c) MAX(MIN((a),(c)),(b))	/* (((a) < (b)) ? (b) : (((a) > (c)) ? (c) : (a))) */

#endif
