/** ###################################################################
**     Filename  : Flash.h
**     Date/Time : 14/01/2010, 16:20
**     Abstract  :
**         This module implements an access to internal FLASH.
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
**         Interrupt service             : Disabled
**         Write method                  : Safe write (with save & erase)
**         Buffer Type                   : Implemented by sucesors
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
#ifndef _FLASH_H
#define _FLASH_H



#include "PE/include/PE_Types.h"

#pragma DATA_SEG IFsh10_DATA                                            
#pragma CODE_SEG IFsh10_CODE                     

void Flash_init(void);
byte Flash_writeWord(word *address,word data16);
byte Flash_grabarFlash(void* pageAddr, word* array);
byte Flash_eraseSector(void * address);
void * Flash_getPage(void * address);
bool Flash_isInPage(void * address,void* pagina);


#pragma CODE_SEG DEFAULT   
#pragma DATA_SEG DEFAULT                                 

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
