/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : IFsh10.H
**     Project   : _2_11_b
**     Processor : MC9S12GC32CFU16
**     Beantype  : IntFLASH
**     Version   : Bean 02.164, Driver 02.08, CPU db: 2.87.320
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 02/12/2005, 16:20
**     Abstract  :
**         This bean "IntFLASH" implements an access to internal FLASH.
**         The bean support reading/writing data into FLASH, erasing of 
**         selected sector.
**         The bean supports events if the write interrupt is supported.
**         The bean supports following modes of write operations:
**           - Write - writing without any test.
**           - Destructive write - sector is erased if necessary.
**           - Safe write - user event is invoked to save and resore data
**                          from the current sector.
**         The bean requires on-chip FLASH memory (not used/allocated by 
**         other beans).
**     Settings  :
**         Total FLASH memory size       : 32KB
**         Interrupt service             : Disabled
**         Write method                  : Safe write (with save & erase)
**         Buffer Type                   : Implemented by the bean
**         Wait in RAM                   : yes
**     Contents  :
**         SetWordFlash - byte IFsh10_SetWordFlash(dword Addr,word Data);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/
/* MODULE IFsh10. */


#ifndef __IFsh10
#define __IFsh10

/* MODULE IFsh10. */

#include "Cpu.h"

#pragma DATA_SEG IFsh10_DATA                                            
#pragma CODE_SEG IFsh10_CODE                     


#define IFsh10_DummyData   0x10        /* This number is used as data word for erase algorithm */


byte WriteWord(word Addr,word Data16);
byte WriteArray(word Addr,word From, word To, word* Array);
byte IFsh10_SetWordsArray(word Addr,word * Data,byte* Indice);
byte IFsh10_DeleteSector(word Addr,byte CantidadBytes);
byte EraseSectorInternal(word Addr);
byte IFsh10_Setbyte(word Addr,byte Data);
byte IFsh10_SetLong(word Addr,long Data);
/*
** ===================================================================
**     Method      :  IFsh10_SetWordFlash (bean IntFLASH)
**
**     Description :
**         Write word to address in FLASH.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Addr            - Address to FLASH.
**         Data            - Data to write.
**     Returns     :
**         ---             - Error code, possible codes:
**                           - ERR_OK - OK
**                           - ERR_NOTAVAIL - Desired program/erase
**                           operation is not available
**                           - ERR_RANGE - Address is out of range
**                           - ERR_VALUE - Read value is not equal to
**                           written value
**                           - ERR_SPEED - This device does not work
**                           in the active speed mode
**                           - ERR_BUSY - Device is busy
** ===================================================================
*/

#pragma CODE_SEG DEFAULT                                   

/* END IFsh10. */

#endif /* ifndef __IFsh10 */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
