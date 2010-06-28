/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : AS1.C
**     Project   : ComSerie
**     Processor : MC9S08AC128CLK
**     Beantype  : AsynchroSerial
**     Version   : Bean 02.453, Driver 01.25, CPU db: 3.00.021
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 04/12/2008, 15:29
**     Abstract  :
**         This bean "AsynchroSerial" implements an asynchronous serial
**         communication. The bean supports different settings of
**         parity, word width, stop-bit and communication speed,
**         user can select interrupt or polling handler.
**         Communication speed can be changed also in runtime.
**         The bean requires one on-chip asynchronous serial channel.
**     Settings  :
**         Serial channel              : SCI2
**
**         Protocol
**             Init baud rate          : 9600baud
**             Width                   : 8 bits
**             Stop bits               : 1
**             Parity                  : none
**             Breaks                  : Disabled
**
**         Registers
**             Input buffer            : SCI2D     [$0047]
**             Output buffer           : SCI2D     [$0047]
**             Control register        : SCI2C1    [$0042]
**             Mode register           : SCI2C2    [$0043]
**             Baud setting reg.       : SCI2BD    [$0040]
**             Special register        : SCI2S1    [$0044]
**
**         Input interrupt
**             Vector name             : Vsci2rx
**             Priority                : 
**
**         Output interrupt
**             Vector name             : Vsci2tx
**             Priority                : 
**
**         Used pins:
**         ----------------------------------------------------------
**           Function | On package           |    Name
**         ----------------------------------------------------------
**            Input   |     80               |  PTC5_RxD2
**            Output  |     79               |  PTC3_TxD2
**         ----------------------------------------------------------
**
**
**
**     Contents  :
**         Enable          - byte AS1_Enable(void);
**         Disable         - byte AS1_Disable(void);
**         RecvChar        - byte AS1_RecvChar(AS1_TComData *Chr);
**         SendChar        - byte AS1_SendChar(AS1_TComData Chr);
**         GetCharsInRxBuf - word AS1_GetCharsInRxBuf(void);
**         GetCharsInTxBuf - word AS1_GetCharsInTxBuf(void);
**         GetError        - byte AS1_GetError(AS1_TError *Err);
**         GetRxIdle       - bool AS1_GetRxIdle(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2008
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/


/* MODULE AS1. */

#pragma MESSAGE DISABLE C4002 /* WARNING C4002: Result not used is ignored */

#include "AS1.h"
#include "Events.h"




#define OVERRUN_ERR      0x01          /* Overrun error flag bit   */
#define FRAMING_ERR      0x02          /* Framing error flag bit   */
#define PARITY_ERR       0x04          /* Parity error flag bit    */
#define NOISE_ERR        0x08          /* Noise error flag bit     */
#define CHAR_IN_RX       0x10          /* Char is in RX buffer     */
#define FULL_TX          0x20          /* Full transmit buffer     */
#define IDLE_ERR         0x40          /* Idle character flag bit  */


static byte SerFlag;                   /* Flags for serial communication */
                                       /* Bit 0 - Overrun error */
                                       /* Bit 1 - Framing error */
                                       /* Bit 2 - Parity error */
                                       /* Bit 3 - Noise error */
                                       /* Bit 4 - Char in RX buffer */
                                       /* Bit 5 - Full TX buffer */
                                       /* Bit 6 - Idle detected */
static bool EnUser;                    /* Enable/Disable SCI */
static byte ErrFlag = 0;               /* Error flags mirror of SerFlag */
static AS1_TComData BufferRead;        /* Input char for SCI commmunication */
static AS1_TComData BufferWrite;       /* Output char for SCI commmunication */

/*
** ===================================================================
**     Method      :  AS1_Enable (bean AsynchroSerial)
**
**     Description :
**         Enables the bean - it starts the send and receive
**         functions. Events may be generated
**         ("DisableEvent"/"EnableEvent").
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte AS1_Enable(void)
{
  if(!EnUser) {                        /* Is the device disabled by user? */
    EnUser = TRUE;                     /* If yes then set the flag "device enabled" */
    if(SCI2S1_TDRE && !SCI2S1_TC) {    /* Test if there is an unsent character in the shift register */
      SCI2C2_TCIE = 1;                 /* Enable transmission complete interrupt */
    }
    SCI2BDH = 0x00;                    /* Set high divisor register (enable device) */
    SCI2BDL = 0x82;                    /* Set low divisor register (enable device) */
      /* SCI2C3: ORIE=1,NEIE=1,FEIE=1,PEIE=1 */
    SCI2C3 |= 0x0F;                    /* Enable error interrupts */
    SCI2C2 |= ( SCI2C2_TE_MASK | SCI2C2_RE_MASK | SCI2C2_RIE_MASK | SCI2C2_ILIE_MASK); /*  Enable transmitter, Enable receiver, Enable receiver interrupt, Enable idle interrupt */
    if(SerFlag & FULL_TX) {            /* Is any char in the transmit buffer? */
      (void)SCI2S1;                    /* Reset interrupt request flag */
      while(!SCI2S1_TDRE) {}           /* Wait for transmitter empty */
      SCI2D = (byte)BufferWrite;       /* Store char to the transmitter register */
      SCI2C2_TIE = 1;                  /* Enable transmit interrupt */
    }
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AS1_Disable (bean AsynchroSerial)
**
**     Description :
**         Disables the bean - it stops the send and receive
**         functions. No events will be generated.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte AS1_Disable(void)
{
  if(EnUser) {                         /* Is the device enabled by user? */
    EnUser = FALSE;                    /* If yes then set the flag "device disabled" */
    /* SCI2C3: ORIE=0,NEIE=0,FEIE=0,PEIE=0 */
    SCI2C3 &= ~0x0F;                   /* Disable error interrupts */
    SCI2C2 &= ( (~SCI2C2_RE_MASK) & (~SCI2C2_TE_MASK) & (~SCI2C2_TIE_MASK) & (~SCI2C2_RIE_MASK) & (~SCI2C2_TCIE_MASK) & (~SCI2C2_ILIE_MASK)); /*  Disable receiver, Disable transmitter, Disable transmit interrupt, Disable receiver interrupt, Disable transmission complete interrupt, Disable idle interrupt */
    SCI2BDH = 0x00;                    /* Set high divisor register to zero (disable device) */
    SCI2BDL = 0x00;                    /* Set low divisor register to zero (disable device) */
  }
  return ERR_OK;                       /* OK */
}

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

  if(!(SerFlag & CHAR_IN_RX)) {        /* Is any char in RX buffer? */
    return ERR_RXEMPTY;                /* If no then error */
  }
  EnterCritical();                     /* Save the PS register */
  *Chr = BufferRead;                   /* Received char */
  Result = (byte)((SerFlag & (OVERRUN_ERR|FRAMING_ERR|PARITY_ERR|NOISE_ERR))?ERR_COMMON:ERR_OK);
  SerFlag &= ~(OVERRUN_ERR|FRAMING_ERR|PARITY_ERR|NOISE_ERR|CHAR_IN_RX); /* Clear all errors in the status variable */
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
  if(SerFlag & FULL_TX) {              /* Is any char in TX buffer? */
    return ERR_TXFULL;                 /* If yes then error */
  }
  EnterCritical();                     /* Save the PS register */
  if(EnUser) {                         /* Is the device enabled by user? */
    (void)SCI2S1;                      /* Reset interrupt request flag */
    SCI2D = (byte)Chr;                 /* Store char to the transmitter register */
    SCI2C2_TIE = 1;                    /* Enable transmit interrupt */
  }
  else {
    BufferWrite = Chr;                 /* Store char to temporary variable */
  }
  SerFlag |= FULL_TX;                  /* Set the flag "full TX buffer" */
  ExitCritical();                      /* Restore the PS register */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AS1_GetCharsInRxBuf (bean AsynchroSerial)
**
**     Description :
**         Returns the number of characters in the input buffer.
**         This method is available only if the receiver property is
**         enabled.
**     Parameters  : None
**     Returns     :
**         ---             - The number of characters in the input
**                           buffer.
** ===================================================================
*/
word AS1_GetCharsInRxBuf(void)
{
  return (word)((SerFlag & CHAR_IN_RX) != 0); /* Return number of chars in receive buffer */
}

/*
** ===================================================================
**     Method      :  AS1_GetCharsInTxBuf (bean AsynchroSerial)
**
**     Description :
**         Returns the number of characters in the output buffer.
**         This method is available only if the transmitter property
**         is enabled.
**     Parameters  : None
**     Returns     :
**         ---             - The number of characters in the output
**                           buffer.
** ===================================================================
*/
word AS1_GetCharsInTxBuf(void)
{
  return (word)((SerFlag & FULL_TX) != 0); /* Return number of chars in the transmitter buffer */
}

/*
** ===================================================================
**     Method      :  AS1_GetError (bean AsynchroSerial)
**
**     Description :
**         Returns a set of errors on the channel (errors that
**         cannot be returned by given methods). The errors
**         accumulate in a set; after calling [GetError] this set is
**         returned and cleared.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Err             - Pointer to the returned set of errors
**     Returns     :
**         ---             - Error code (if GetError did not succeed),
**                           possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte AS1_GetError(AS1_TError *Err)
{
  EnterCritical();                     /* Save the PS register */
  Err->err = 0;
  Err->errName.OverRun = ((ErrFlag & OVERRUN_ERR) != 0); /* Overrun error */
  Err->errName.Framing = ((ErrFlag & FRAMING_ERR ) != 0); /* Framing error */
  Err->errName.Parity = ((ErrFlag & PARITY_ERR) != 0); /* Parity error */
  Err->errName.Noise = ((ErrFlag & NOISE_ERR) != 0); /* Noise error */
  ErrFlag = 0;                         /* Clear error flags */
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
#define ON_ERROR      1
#define ON_FULL_RX    2
#define ON_RX_CHAR    4
#define ON_IDLE_CHAR  8
ISR(AS1_InterruptRx)
{
  byte StatReg = SCI2S1;               /* Temporary variable for status flags */
  AS1_TComData Data;                   /* Temporary variable for data */
  byte OnFlags = 0;                    /* Temporary variable for flags */

  if (StatReg & SCI2S1_RDRF_MASK) {    /* Has a character been received? */
    Data = SCI2D;                      /* Read data from the receiver */
    if(SerFlag & CHAR_IN_RX) {         /* Is any char already present in the receive buffer? */
      SerFlag |= OVERRUN_ERR;          /* If yes then set flag OVERRUN_ERR */
      ErrFlag |= OVERRUN_ERR;
    }
    if(!(SerFlag & OVERRUN_ERR )) {    /* Is an overrun detected? */
      BufferRead = Data;
      SerFlag |= CHAR_IN_RX;           /* Set flag "char in RX buffer" */
      OnFlags |= ON_RX_CHAR;           /* Set flag "OnRxChar" */
    }
    else {
      OnFlags |= ON_ERROR;             /* Set flag "OnError" */
    }
  }
  if (StatReg & SCI2S1_IDLE_MASK) {    /* If IDLE character received */
    if (!(StatReg & SCI2S1_RDRF_MASK)) { /* If no data received, clear the flag */
      (void)SCI2D;                     /* Dummy read of data register - clear idle flag */
    }
    SerFlag |= IDLE_ERR;
  }
  if(OnFlags & ON_ERROR) {             /* Is OnError flag set? */
    AS1_OnError();                     /* If yes then invoke user event */
  }
  else {
    if(OnFlags & ON_RX_CHAR) {         /* Is OnRxChar flag set? */
      AS1_OnRxChar();                  /* If yes then invoke user event */
      AS1_OnRxCharExt(Data);           /* If yes then invoke user event */
    }
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
ISR(AS1_InterruptTx)
{
  byte OnFlags = 0;                    /* Temporary variable for flags */

  if(SCI2C2_TCIE && SCI2S1_TC) {       /* Was the interrupt caused by the transmission complete flag? */
    SCI2C2_TCIE = 0;                   /* Disable transmission complete interrupt */
    AS1_OnTxComplete();                /* Invoke user invent */
    return;
  }
  if(SerFlag & FULL_TX) {              /* Is a char already present in the transmit buffer? */
    OnFlags |= ON_TX_CHAR;             /* Set flag "OnTxChar" */
  }
  SerFlag &= ~FULL_TX;                 /* Reset flag "full TX buffer" */
  SCI2C2_TIE = 0;                      /* Disable transmit interrupt */
  SCI2C2_TCIE = 1;                     /* Enable transmission complete interrupt */
  if(OnFlags & ON_TX_CHAR) {           /* Is flag "OnTxChar" set? */
    AS1_OnTxChar();                    /* If yes then invoke user event */
  }
}

/*
** ===================================================================
**     Method      :  AS1_InterruptError (bean AsynchroSerial)
**
**     Description :
**         The method services the error interrupt of the selected 
**         peripheral(s) and eventually invokes the bean's event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
ISR(AS1_InterruptError)
{
  byte StatReg = getReg(SCI2S1);
  byte OnFlags = 0;                    /* Temporary variable for flags */

  (void)SCI2D;                         /* Dummy read of data register - clear error bits */
  if(StatReg & SCI2S1_IDLE_MASK) {     /* if IDLE character received */
    OnFlags |= IDLE_ERR;
  }
  if(StatReg & SCI2S1_OR_MASK) {       /* Is overrun error detected? */
    OnFlags |= OVERRUN_ERR;            /* If yes then set an internal flag */
  }
  if(StatReg & SCI2S1_NF_MASK) {       /* Is noise error detected? */
    OnFlags |= NOISE_ERR;              /* If yes then set an internal flag */
  }
  if (StatReg & SCI2S1_FE_MASK) {      /* Is framing error detected? */
    OnFlags |= FRAMING_ERR;            /* If yes then set an internal flag */
    }
  if(StatReg & SCI2S1_PF_MASK) {
    OnFlags |= PARITY_ERR;
  }
  SerFlag |= OnFlags;                  /* Copy flags status to SerFlag status variable */
  ErrFlag |= OnFlags;                  /* Copy flags status to ErrFlag status variable */
  if(OnFlags & (OVERRUN_ERR|FRAMING_ERR|PARITY_ERR|NOISE_ERR)) { /* Was any error set? */
    AS1_OnError();                     /* If yes then invoke user event */
  }
}

/*
** ===================================================================
**     Method      :  AS1_Init (bean AsynchroSerial)
**
**     Description :
**         Initializes the associated peripheral(s) and the bean internal 
**         variables. The method is called automatically as a part of the 
**         application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void AS1_Init(void)
{
  SerFlag = 0;                         /* Reset flags */
  EnUser = TRUE;                       /* Enable device */
  /* SCI2C1: LOOPS=0,SCISWAI=0,RSRC=0,M=0,WAKE=0,ILT=0,PE=0,PT=0 */
  setReg8(SCI2C1, 0x00);               /* Configure the SCI */ 
  /* SCI2C3: R8=0,T8=0,TXDIR=0,TXINV=0,ORIE=0,NEIE=0,FEIE=0,PEIE=0 */
  setReg8(SCI2C3, 0x00);               /* Disable error interrupts */ 
  /* SCI2S2: LBKDIF=0,RXEDGIF=0,??=0,RXINV=0,RWUID=0,BRK13=0,LBKDE=0,RAF=0 */
  setReg8(SCI2S2, 0x00);                
  /* SCI2C2: TIE=0,TCIE=0,RIE=0,ILIE=0,TE=0,RE=0,RWU=0,SBK=0 */
  setReg8(SCI2C2, 0x00);               /* Disable all interrupts */ 
  SCI2BDH = 0x00;                      /* Set high divisor register (enable device) */
  SCI2BDL = 0x82;                      /* Set low divisor register (enable device) */
      /* SCI2C3: ORIE=1,NEIE=1,FEIE=1,PEIE=1 */
  SCI2C3 |= 0x0F;                      /* Enable error interrupts */
  SCI2C2 |= ( SCI2C2_TE_MASK | SCI2C2_RE_MASK | SCI2C2_RIE_MASK | SCI2C2_ILIE_MASK); /*  Enable transmitter, Enable receiver, Enable receiver interrupt, Enable idle interrupt */
}

/*
** ===================================================================
**     Method      :  AS1_GetRxIdle (bean AsynchroSerial)
**
**     Description :
**         Returns the state of the receiver idle flag. This method
**         is available only if event <OnIdle> is disabled.
**     Parameters  : None
**     Returns     :
**         ---             - The state of the receiver idle flag.
** ===================================================================
*/
bool AS1_GetRxIdle(void)
{
  bool Result;

  EnterCritical();                     /* Save the PS register */
  Result = (bool)((SerFlag & IDLE_ERR)?1:0); /* If idle signal has been received? */
  SerFlag &= ~IDLE_ERR;                /* Reset idle signal flag */
  ExitCritical();                      /* Restore the PS register */
  return Result;                       /* OK */
}



/* END AS1. */


/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 3.03 [04.07]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
