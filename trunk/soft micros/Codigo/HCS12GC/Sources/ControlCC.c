/*  MODULE Control Colada Caliente: Desciende de CONTROL*/
#include "stddef.h"
#include "Selftune.h"
#include "Mydefines.h"
#include "funciones.h"
#include "IFsh10.h"
#include "Timer.h"
#include "Sensores.h"
#include "ControlCC.h"

/*  Herencia  */
void CNTR_OnInit(void);
void CNTR_ActProcVal(int,byte);
void CNTR_setPotActual(int val,byte num_cont);

/*            */
const byte TimeCC[]={
  5,10,15,20  
};

#pragma CONST_SEG PARAMETERS_PAGE   
  volatile const int PotenciaSS=500;
  volatile const int ConstanteSS=100; /*  si no es 0 Determina el momento de corte*/
  volatile const T_Tiempos_Colada eTieSS;/*si ConstanteSS es cero, determina el momento de corte*/
  volatile const int PotCritTime;
  volatile const int PotCritica;
  volatile const int PotCicleTime;
  volatile const int PotRelax;
  volatile const int RampToSP[CANTIDAD_SAL_CONTROL];
#pragma CONST_SEG DEFAULT

static bool bIsSoftStart[CANTIDAD_SAL_CONTROL]; 
static bool bPotRelax[CANTIDAD_SAL_CONTROL];
static int SP[CANTIDAD_SAL_CONTROL];  // Lo limito por RampToSP
static T_Timer * pTimerRmpSP[CANTIDAD_SAL_CONTROL];

static void CC_OnTimeSS(void);
void CC_OnCriticalPotTime(byte chan);
void CC_OnRelaxPotTime(byte chan);
void CC_OnSP_Inc1(byte num_cont);

/*  Controla que la potencia no este en un % alto durante un tiempo determinado*/
static void CC_ControlPot(int duty,byte chan);

void CC_OnInit(int (*pf_getValProc) (byte)){
byte i;
bool bOnTime=FALSE;
  
  CNTR_OnInit();
    
  
  for(i=0;i<CANTIDAD_SAL_CONTROL;i++){
    CNTR_setIntSP(get_SP(i),i);
    if (((*pf_getValProc)(i)<CNTR_getIntSP(i)/2) && PotenciaSS!=0){
      if(ConstanteSS==0)
        bOnTime=TRUE;   
      bIsSoftStart[i]= TRUE;
    }else
      bIsSoftStart[i]= FALSE;
    
  }
  if(bOnTime)
    TimerRun(60000*TimeCC[eTieSS],NULL,UNICO_SET,CC_OnTimeSS);
  
}


void CC_ActProcesValue(int vp, byte result,byte chan){

  if((result==ERR_OF || result==ERR_UF) && get_SalControl(chan)!=_MAN)
    set_SalControl(_MAN,chan);
  CNTR_ActProcVal(vp,chan);
  if(bIsSoftStart[chan] && ConstanteSS!=0){
    if( ((long)vp*100)  > ((long)CNTR_getIntSP(chan)*ConstanteSS) )
      bIsSoftStart[chan]=FALSE;  
  }
  
}


static void CC_OnTimeSS(void){
  byte i;
    
  for(i=0;i<CANTIDAD_SAL_CONTROL;i++)  
    bIsSoftStart[i]=FALSE;
  Timer_Terminate(CC_OnTimeSS);
}

void CC_DutyControl(int * duty,byte chan){
int dutytmp;
  
  if(!CNTR_isConnected(0)){
    CNTR_setPotActual(0,chan);
    *duty = 0;
    return;  
  }
  if (CNTR_getModSal(chan) == _MAN){
    *duty =dutytmp = get_PotenciaManual(chan); 
    CNTR_setPotActual(*duty,chan);
    CC_ControlPot(*duty,chan);
    return;
  }
//Calculo del duty
        if (cntrl_es_pid(chan)){  //Estoy en PID
          dutytmp = duty_prop(CNTR_getValControl(chan), 
                              CNTR_getHisteresis(chan),
															get_PotenciaInf(chan),
															CC_getPotenciaSup(chan)
                              );
                              
    		  if (CNTR_getModSal(chan) != _REF)
    		    CC_ControlPot(dutytmp,chan);
        }
		    
        else{
          if (CNTR_getModSal(chan) == _REF)
		          dutytmp = 1000-*duty;
            else  
              dutytmp = *duty;
          dutytmp = duty_onoff(dutytmp,  //o en onoff
                            CNTR_getValControl(chan), 
                            CNTR_getHisteresis(chan)  
                           );
        }
//Valor de la salida
		  if (CNTR_getModSal(chan) == _REF)
		    dutytmp = 1000-dutytmp;

//seteo el duty de salida
      *duty = dutytmp;
      CNTR_setPotActual(*duty,chan);
      
}

/*  Limite de Potencia Superior en Colada Caliente*/
int CC_getPotenciaSup(byte num_cont)
{
  if(bIsSoftStart[num_cont])
    return PotenciaSS;
  if(bPotRelax[num_cont])
    return PotRelax;
  return get_PotenciaSup(num_cont);
}

/*  Indica si estoy haciendo SoftStart  */
bool CC_isSoftStart(byte num_cont){
  return bIsSoftStart[num_cont];
}

/*  Controla que la potencia no este en 100% durante un tiempo determinado*/

static void CC_ControlPot(int duty,byte chan)
{
  
  static T_Timer * pTimer[CANTIDAD_SAL_CONTROL];
  
  if(PotCicleTime!=0 && duty>= PotCritica){
    if(!Timer_Contain(pTimer[chan])) 
      pTimer[chan]=RefTimer_Run(1000*PotCritTime,UNICO_SET,COUNT_NORMAL,CC_OnCriticalPotTime, chan);
  }else
    Timer_Destructor(&pTimer[chan]);
}

//T_Timer * pTimer_Relax[CANTIDAD_SAL_CONTROL];

void CC_OnCriticalPotTime(byte num_cont)
{
  bPotRelax[num_cont]=TRUE;
  
  (void)RefTimer_Run(1000*(PotCicleTime-PotCritTime),UNICO_SET,COUNT_NORMAL,CC_OnRelaxPotTime, num_cont);
  
}

void CC_OnRelaxPotTime(byte num_cont){
  bPotRelax[num_cont]=FALSE;  
}

/*  Seteo el SP interno limitado por ramp to SP */

byte CC_setIntSP(int val,byte num_cont){
  SP[num_cont]=val;
  if(!pTimerRmpSP[num_cont] && SP[num_cont]>SENSOR_getProcVal(num_cont)){
 //   float min_inc= SENSORES_getScaled(0.1);		// min_inc(minimo incremento)=una decima de grado cuanto incremento es al VP
    long refresh_time= 60*1000*10/RampToSP[num_cont]; // El 10 lo pasa a decimas de unidad por minuto y el 1000 a ms 
    pTimerRmpSP[num_cont]= RefTimer_Run(refresh_time,CONTINUO_SET,COUNT_NORMAL,CC_OnSP_Inc1, num_cont);		//refresco cada RAMP_TO_SP_REFERSH_TIME ms
    if(!pTimerRmpSP[num_cont]){
      CNTR_setIntSP(val,num_cont);
      return ERR_BUSY;  
    }
  }
}

void CC_OnSP_Inc1(byte num_cont){
  
  //CNTR_setIntSP();
}

/*  Configuracion */

/*  Limite Superior de Potencia de Salida en Soft Start */
int CC_getPotencia(byte num_cont){
  return PotenciaSS;
}

byte CC_setPotencia(int val,byte num_cont){
  return EscribirWord((word)&PotenciaSS,val);
}

int CC_getLimInfPotencia(byte num_cont){
  return get_PotenciaInf(0);
}
int CC_getLimSupPotencia(void){
  return get_PotenciaSup(0);
}

/*  Constante que indica el corte en Soft Start */
int CC_getConstanteCorte(byte num_cont){
  return ConstanteSS;
}

byte CC_setConstanteCorte(int val,byte num_cont){
  return EscribirWord((word)&ConstanteSS,val);
}

int CC_getLimInfConstanteCorte(byte num_cont){
  return 0;
}
int CC_getLimSupConstanteCorte(void){
  return MAX_NUMBER_DISP;
}


/*  Tiempo en Soft Start  en caso de constante 0*/
int CC_getTiempoColada(byte num_cont){
  return eTieSS;
}

byte CC_setTiempoColada(int val,byte num_cont){
  return EscribirByte((word)&eTieSS,val);
}

int CC_getLimInfTiempoColada(byte num_cont){
  return 0;
}

int CC_getLimSupTiempoColada(void){
  return MAX_VALUE_TIEMPO_COLADA;
}

/*  Ciclo en Segundos de Potencia Critica y Potencia de Relajo*/
int CC_getCicleTime(byte num_cont){
  return  IFsh10_getWord((word)&PotCicleTime);
}

byte CC_setCicleTime(int val,byte num_cont){
  return EscribirWord((word)&PotCicleTime,val);
}

int CC_getLimInfCicleTime(byte num_cont){
  return 0;
}
int CC_getLimSupCicleTime(void){
  return MAX_NUMBER_DISP;
}

/* Tiempo en Segundos en que se puede estar en potencia critica*/
int CC_getCriticalPotTime(byte num_cont){
  return  IFsh10_getWord((word)&PotCritTime);
}

byte CC_setCriticalPotTime(int val,byte num_cont){
  return EscribirWord((word)&PotCritTime,val);
}

int CC_getLimInfCriticalPotTime(byte num_cont){
  return 1;
}
int CC_getLimSupCriticalPotTime(byte num_cont){
  return CC_getCicleTime(num_cont);
}

/*  Limite Inferior de Potencia Critica */
int CC_getCriticalPot(byte num_cont){
  return  IFsh10_getWord((word)&PotCritica);
}

byte CC_setCriticalPot(int val,byte num_cont){
  return EscribirWord((word)&PotCritica,val);
}

int CC_getLimInfCriticalPot(byte num_cont){
  return get_PotenciaInf(0);
}
int CC_getLimSupCriticalPot(byte num_cont){
  return get_PotenciaSup(0);
}

/*  Limite Superior de la Potencia de Relajo */
int CC_getRelaxPot(byte num_cont){
  return  PotRelax;
}

byte CC_setRelaxPot(int val,byte num_cont){
  return EscribirWord((word)&PotRelax,val);
}

int CC_getLimInfRelaxPot(byte num_cont){
  return get_PotenciaInf(0);
}
int CC_getLimSupRelaxPot(byte num_cont){
  return CC_getCriticalPot(0);
} 

