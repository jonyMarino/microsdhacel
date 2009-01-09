/** ###################################################################
**     Filename  : PWMManager01_45.c
**     Project   : Controlador
**     Processor : MC9S12GC32CFU16
**     Version   : 0.0.1
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 11/08/2008, 14:39
**     Abstract  :
**         Metodo de factoria que retorna instancias de clase que 
**     encapsulan el comportamiento del PWM01 y PWM45 manejados 
**     simultaneamente.
**      Para utilizar alguno de los dos por separado, utilize PWMHardXX. 
**
**
**     Autor     : Jonathan Marino
**     mail      : jonymarino@gmail.com
** ###################################################################*/
#include "PWMManager01_45.h"
#include "PWMHard_protected.h"
#include "stddef.h"

static void PWM01_defConstructor(void * self,TConfPWM * conf);
static void PWM45_defConstructor(void * self,TConfPWM * conf);
static void PWM01_actualizarPotencia(uint duty); 
static void PWM45_actualizarPotencia(uint duty);
static void PWM01_setDuty(struct PWM01* self,uint duty);
static void PWM45_setDuty(struct PWM45* self,uint duty);
static void PWM01_setTipoSalida(struct PWM01* self,TipoSalida onoff);
static void PWM45_setTipoSalida(struct PWM45* self,TipoSalida onoff);
static TipoSalida PWM01_tipoSalida(struct PWM01* self);
static TipoSalida PWM45_tipoSalida(struct PWM45* self);
TError PWMManager01_45_setPeriodo(struct PWM* self,int periodo);  
/*
  CASOS DE COMBINACION DE PERIODOS ENTRE 01 y 45
*/

/*
  CASO 1 : uno en 50s y el otro en .5s 
  				 el de 50 tiene un clock de 992us y el de .5 8uS
  Sus periodos son los siguientes:
*/
#define PERIODO_50S_CASO1 50403
#define PERIODO_05S_CASO1 62500


/*
  CASO 2 : uno en 50s y el otro distinto de .5s 
  				 los mayores igual a 1s tienen un clock de 1ms y el resto de 4uS
  Sus periodos son los siguientes:
*/
static const uint periodosCaso2[] = {  
  20000,		//.1 s
  40000,		//.2 s
  0,		    //.5 s
  1000,		  //1 s
  2000,		  //2 s
  5000,		  //5 s
  10000,		//10 s
  20000,		//20 s
  50000,		//50s
  1000, 		//anlg 5ms
};

/*
  CASO 3 : uno en 50s y el otro distinto de .5s 
  				 los mayores igual a 1s tienen un clock de 1ms y el resto de 4uS
  Sus periodos son los siguientes:
*/
static const uint periodosCaso3[] = {  
  25000,		//.1 s
  50000,		//.2 s
  1250,		  //.5 s
  2500,		  //1 s
  5000,		  //2 s
  12500,		//5 s
  25000,		//10 s
  50000,		//20 s
  0,		    //50s
  1250, 		//anlg 5ms
};

/*
  escaladoresCaso2_3  0 - no escala
                      1 - escala
*/
static const bool escaladoresCaso2_3[]={
  0,		//.1 s
  0,		//.2 s
  1,		//.5 s
  1,		//1 s
  1,		//2 s
  1,		//5 s
  1,		//10 s
  1,		//20 s
  1,		//50s
  0, 		//anlg 5ms
};

/*
PCKA2 PCKA1 PCKA0 Value of Clock A
0     0     0     Bus Clock
0     0     1     Bus Clock / 2
0     1     0     Bus Clock / 4
0     1     1     Bus Clock / 8
1     0     0     Bus Clock / 16
1     0     1     Bus Clock / 32
1     1     0     Bus Clock / 64
1     1     1     Bus Clock / 128
*/


static struct PWM01{
    struct PWM super;
}pwm01;
static struct PWM45{
    struct PWM super;
}pwm45;
  
/*  public: PWMManager01_45_get01() */
struct PWM * PWMManager01_45_get01(TConfPWM * conf){
   static const struct IPWMClass PWM01Class={ 
    &Class,
    "",
    &Object,
    sizeof(pwm01),
    PWM01_defConstructor,
    NULL,
    NULL,
    NULL,
    Salida_getPotencia,
    PWM01_setDuty,    
    PWM01_tipoSalida,
    PWM01_setTipoSalida,
    Salida_getConectada,
    Salida_setConectada,
    PWM_getPeriodo,
    PWMManager01_45_setPeriodo   
  };

  newAlloced(&pwm01,&PWM01Class,conf);
  return &pwm01;

}

/*  public: PWMManager01_45_get45() */
struct PWM * PWMManager01_45_get45(TConfPWM * conf){
  static const struct IPWMClass PWM45Class={ 
    &Class,
    "",
    &Object,
    sizeof(pwm45),
    PWM45_defConstructor,
    NULL,
    NULL,
    NULL,
    Salida_getPotencia,
    PWM45_setDuty,
    PWM45_setTipoSalida,
    PWM45_tipoSalida,
    Salida_getConectada,
    Salida_setConectada,
    PWM_getPeriodo,
    PWMManager01_45_setPeriodo   
  };
  
  newAlloced(&pwm45,&PWM45Class,conf);
  
  return &pwm45;
}

/* private: PWMManager01_45_configCaso1()*/
void PWMManager01_45_configCaso1(ReferenciaPWM pwmPeriodo50,ReferenciaPWM pwmPeriodo05){
  PWMPRCLK_PCKA=7;   /*Set Prescaler*/
  PWMSCLA = 112; 		 /*Set Scaler*/
  PWMHard_setPeriodo(pwmPeriodo50,PERIODO_50S_CASO1);
  PWMHard_setPeriodo(pwmPeriodo05,PERIODO_05S_CASO1); 
  PWMHard_noEscalar(pwmPeriodo05); 
}

/* private: PWMManager01_45_configCaso2()*/
void PWMManager01_45_configCaso2(ReferenciaPWM pwmPeriodo50,ReferenciaPWM pwmPeriodoNo05,TPeriod periodoNo05){
  bool escalar;
  PWMPRCLK_PCKA=6;   /*Set Prescaler*/
  PWMSCLA = 125; 		 /*Set Scaler*/
  
  PWMHard_setPeriodo(pwmPeriodo50,PERIODO_50S_CASO1);
  PWMHard_setPeriodo(pwmPeriodoNo05,periodosCaso2[periodoNo05]); 
  PWMHard_escalar(pwmPeriodo50);
  
  if(escaladoresCaso2_3[periodoNo05])
    PWMHard_escalar(pwmPeriodoNo05);
  else
    PWMHard_noEscalar(pwmPeriodoNo05);
}

/* private: PWMManager01_45_configCaso3()*/
void PWMManager01_45_configCaso3(ReferenciaPWM pwmPeriodo1,TPeriod periodo1,ReferenciaPWM pwmPeriodo2,TPeriod periodo2){
  bool escalar;
  PWMPRCLK_PCKA=6;   /*Set Prescaler*/
  PWMSCLA = 125; 		 /*Set Scaler*/ 
  
  PWMHard_setPeriodo(pwmPeriodo1,periodosCaso3[periodo1]);
  PWMHard_setPeriodo(pwmPeriodo2,periodosCaso3[periodo2]); 
  
  // escalar periodo1??
  if(escaladoresCaso2_3[periodo1])
    PWMHard_escalar(pwmPeriodo1); 
  else
    PWMHard_noEscalar(pwmPeriodo1);
  // escalar periodo2??
    if(escaladoresCaso2_3[periodo2])
    PWMHard_escalar(pwmPeriodo2); 
  else
    PWMHard_noEscalar(pwmPeriodo2);
}

/*  private: PWMManager01_45_setPeriodo() */
TError PWMManager01_45_setPeriodo(struct PWM* self,int periodo){
  struct PWM* pwmDependienteObj;
  ReferenciaPWM pwmPeriodoCambiando;
  ReferenciaPWM pwmDependiente;
  uint periodoDependiente;
  TError err;
  
  if(periodo<0 || periodo>PWM_MAX_VALUE_PERIODS)
    return ERR_VALUE; //error
  err= PWM_setPeriodo(self,periodo);
  if(err)
    return err;
  
  
  if(self == &pwm01){
    pwmDependiente = RefPWM45;
    pwmPeriodoCambiando = RefPWM01; 
    pwmDependienteObj=&pwm45;
    
  }else{																			
    pwmDependiente = RefPWM01;
    pwmPeriodoCambiando = RefPWM45;
    pwmDependienteObj=&pwm01;
  }
  
  periodoDependiente = getPeriodo(pwmDependienteObj);
  
  //Checkear caso1
  if(periodo == PWM_50sec && periodoDependiente == PWM_500ms ){      			 
      PWMManager01_45_configCaso1(pwmPeriodoCambiando,pwmDependiente);    
  } else if(periodoDependiente == PWM_50sec && periodo == PWM_500ms){																					
      PWMManager01_45_configCaso1(pwmDependiente,pwmPeriodoCambiando);
  }
  
  //Checkear caso2
  else if(periodo == PWM_50sec ){
    PWMManager01_45_configCaso2(pwmPeriodoCambiando,pwmDependiente,periodoDependiente); 
  } else if(periodoDependiente == PWM_50sec) {    
    //caso2																			 
    PWMManager01_45_configCaso2(pwmDependiente,pwmPeriodoCambiando,periodo); 
  }
  
  //Es el caso3
  //caso3 
  else
    PWMManager01_45_configCaso3(pwmDependiente,periodoDependiente,pwmPeriodoCambiando,periodo);  
  
  PWM45_actualizarPotencia(getPotencia(&pwm45));
  PWM01_actualizarPotencia(getPotencia(&pwm01));
  return 0;
}


/*
** ===================================================================
**     Method      :  PWMHard23_setDuty 
**    Description : Setear duty del PWMHard23
** ===================================================================
*/
static void PWM01_defConstructor(void * self,va_list * args){
  PWM_Construct(self,va_arg(*args,TConfPWM *));
  CONTROLADOR_PWM_INIT(0,1);
  													 
  
  #ifndef _NMODRR
    setReg8Bits(MODRR, 2);  //cablear al puerto T
    setReg8Bits(DDRT, 2); 
  #endif
  
  setReg8Bits(DDRP, 2);
}
/*
** ===================================================================
**     Method      :  PWM01_actualizarPotencia 
**    Description : Setear duty del PWM45 sin guardarlo
** ===================================================================
*/
static void PWM01_actualizarPotencia(uint duty){  
  if(PWME_PWME1){		 /* PWM?*/    
    PWMHard_setDuty(RefPWM01,duty);
  }
  else{
    if(duty==0)
      #ifndef _NMODRR 
      clrReg8Bits(PTT, 2);               /* PTT1=0 */
      #else
      clrReg8Bits(PTP, 2);               /* PTP1=0 */
      #endif
    else
      #ifndef _NMODRR 
      setReg8Bits(PTT, 2);               /* PTT1=1 */ 
      #else
      setReg8Bits(PTP, 2);               /* PTP1=1 */ 
      #endif     
  }
}
/*
** ===================================================================
**    Method      :  PWM01_setDuty 
**    Description : Setear duty del PWM01
** ===================================================================
*/
static void PWM01_setDuty(struct PWM01* self,uint duty){
  PWM01_actualizarPotencia(duty);
  Salida_setPotencia(self,duty);
}

/*
** ===================================================================
**     Method      :  PWM01_setTipoSalida 
**    Description : Setear el PWM01 en on-off o en PID
** ===================================================================
*/
void PWM01_setTipoSalida(struct PWM01* self,TipoSalida onoff){
    PWME_PWME1 = (onoff==SALIDA_ONOFF)?0:1;
}

/*
** ===================================================================
**     Method      :  PWM01_setTipoSalida 
**    Description : verifica si el PWM01 esta en on-off o en proporcional
** ===================================================================
*/
TipoSalida PWM01_tipoSalida(struct PWM01* self){
  return (PWME_PWME1)?SALIDA_PROPORCIONAL:SALIDA_ONOFF;
}



static void PWM45_defConstructor(void * self,va_list * args){
  PWM_Construct(self,va_arg(*args,TConfPWM *));
  
  CONTROLADOR_PWM_INIT(4,5);
  
  setReg8Bits(DDRP, 32);
}

/*
** ===================================================================
**     Method      :  PWM45_actualizarPotencia 
**    Description : Setear duty del PWM45 sin guardarlo
** ===================================================================
*/
static void PWM45_actualizarPotencia(uint duty){
  
  if(PWME_PWME5){		 /* PWM?*/    
     asm {														 
      LDY    PWMPER45				 
      LDD    duty										 
      EMUL													 
      ADDD   #500										 
      EXG    D,Y										 
      ADCB   #0											 
      ADCA   #0											 
      LDX    #1000									 
      EXG    D,Y										 
      EDIV													 
      STY    PWMDTY45				
    }
  }
  else{
    if(duty==0)
      clrReg8Bits(PTP, 8);               
    else
      setReg8Bits(PTP, 8);                
  }
}
/*
** ===================================================================
**     Method      :  PWM45_setDuty 
**    Description : Setear duty del PWM45
** ===================================================================
*/
void PWM45_setDuty(struct PWM45* self,uint duty){
  
  PWM45_actualizarPotencia(duty);
  Salida_setPotencia(self,duty);
}

/*
** ===================================================================
**     Method      :  PWM45_setTipoSalida 
**    Description : Setear el PWM45 en on-off o en PID
** ===================================================================
*/
void PWM45_setTipoSalida(struct PWM45* self,TipoSalida onoff){
    PWME_PWME5 = (onoff==SALIDA_ONOFF)?0:1;
}

/*
** ===================================================================
**     Method      :  PWM45_setTipoSalida 
**    Description : verifica si el PWM45 esta en on-off o en proporcional
** ===================================================================
*/
TipoSalida PWM45_tipoSalida(struct PWM45* self){
  return (PWME_PWME5)?SALIDA_PROPORCIONAL:SALIDA_ONOFF;
}






