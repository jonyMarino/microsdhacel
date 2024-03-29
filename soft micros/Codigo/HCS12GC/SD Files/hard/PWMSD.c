/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : TO1.C
**     Project   : _10_03
**     Processor : MC9S12GC32CFU16
**     Beantype  : TimerOut
**     Version   : Bean 02.095, Driver 01.08, CPU db: 2.87.320
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 19/07/2006, 10:03 a.m.
**     Abstract  :
**         This bean implements a periodic signal generator 1:1 (Flip-Flop Output).
**         The signal alternates the "0" and "1" output values in exactly
**         regular intervals; that is why the time length of the "0" part
**         of one pulse is equal to the "1" part of one pulse.
**     Settings  :
**         Used output pin             : 
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       6             |  PT1_PWM1_IOC1
**             ----------------------------------------------------
**
**         Timer name                  : TIM (16-bit)
**         Compare name                : TC1
**           Counter shared            : No
**
**         High speed mode
**             Prescaler               : divide-by-4
**             Clock                   : 6250000 Hz
**           Pulse width
**             Xtal ticks              : 32
**             microseconds            : 4
**             seconds (real)          : 0.0000040
**             Hz                      : 250000
**             kHz                     : 250
**
**         Runtime setting             : pulse width interval (continual setting)
**             ticks                   : 32 to 80000 ticks
**             microseconds            : 4 to 10000 microseconds
**             milliseconds            : 1 to 10 milliseconds
**             seconds (real)          : 0.0000040 to 0.0100000 seconds
**             Hz                      : 100 to 250000 Hz
**             kHz                     : 1 to 250 kHz
**
**         Initialization:
**              Output level           : low
**              Timer                  : Enabled
**              Events                 : Enabled
**
**         Timer registers
**              Counter                : TCNT      [68]
**              Mode                   : TIOS      [64]
**              Run                    : TSCR1     [70]
**              Prescaler              : TSCR2     [77]
**
**         Compare registers
**              Compare                : TC1       [82]
**
**         Flip-flop registers
**              Mode                   : TCTL2     [73]
**     Contents  :
**         Enable      - byte TO1_Enable(void);
**         Disable     - byte TO1_Disable(void);
**         SetPeriodUS - byte TO1_SetPeriodUS(word Time);
**         SetValue    - byte TO1_SetValue(void);
**         ClrValue    - byte TO1_ClrValue(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/


/* MODULE PWM. */

#include "Events.h"
#include "PE_Error.h"
#include "Mydefines.h"
#include "PWM.h"
#include "SalidaEvents.h"


#pragma DATA_SEG PWM_DATA                                            
#pragma CODE_SEG PWM_CODE  
#pragma CONST_SEG DEFAULT

#pragma MESSAGE DISABLE C2705                   

#define PWM_NUM_SALIDAS 4

#if NUM_SALIDAS > PWM_NUM_SALIDAS
#error no se van a poder usar todas las salidas con PWM
#endif

#define TICKS_1_SEG 500000

const dword PeriodsTicks[PWM_MAX_VALUE_PERIODS+1]={ 
   TICKS_1_SEG/10, /* 100 ms*/
   TICKS_1_SEG/5,	 /* 200 ms*/
   TICKS_1_SEG/2,	 /* 500 ms*/
   TICKS_1_SEG,	   /*   1  s*/
   TICKS_1_SEG*2,	 /*   2  s*/
   TICKS_1_SEG*5,	 /*   5  s*/
   TICKS_1_SEG*10,	 /*  10  s*/
   TICKS_1_SEG*20,	 /*  20  s*/
   TICKS_1_SEG*50,	 /*  50  s*/
   TICKS_1_SEG/200   /* Anl(5ms) */
};
const char * const strsPeriods[]={
  ".1  ",".2  ",".5  ","1   ","2   ","5   ","10  ","20  "
  ,"50  ","AnL "
};


word Pot[PWM_NUM_SALIDAS];

static bool EnUser[PWM_NUM_SALIDAS];      /* Enable/Disable device by user */

static dword Period[PWM_NUM_SALIDAS],Duty[PWM_NUM_SALIDAS];

#define DutyFree(num) Period[num] - Duty[num]

/*
** ===================================================================
**     Method      :  TO1_SetPeriod (bean TimerOut)
**
**     Description :
**         This method sets the new period of the output signal. The
**         period is expressed in microseconds as a 16-bit unsigned
**         integer number.
**         This method is available only if the runtime setting type
**         'from interval' is selected in the Timing dialog box in
**         the Runtime setting area.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Time            - Period to set [in microseconds]
**                      (4 to 10000 microseconds)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/
byte setPWM_period(byte Mode,byte salida)
{
  if (Mode>PWM_MAX_VALUE_PERIODS)
    return ERR_RANGE;
  Period[salida] = PeriodsTicks[Mode];

  return ERR_OK;                       /* OK */ 
}

byte PWM_SetRatio16(word Ratio,byte salida)		/*Ratio es un valor de 0 a 1000*/
{
  
  if (Ratio >1000 || salida>PWM_NUM_SALIDAS)    /* Is the given value out of range? */
    return ERR_RANGE;                  /* If yes then error */
  
  if(EnUser[salida]){
    if (Ratio==1000)
      Duty[salida] = Period[salida];
    else if(Ratio==0)
      Duty[salida] = 0;
    else if (Period[salida]<4000000)		 /*Verifico los valores para decidir que operacion hacer debido a los limites de un long*/
      Duty[salida] = (Period[salida]*Ratio)/1000;
    else
      Duty[salida] = (Period[salida]/1000)*Ratio;
  }else{
     if(Ratio==0){
      Duty[salida]=0;
  	  PWM_ClrValue(salida);
     }else{
      Duty[salida]=1000;
      Ratio=1000;
  	  PWM_SetValue(salida);  
     }
  }
  
  if(Duty[salida]<15){//15 es el minimo tiempo para asegurar la corrida de la interrupcion  
    if(Duty[salida]<8) 
      Duty[salida]=0;
    else 
      Duty[salida]=15;  
  } 
  else{
    long dutyfree=DutyFree(salida);
    
    if (dutyfree<15){
      if(dutyfree<8) 
        Duty[salida]=Period[salida];
      else 
        Duty[salida]=Period[salida]-15;      
    }
  }
  
  Pot[salida]=Ratio;
  
  return ERR_OK;                       /* OK */
}

int PWM_GetRatio16(byte salida){
  return Pot[salida]; 
}


/*
** ===================================================================
**     Method      :  PWM_getState
**
**     Description :
** ===================================================================
*/
bool PWM_getState(byte num_salida){
  return EnUser[num_salida]; 
}
/*
** ===================================================================
**     Method      :  PWM_getPeriodText
**
**     Description :
** ===================================================================
*/
const char * PWM_getPeriodText(byte period){
  return strsPeriods[period];
}
/*
** ===================================================================
**     Method      :  HWEnDi (bean TimerOut)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
static void HWEnDi(byte num_salida)
{  byte pos,num_pwm;
  
  num_pwm= num_salida;
  pos = 1<<num_pwm;
  if (EnUser[num_salida]) {           /* Enable device? */
    TFLG1 |= pos;                     /* Reset request flag */
    TIE |= pos;                       /* Enable interrupt */
    if(num_pwm<=3)
      TCTL2 |= 1<<(num_pwm*2);                     /* Connect timer to output pin */
    else
      TCTL1 |= 1<<((num_pwm-3)*2);
  }
  else {                               /* Disable device? */
    if(num_pwm<=3)
      TCTL2 &= ~(1<<(num_pwm*2));                     /* Connect timer to output pin */
    else
      TCTL1 &= ~(1<<((num_pwm-3)*2));
      TIE &= ~pos;                       /* Disable interrupt */
  }
}


/*
** ===================================================================
**     Method      :  TO1_Enable (bean TimerOut)
**
**     Description :
**         Enables the bean - it starts the signal generation. Events
**         may be generated ("DisableEvent"/"EnableEvent").
**     Parameters  : None
**     Returns     : None
** ===================================================================
*/
void PWM_Enable(byte num_salida)
{
  if (!EnUser[num_salida]) {                       /* Is the device disabled by user? */
    EnUser[num_salida] = TRUE;                     /* If yes then set the flag "device enabled" */
    HWEnDi(num_salida);                          /* Disable the device */
  }
}

/*
** ===================================================================
**     Method      :  TO1_Disable (bean TimerOut)
**
**     Description :
**         Disables the timer - it stops signal generation and events
**         calling. When the timer is disabled, it is possible to
**         call methods "ClrValue" and "SetValue".
**     Parameters  : None
**     Returns     : None
** ===================================================================
*/
void PWM_Disable(byte num_salida)
{
  if (EnUser[num_salida]) {                        /* Is the device enabled by user? */
    EnUser[num_salida] = FALSE;                    /* If yes then set the flag "device disabled" */
    HWEnDi(num_salida);                          /* Disable the device */
  }
}

/*
** ===================================================================
**     Method      :  TO1_Init (bean TimerOut)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
void PWM_Init(void)
{					
}

/*
** ===================================================================
**     Method      :  PWM_SetValue (bean TimerOut)
**
**     Description :
**         This method sets (sets to "1" = "High") timer flip-flop
**         output signal level. It allow user to directly set the
**         output pin value (=flip-flop state), and can set the
**         signal polarity. This method works only when the timer is
**         disabled (Disable) otherwise it returns the error code.
**     Parameters  : None
**     Returns     : None
** ===================================================================
*/
void PWM_SetValue(byte num_salida)
{
  
  PTT |= 1<<num_salida;                        /* Set output signal level to high */
  Pot[num_salida]=1000;
  Salida_OnToggle(1,num_salida);
}


/*
** ===================================================================
**     Method      :  PWM_ClrValue (bean TimerOut)
**
**     Description :
**         This method clears (sets to "0" = "Low") timer flip-flop
**         output signal level. It allow user to directly set the
**         output pin value (=flip-flop state), and can set the
**         signal polarity. This method works only when the timer is
**         disabled (Disable) otherwise it returns the error code.
**     Parameters  : None
**     Returns     : None
** ===================================================================
*/
void PWM_ClrValue(byte num_salida)
{
  PTT &= ~(1<<num_salida);                        /* Set output signal level to high */
  Pot[num_salida]=0;  
  Salida_OnToggle(0,num_salida);
}

/*
** ===================================================================
**     Method      :  Conf_Toggle (bean TimerOut)
**
**     Description :
**         This method is internal. Permite Elegir cual ser� el proximo 
**  estado al interrumpir
** ===================================================================
*/
void PutVal (bool Value,byte salida){
  switch(salida){
    case 0:
      TCTL2_OL1=Value;
      break;
    case 1:
      TCTL1_OL4=Value; 
      break;
    case 2:
      TCTL1_OL5=Value;
      break;
    case 3:
      TCTL1_OL6=Value;
  }
}
/*
** ===================================================================
**     Method      :  Conf_Toggle (bean TimerOut)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
static dword Conf_Toggle(bool * next_Value,byte salida)
{
static long CicloLow[PWM_NUM_SALIDAS];//={65535,65535,65535,65535};
  
if ((* next_Value &&  Duty[salida]!=Period[salida]) || Duty[salida]==0){
    PutVal (0,salida);  /* Poner la salida en bajo al interrumpir */                   
    * next_Value=0;
    return CicloLow[salida]; 
  }else{
    PutVal(1,salida);  /* Poner la salida en alto al interrumpir */                   
    * next_Value=1;
    CicloLow[salida] = DutyFree(salida);
    return Duty[salida];
  }
}

/*
** ===================================================================
**     Method      :  TO1_Interrupt (bean TimerOut)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
#define PWM_INTERRUPT(n)    \
ISR(PWM##n##_Interrupt){\
  static long ciclo=65535;   \
  static bool internalValue=0,previousValue=1;  \
  if (ciclo>65535){					\
    TC##n += 65500;				  \
 		ciclo-=65500;						\
  }else{										\
    TC##n += ciclo;					\
    ciclo=0;								\
  }												  \
  TFLG1 = 1<<n;             \
  Cpu_EnableInt();          \
    if (internalValue!=previousValue){/*�Hubo un cambio de estado en esta interrupcion???*/  \
 		  previousValue=internalValue;\
 		  Salida_OnToggle(internalValue,n); \
  }																			 \
  if(ciclo==0)													 \
    ciclo=Conf_Toggle(&internalValue,n); \
}


#pragma CODE_SEG __NEAR_SEG NON_BANKED   

PWM_INTERRUPT(0)
PWM_INTERRUPT(1)
PWM_INTERRUPT(2)
PWM_INTERRUPT(3)
PWM_INTERRUPT(4)
PWM_INTERRUPT(5)
PWM_INTERRUPT(6)
PWM_INTERRUPT(7)

									
#pragma CODE_SEG PWM_CODE   
 


  	

  			                 

/* END TO1. */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
