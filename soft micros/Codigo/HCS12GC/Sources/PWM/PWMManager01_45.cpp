
#include "PWMManager01_45.hpp"
#include "PWMHard.hpp"

#pragma CONST_SEG PARAMETERS_PAGE
volatile const TConfPWM pwmconf01={0};
volatile const TConfPWM pwmconf45={0};
#pragma CONST_SEG DEFAULT
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

PWMManager01_45::PWMHard01* PWMManager01_45::pwmHard01=NULL;

PWMManager01_45::PWMHard45* PWMManager01_45::pwmHard45=NULL; 

void PWMManager01_45::PWMHard01::PWMHard01(struct ManejadorMemoria &_manejadorMemoria,const TConfPWM &_conf): PWMHard(_manejadorMemoria,_conf){
  
  CONTROLADOR_PWM_INIT(0,1);
  													 
  
  #ifdef __MODRR
    setReg8Bits(MODRR, 8);//2  //cablear al puerto T
    setReg8Bits(DDRT, 8);//2 
  #endif
  
  setReg8Bits(DDRP, 8); //2
}

void PWMManager01_45::PWMHard45::PWMHard45(struct ManejadorMemoria &_manejadorMemoria,const TConfPWM &_conf):PWMHard(_manejadorMemoria,_conf){
 
 
 CONTROLADOR_PWM_INIT(4,5);
  
  setReg8Bits(DDRP, 32);
}

void PWMManager01_45::PWMHard01::setPotenciaGuardada() {
 unsigned int potencia = getPotencia();
 if(PWME_PWME1){		 /* PWM?*/    
    setDuty(RefPWM01,potencia);
  }
  else{
    if(potencia==0)
      #ifdef __MODRR
      clrReg8Bits(PTT, 8);//2              /* PTT3=0 */
      #else
      clrReg8Bits(PTP, 8);//2 
      #endif
    else
      #ifdef __MODRR
      setReg8Bits(PTT, 8);//2            /* PTT3=1 */
      #else
      setReg8Bits(PTP, 8);//2
      #endif 
  }
}


void PWMManager01_45::PWMHard45::setPotenciaGuardada() {
  unsigned int potencia = getPotencia();
  if(PWME_PWME5){		 /* PWM?*/    
    setDuty(RefPWM45,potencia);
  }
  else{
    if(potencia==0)
      clrReg8Bits(PTP, 32);               
    else
      setReg8Bits(PTP, 32);               
  }
}

TipoSalida PWMManager01_45::PWMHard01::getTipoSalida() {
  return (PWME_PWME1)?SALIDA_PROPORCIONAL:SALIDA_ONOFF;
}

TipoSalida PWMManager01_45::PWMHard45::getTipoSalida() {
  return (PWME_PWME5)?SALIDA_PROPORCIONAL:SALIDA_ONOFF;
}

void PWMManager01_45::PWMHard01::setTipoSalida(TipoSalida tipoSalida) {
  PWME_PWME1 = (tipoSalida==SALIDA_ONOFF)?0:1;
}

void PWMManager01_45::PWMHard45::setTipoSalida(TipoSalida tipoSalida) {
  PWME_PWME5 = (tipoSalida==SALIDA_ONOFF)?0:1;
}

PWMHard* PWMManager01_45::get01(ManejadorMemoria &_manejadorMemoria,TConfPWM &_conf) {
  if( !pwmHard01)
    pwmHard01 = new PWMHard01(_manejadorMemoria,_conf); 
  return pwmHard01; 

}

PWMHard* PWMManager01_45::get45(ManejadorMemoria &_manejadorMemoria,TConfPWM &_conf) {
  if( !pwmHard45)
    pwmHard45 = new PWMHard45(_manejadorMemoria,_conf); 
  return pwmHard45; 
}

bool PWMManager01_45::PWMHard01:: getEstadoSalida (){
  return PTP_PTP1;
}

bool PWMManager01_45::PWMHard45:: getEstadoSalida (){
  return PTP_PTP3;
}

unsigned char PWMManager01_45::PWMHard01::setPeriodo( TPeriod periodo) {
  TError err;
  if(periodo<0 || periodo>PWM_MAX_VALUE_PERIODS)
    return ERR_VALUE; //error
  err= setPeriodoConfiguracion(periodo);
  if(err)
    return err;
  return PWMManager01_45_setPeriodo(this, periodo);  
   
}


unsigned char PWMManager01_45::PWMHard45::setPeriodo(TPeriod periodo) {
  TError err;
  if(periodo<0 || periodo>PWM_MAX_VALUE_PERIODS)
    return ERR_VALUE; //error
  err= setPeriodoConfiguracion(periodo);
  if(err)
    return err;
 return PWMManager01_45_setPeriodo(this, periodo);   
}


TError PWMManager01_45::PWMManager01_45_setPeriodo( PWM * self,TPeriod periodo){
  PWM* pwmDependienteObj;
  PWMHard::ReferenciaPWM pwmPeriodoCambiando;
  PWMHard::ReferenciaPWM pwmDependiente;
  TPeriod periodoDependiente;
  TError err;
  
  
  if(self == pwmHard01){
    pwmDependiente = PWMHard::RefPWM45;
    pwmPeriodoCambiando = PWMHard::RefPWM01; 
    pwmDependienteObj=self;//pwmHard45;
    
  }else{																			
    pwmDependiente = PWMHard::RefPWM01;
    pwmPeriodoCambiando = PWMHard::RefPWM45;
    pwmDependienteObj=self;//pwmHard01;
  }
  
  periodoDependiente = pwmDependienteObj->getPeriodo();
  
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
  
  PWM45_actualizarPotencia(/*pwmHard45->getPotencia()*/self->getPotencia());
  PWM01_actualizarPotencia(/*pwmHard01->getPotencia()*/self->getPotencia());
  return 0;
}



void PWMManager01_45::PWMManager01_45_configCaso1(PWMHard::ReferenciaPWM pwmPeriodo50,PWMHard::ReferenciaPWM pwmPeriodo05){
  PWMPRCLK_PCKA=7;   /*Set Prescaler*/
  PWMSCLA = 112; 		 /*Set Scaler*/
  PWMHard::setPeriodoHard(pwmPeriodo50,PERIODO_50S_CASO1);
  PWMHard::setPeriodoHard(pwmPeriodo05,PERIODO_05S_CASO1); 
  PWMHard::noEscalar(pwmPeriodo05); 
}


void PWMManager01_45::PWMManager01_45_configCaso2(PWMHard::ReferenciaPWM pwmPeriodo50,PWMHard::ReferenciaPWM pwmPeriodoNo05,TPeriod periodoNo05){
  bool escalar;
  PWMPRCLK_PCKA=6;   /*Set Prescaler*/
  PWMSCLA = 125; 		 /*Set Scaler*/
  
  PWMHard::setPeriodoHard(pwmPeriodo50,PERIODO_50S_CASO1);
  PWMHard::setPeriodoHard(pwmPeriodoNo05,periodosCaso2[periodoNo05]); 
  PWMHard::noEscalar(pwmPeriodo50);
  
  if(escaladoresCaso2_3[periodoNo05])
    PWMHard::escalar(pwmPeriodoNo05);
  else
    PWMHard::noEscalar(pwmPeriodoNo05);
}

void PWMManager01_45::PWMManager01_45_configCaso3(PWMHard::ReferenciaPWM pwmPeriodo1,TPeriod periodo1,PWMHard::ReferenciaPWM pwmPeriodo2,TPeriod periodo2){
  bool escalar;
  PWMPRCLK_PCKA=6;   /*Set Prescaler*/
  PWMSCLA = 125; 		 /*Set Scaler*/ 
  
  PWMHard::setPeriodoHard(pwmPeriodo1,periodosCaso3[periodo1]);
  PWMHard::setPeriodoHard(pwmPeriodo2,periodosCaso3[periodo2]); 
  
  // escalar periodo1??
  if(escaladoresCaso2_3[periodo1])
    PWMHard::escalar(pwmPeriodo1); 
  else
    PWMHard::noEscalar(pwmPeriodo1);
  // escalar periodo2??
    if(escaladoresCaso2_3[periodo2])
    PWMHard::escalar(pwmPeriodo2); 
  else
    PWMHard::noEscalar(pwmPeriodo2);
}

static void PWMManager01_45::PWM45_actualizarPotencia(uint duty){
  
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

static void PWMManager01_45::PWM01_actualizarPotencia(uint duty){  
  if(PWME_PWME1){		 /* PWM?*/    
    PWMHard::setDuty(PWMHard::RefPWM01,duty);
  }
  else{
    if(duty==0)
      #ifdef __MODRR 
      clrReg8Bits(PTT, 2);               /* PTT1=0 */
      #else
      clrReg8Bits(PTP, 2);               /* PTP1=0 */
      #endif
    else
      #ifdef __MODRR 
      setReg8Bits(PTT, 2);               /* PTT1=1 */ 
      #else
      setReg8Bits(PTP, 2);               /* PTP1=1 */ 
      #endif     
  }
}