/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : AS1.C
**     Project   : cntr_26_07
**     Processor : MC9S12GC32CFU16
**     Beantype  : AsynchroSerial
**     Version   : Bean 02.433, Driver 01.17, CPU db: 2.87.392
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 23/09/2008, 10:04
**     Abstract  :
**         This bean "AsynchroSerial" implements an asynchronous serial
**         communication. The bean supports different settings of
**         parity, word width, stop-bit and communication speed,
**         user can select interrupt or polling handler.
**         Communication speed can be changed also in runtime.
**         The bean requires one on-chip asynchronous serial channel.
**     Settings  :
**         Serial channel              : SCI
**
**         Protocol
**             Init baud rate          : 9600baud
**             Width                   : 8 bits
**             Stop bits               : 1
**             Parity                  : none
**             Breaks                  : Disabled
**
**         Registers
**             Input buffer            : SCIDRL    [207]
**             Output buffer           : SCIDRL    [207]
**             Control register        : SCICR1    [202]
**             Mode register           : SCICR2    [203]
**             Baud setting reg.       : SCIBD     [200]
**             Special register        : SCISR1    [204]
**
**         Input interrupt
**             Vector name             : Vsci
**             Priority                : 1
**
**         Output interrupt
**             Vector name             : Vsci
**             Priority                : 1
**
**         Used pins:
**         ----------------------------------------------------------
**           Function | On package           |    Name
**         ----------------------------------------------------------
**            Input   |     63               |  PS0_RxD
**            Output  |     64               |  PS1_TxD
**         ----------------------------------------------------------
**
**
**
**     Contents  :
**         RecvChar - byte AS1_RecvChar(AS1_TComData *Chr);
**         SendChar - byte AS1_SendChar(AS1_TComData Chr);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2007
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

/* MODULE AS1. */

#pragma MESSAGE DISABLE C4002 /* WARNING C4002: Result not used is ignored */
#pragma MESSAGE DISABLE C4301 /* INFORMATION C4301: Inline expansion done for function call */

#include "AS1.h"
#include "Display1.h"
#include "bits5ULN.h"
#include "bits2ULN.h"
#include "trx.h"
#include "PTSL.h"
#include "PWSN.h"
#include "PUL.h"
#include "WDog1.h"
#include "ADC1.h"
#include "FLASH1.h"
#include "TI1.h"
#include "PWM.h"
#include "PWM4.h"
#include "PWM5.h"
#include "PWM6.h"
#include "O2.h"
#include "O4.h"
#include "O6.h"
#include "O7.h"
#include "In1.h"
#include "In2.h"
#include "Events.h"

#pragma DATA_SEG AS1_DATA
#pragma CODE_SEG AS1_CODE



#define OVERRUN_ERR      1             /* Overrun error flag bit   */
#define COMMON_ERR       2             /* Common error of RX       */
#define CHAR_IN_RX       4             /* Char is in the RX buffer     */
#define FULL_TX          8             /* Full transmit buffer     */

static byte SerFlag;                   /* Flags for serial communication */
                                       /* Bit 0 - Overrun error */
                                       /* Bit 1 - Common error of RX */
                                       /* Bit 2 - Char in the RX buffer */
                                       /* Bit 3 - Full TX buffer */
static AS1_TComData BufferRead;        /* Input char for SCI commmunication */

/*
** ===================================================================
**     Method      :  AS1_RecvChar (bean AsynchroSerial)
**
**     Description :
**         If any data is received, this method returns one
**         character, otherwise it returns an error code (it does
**         not wait for data). This method is enabled only if the
**         receiver property is enabled.
**         [Note:] Because the preferred method to handle error and
**         break exception in the interrupt mode is to use events
**         <OnError> and <OnBreak> the return value ERR_RXEMPTY has
**         higher priority than other error codes. As a consequence
**         the information about an exception in interrupt mode is
**         returned only if there is a valid character ready to be
**         read.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - Pointer to a received character
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_RXEMPTY - No data in receiver
**                           ERR_BREAK - Break character is detected
**                           (only when the <Interrupt service>
**                           property is disabled and the <Break
**                           signal> property is enabled)
**                           ERR_COMMON - common error occurred (the
**                           <GetError> method can be used for error
**                           specification)
** ===================================================================
*/
byte AS1_RecvChar(AS1_TComData *Chr)
{
  byte Result = ERR_OK;                /* Return error code */

  if(!(SerFlag & CHAR_IN_RX)) {        /* Is any char in the RX buffer? */
    return ERR_RXEMPTY;                /* If no then error */
  }
  EnterCritical();                     /* Save the PS register */
  *Chr = BufferRead;                   /* Received char */
  Result = (byte)((SerFlag & (OVERRUN_ERR|COMMON_ERR))?ERR_COMMON:ERR_OK);
  SerFlag &= ~(OVERRUN_ERR|COMMON_ERR|CHAR_IN_RX); /* Clear all errors in the status variable */
  ExitCritical();                      /* Restore the PS register */
  return Result;                       /* Return error code */
}

/*
** ===================================================================
**     Method      :  AS1_SendChar (bean AsynchroSerial)
**
**     Description :
**         Sends one character to the channel. If the bean is
**         temporarily disabled (Disable method) SendChar method
**         only stores data into an output buffer. In case of a zero
**         output buffer size, only one character can be stored.
**         Enabling the bean (Enable method) starts the transmission
**         of the stored data. This method is available only if the
**         transmitter property is enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Chr             - Character to send
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_TXFULL - Transmitter is full
** ===================================================================
*/
byte AS1_SendChar(AS1_TComData Chr)
{
  if(SerFlag & FULL_TX) {              /* Is any char in the TX buffer */
    return ERR_TXFULL;                 /* If yes then error */
  }
  EnterCritical();                     /* Save the PS register */
  (void) SCISR1;                       /* Reset interrupt request flag */
  SCIDRL = (byte)Chr;                  /* Store char to transmitter register */
  SCICR2_SCTIE = 1;                    /* Enable transmit interrupt */
  SerFlag |= FULL_TX;                  /* Set the flag "full TX buffer" */
  ExitCritical();                      /* Restore the PS register */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AS1_InterruptRx (bean AsynchroSerial)
**
**     Description :
**         The method services the receive interrupt of the selected 
**         peripheral(s) and eventually invokes the bean's event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#define ON_ERROR    1
#define ON_FULL_RX  2
#define ON_RX_CHAR  4
#pragma INLINE
void AS1_InterruptRx(void)
{
  AS1_TComData Data;                   /* Temporary variable for data */
  byte OnFlags = 0;                    /* Temporary variable for flags */

  Data = SCIDRL;                       /* Read data from the receiver */
  if(SerFlag & CHAR_IN_RX) {           /* Is a character already present in the receive buffer? */
    SerFlag |= OVERRUN_ERR;            /* If yes then set flag OVERRUN_ERR */
  } else {
    BufferRead = Data;
    SerFlag |= CHAR_IN_RX;             /* Set flag "char in RX buffer" */
    OnFlags |= ON_RX_CHAR;             /* Set flag "OnRxChar" */
  }
    if(OnFlags & ON_RX_CHAR) {         /* Is OnRxChar flag set? */
      AS1_OnRxChar();                  /* If yes then invoke user event */
    }
}

/*
** ===================================================================
**     Method      :  AS1_InterruptTx (bean AsynchroSerial)
**
**     Description :
**         The method services the receive interrupt of the selected 
**         peripheral(s) and eventually invokes the bean's event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#define ON_FREE_TX  1
#define ON_TX_CHAR  2
#pragma INLINE
void AS1_InterruptTx(void)
{
  if(SCICR2_TCIE && SCISR1_TC) {       /* Was the interrupt caused by the transmission complete flag? */
    SCICR2_TCIE = 0;                   /* Disable transmission complete interrupt */
    AS1_OnTxComplete();                /* Invoke user invent */
    return;
  }
  SerFlag &= ~FULL_TX;                 /* Reset flag "full TX buffer" */
  SCICR2_SCTIE = 0;                    /* Disable transmit interrupt */
  SCICR2_TCIE = 1;                     /* Enable transmission complete interrupt */
}

/*
** ===================================================================
**     Method      :  AS1_Interrupt (bean AsynchroSerial)
**
**     Description :
**         The method services the receive interrupt of the selected 
**         peripheral(s) and eventually invokes the bean's event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
ISR(AS1_Interrupt)
{
  byte StatReg = getReg(SCISR1);

  if (StatReg & (SCISR1_OR_MASK | SCISR1_FE_MASK | SCISR1_NF_MASK)) { /* Is any error flag set? */
    SerFlag |= COMMON_ERR;             /* If yes then set an internal flag */
    (void) SCIDRL;                     /* Dummy read of data register - clear error bits */
    StatReg &= ~SCISR1_RDRF_MASK;      /* Clear the receive data flag to discard the errorneous data */
  }
  if (StatReg & SCISR1_RDRF_MASK) {    /* Is the receiver interrupt flag set? */
    AS1_InterruptRx();                 /* If yes, then invoke the internal service routine. This routine is inlined. */
  }
  if (SCICR2 & (SCICR2_SCTIE_MASK | SCICR2_TCIE_MASK)) { /* Is the transmitter or the transmission complete interrupt enabled? */
    if (StatReg & SCISR1_TDRE_MASK) {  /* Is the transmitter interrupt flag set? */
      AS1_InterruptTx();               /* If yes, then invoke the internal service routine. This routine is inlined. */
    }
  }
}

#pragma CODE_SEG AS1_CODE
/*
** ===================================================================
**     Method      :  AS1_Init (bean AsynchroSerial)
**
**     Description :
**         Initializes the associated peripheral(s) and internal 
**         variables of the bean. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void AS1_Init(void)
{
  SerFlag = 0;                         /* Reset flags */
  /* SCICR1: LOOPS=0,SCISWAI=1,RSRC=0,M=0,WAKE=0,ILT=0,PE=0,PT=0 */
  setReg8(SCICR1, 64);                  
  /* SCISR2: ??=0,??=0,??=0,??=0,??=0,BRK13=0,TXDIR=0,RAF=0 */
  setReg8(SCISR2, 0);                   
  (void) SCISR1;                       /* Reset interrupt request flags */
  /* SCICR2: SCTIE=0,TCIE=0,RIE=0,ILIE=0,TE=0,RE=0,RWU=0,SBK=0 */
  SCICR2 = 0;                          /* Disable error interrupts */
  SCIBD = 104;                         /* Set prescaler bits */
  SCICR2 |= (SCICR2_TE_MASK | SCICR2_RE_MASK | SCICR2_RIE_MASK); /* Enable transmitter, Enable receiver, Enable receiver interrupt */
}



/* END AS1. */


/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.98 [03.98]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/