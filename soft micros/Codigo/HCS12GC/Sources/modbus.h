#ifndef _MODBUS_H
#define _MODBUS_H

#include "AS1.h"

#pragma DATA_SEG ModBus_DATA                                            
#pragma CODE_SEG ModBus_CODE 
#pragma CONST_SEG DEFAULT

/*										 
** ===================================================================
**     Function    : Comu_Init 
**     Description :
**         Inicialización de la comunicación
** ===================================================================
*/
void Comu_Init(void);

void ModBus_Recive(AS1_TComData dat);

void ModBus_OnSend(void);

void setOnSend(void (*pf)(void));
/*
** ===================================================================
**     Method      :  ModBus_Send
**
**     Description :
**         llamar a esta función para enviar un mensaje por el puerto 
**     serie
** ===================================================================
*/
byte ModBus_Send(byte * data,byte cant);

/*
** ===================================================================
**     Event       :  AS1_OnRxChar (module Events)
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
void AS1_OnRxChar(void);

/*
** ===================================================================
**     Event       :  AS1_OnTxComplete (module Events)
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
void AS1_OnTxComplete(void);


//  FUNCIONES SET GET
/*  Id  */
int get_Id(void*);
byte set_Id(void*, int);
int get_LimSup_Id(void*a);


#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 
#pragma CONST_SEG DEFAULT

#endif