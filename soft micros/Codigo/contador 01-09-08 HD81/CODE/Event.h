/** ###################################################################
**     Filename  : Event.H
**     Project   : contador_12_06_06
**     Processor : MC9S12GC16CFU16
**     Beantype  : Events
**     Version   : Driver 01.03
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 01/09/2008, 11:31 a.m.
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         AS1_OnRxChar     - void AS1_OnRxChar(void);
**         AS1_OnTxComplete - void AS1_OnTxComplete(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef __Event_H
#define __Event_H
/* MODULE Event */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Display1.h"
#include "Display2.h"
#include "DL2.h"
#include "bits5ULN.h"
#include "vx1.h"
#include "vx2.h"
#include "trx.h"
#include "PTSL.h"
#include "PWSN.h"
#include "PUL.h"
#include "AS1.h"
#include "FLASH1.h"
#include "TI2.h"
#include "TI1.h"
#include "Rele1.h"
#include "Rele2.h"
#include "Reset.h"
#include "PP4.h"
#include "PP3.h"
#include "FreeCounter.h"

void AS1_OnRxChar(void);
/*
** ===================================================================
**     Event       :  AS1_OnRxChar (module Event)
**
**     From bean   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is
**         received. 
**         DMA mode:
**         If DMA controller is available on the selected CPU and
**         the receiver is configured to use DMA controller then
**         this event is disabled. Only OnFullRxBuf method can be
**         used in DMA mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void AS1_OnTxComplete(void);
/*
** ===================================================================
**     Event       :  AS1_OnTxComplete (module Event)
**
**     From bean   :  AS1 [AsynchroSerial]
**     Description :
**         This event indicates that the transmitter is finished
**         transmitting all data, preamble, and break characters and
**         is idle. It can be used to determine when it is safe to
**         switch a line driver (e.g. in RS-485 applications). This
**         event is available only if property <Transmitter > is
**         enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/


/* END Event */
#endif /* __Event_H*/

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95.01 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
