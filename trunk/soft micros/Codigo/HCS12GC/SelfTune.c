/*MODULE: Self Tune (Auto Sintonia):
  Desciende de Control Comun o de Colada caliente segun Corresponda
*/
#include "funciones.h"
#include "Mydefines.h"
#include "cnfbox.h"
#include "boxes.h"
#include "IFsh10.h"
#include "PWM.h"
#include "ValvulaP.h"
#ifdef _COLADA_CALIENTE
  #include "ControlCC.h"
#else
  #include "Control.h"
#endif
#include "Timer.h"
#include "SelfTune.h"
#include "Sensores.h" 

/*  Herencia  */
extern const byte Sal_Control[];
void CNTR_setIntegral(int,byte); 
void CNTR_setDerivada(int,byte); 
/**/

#pragma CONST_SEG PARAMETERS_PAGE
volatile const TSelfTune eSelfTune[CANTIDAD_SAL_CONTROL];
volatile const int SelfTuneSP[CANTIDAD_SAL_CONTROL];  // Set Point de Auto Sintonia
volatile const int SelfTuneIn[CANTIDAD_SAL_CONTROL];  // Integral de Auto Sintonia
volatile const int SelfTuneDr[CANTIDAD_SAL_CONTROL];  // Derivada de Auto Sintonia
volatile const int SelfTuneAb[CANTIDAD_SAL_CONTROL];  // Ancho de banda de Auto Sintonia 
#pragma CONST_SEG DEFAULT

T_ST_State ST_State[CANTIDAD_SAL_CONTROL];
dword St_Counter[CANTIDAD_SAL_CONTROL];
byte St_Step[CANTIDAD_SAL_CONTROL];
int prev_val[CANTIDAD_SAL_CONTROL];
int St_val_max[CANTIDAD_SAL_CONTROL];
int St_val_min[CANTIDAD_SAL_CONTROL];
int St_time_cnt[CANTIDAD_SAL_CONTROL];
int St_abrt_cnt[CANTIDAD_SAL_CONTROL];

void SelfTuneControl(int * duty,byte num_cntrl);
void CST_setState(T_ST_State state,byte num_cntrl);

/*
** ===================================================================
**     Method      :  CST_OnInit
**
**     Description : Inicializa el control con self tune
**     Parameters  : * pf_getValProc - Puntero a funcion para obtener los valores dela variables
**                   num_cntrl  _ Numero de control
**     Returns     : None
**         ---    
** ===================================================================
*/
void CST_OnInit( int (*pf_getValProc) (byte)){
byte i;
#ifdef _COLADA_CALIENTE
  CC_OnInit(SENSOR_getProcVal);
#else
  CNTR_OnInit();
#endif  
  for(i=0;i<CANTIDAD_SAL_CONTROL;i++){
    if(eSelfTune[i]==ST_AUTO)
      if((*pf_getValProc)(i)<CNTR_getIntSP(i)/2){
         #ifdef _COLADA_CALIENTE
          CST_setState(ST_STATE_WAIT_SOFT_START,i);  
          CNTR_setIntegral(SelfTuneIn[i],i);
          CNTR_setDerivada(SelfTuneDr[i],i);
          CNTR_setHisteresis(SelfTuneAb[i],i);
         #else
          CST_setState(ST_STATE_RUNNING,i);
         #endif
      }
  }
}						
  

/*																				
** ===================================================================
**     Method      :  ST_DutyControl 
**
**     Description : Calcula el duty de salida
**     Parameters  : * pduty - Puntero al duty
**                   num_cntrl  _ Numero de control
**     Returns     : None
**         ---    
** ===================================================================
*/

void CST_DutyControl(int * pduty,byte num_cont){
  if (!get_SelfTun(num_cont)== ST_ON){//no estoy haciendo selftune ?
    SelfTuneControl(pduty,num_cont);	 	//obtengo duty
    return;
  }
  #ifdef _COLADA_CALIENTE
    CC_DutyControl(pduty,num_cont);
  #else
    DutyControl(pduty,num_cont);
  #endif
  
  #ifdef _COLADA_CALIENTE
  if(CST_getState(num_cont)==ST_STATE_WAIT_SOFT_START)
    if(!CC_isSoftStart(num_cont))
      CST_setState(ST_STATE_RUNNING,num_cont);
  #endif
}

/*Incrementa el Tiempo de ST transcurrido*/
void On_StCountInc(word a){
byte i;	 
	 for(i=0;i<NUM_SALIDAS;i++)
    if (CST_getState(i)==ST_STATE_RUNNING)
		  St_Counter[i]++;    
}
/*
** ===================================================================
**     Method      :  SelfTuneControl 
**
**     Description :
**     Parameters  : vx
**                   sp
**									 duty
**                   num_cntrl  _ Numero de canal
**     Returns     : None
**         ---    
** ===================================================================
*/
void SelfTuneControl(int * duty,byte num_cntrl){
int Pr;
int ctrl_sp=get_SP(num_cntrl);
int sp = (SelfTuneSP[num_cntrl]==0)?ctrl_sp:ctrl_sp-ctrl_sp/SelfTuneSP[num_cntrl];   
int vx = SENSOR_getProcVal(num_cntrl);
int kint=SelfTuneIn[CANTIDAD_SAL_CONTROL];  // Integral de Auto Sintonia
int kder=SelfTuneDr[CANTIDAD_SAL_CONTROL];  // Derivada de Auto Sintonia
int ab=SelfTuneAb[CANTIDAD_SAL_CONTROL];  // Ancho de banda de Auto Sintonia 

// primero hago el control onoff


        Pr = proporcional (vx,								    //calculo señal de error
                           0,
													 sp
													 );
  
        *duty =  duty_onoff(*duty,    //hago accion onoff
                            Pr, 
                            ab 
                            );

        #ifdef _VP 
        VP_SetDuty(*duty);
        #else
        set_salida_onoff(*duty,Sal_Control[num_cntrl]);								  //pongo salida
				#endif
				
	      if (St_abrt_cnt[num_cntrl]<St_abrt_MAX)
          St_abrt_cnt[num_cntrl]++;
	      else 
	        St_Step[num_cntrl]=6;                              //veo si me pase y pongo error



//	      EscribirParametro(R_Stn,St_Err);

	      switch(St_Step[num_cntrl]){							          					//estoy en el paso cero que es comienzo abajo. 
        case 0: if (vx>= (sp+ab/2)){    //Si subo pongo paso 1
                St_Step[num_cntrl]++;
                St_Counter[num_cntrl]=0;														//reinicio
								St_abrt_cnt[num_cntrl]=0;
                #ifdef jony_28_06
                set_MainText("St 1");
                #endif

                }
            break;
        case 1: if (vx< (sp-ab/2)){    //estoy en el paso 1 que puede ser comienzo arriba
                St_Step[num_cntrl]++;														    //si bajo, pongo paso 2
                #ifdef jony_28_06
                set_MainText("St 2");
                #endif
       			    St_Counter[num_cntrl]=0;
								St_abrt_cnt[num_cntrl]=0;
                prev_val[num_cntrl] = vx;                     //e inicio detector de minima
              //  St_time_cnt = 0;                         		//y cuando guardo min reseteo cnt de t
                }
      			break;
        case 2:// St_time_cnt++;                              //estoy contando tiempo
                if (vx < prev_val[num_cntrl])
                prev_val[num_cntrl] = vx;    								  //nuevo minimo
							//	St_time_cnt =0;                             //y nuevo com de cuenta
                if (vx > (sp+ab/2)){		//si subo voy a paso 3
                St_Step[num_cntrl]++;                             
                #ifdef jony_28_06
                set_MainText("St 3");
                #endif
                St_Counter[num_cntrl]=0;
								St_abrt_cnt[num_cntrl]=0;
                St_val_min[num_cntrl] = prev_val[num_cntrl];                      //pero guardo minimo
                }
      				break;
	      case 3:// St_time_cnt++;                              //sigo contando tiempo 
                if (vx > prev_val[num_cntrl])									//y busco maximo
                prev_val[num_cntrl] = vx;    								  //nuevo maximo
  	            if (vx<(sp-ab/2)){	    //espero bajar
                St_Step[num_cntrl]++;
                #ifdef jony_28_06
                set_MainText("St 4");
                #endif
               // St_Counter[num_cntrl]=0;
								St_abrt_cnt[num_cntrl]=0;
                St_val_max[num_cntrl] = prev_val[num_cntrl];                      //pero guardo maximo
  	            }
	            break;
        case 4: //St_time_cnt++;                              //baje, sigo contando
                if (vx<prev_val[num_cntrl])										//busco minimo
                    prev_val[num_cntrl] = vx;  
                else{
                St_Step[num_cntrl]++;
                #ifdef jony_28_06
                set_MainText("St 5");
                #endif
               // St_Counter[num_cntrl]=0;
								St_abrt_cnt[num_cntrl]=0;
                }
							 break;
        case 5: 
                set_H_Control((int)((St_val_max-St_val_min)*3)/2,num_cntrl);
	              set_integral(St_Counter[num_cntrl]/10,num_cntrl);
	              set_derivada((St_Counter[num_cntrl]/10),num_cntrl);
	              if(get_SelfTun(num_cntrl)==ST_ON)
	                set_SelfTun(ST_OFF,num_cntrl);
                Timer_Terminate(On_StCountInc);
                set_MainText("");
                     
	             
	             break; 

	      case 6:
                set_H_Control(ab,num_cntrl);
	              set_integral(kint,num_cntrl);
	              set_derivada(kder,num_cntrl);
	              if(get_SelfTun(num_cntrl)==ST_ON)
	                set_SelfTun(ST_OFF,num_cntrl);               
                Timer_Terminate(On_StCountInc);
                set_MainText("St E");

							 break;


   		}
}


// Estado del Self Tune
T_ST_State CST_getState(byte num_cntrl){
  return ST_State[num_cntrl];
}

void CST_setState(T_ST_State state,byte num_cntrl){
  if(state==ST_STATE_RUNNING){
    St_Step[num_cntrl]=0;
    St_Counter[num_cntrl]=0,
    TimerRun(100,NULL,CONTINUO_SET,On_StCountInc);
    Cntr_SetearOnOff(CNTR_ONOFF,num_cntrl); //seteo salida en ON-OFF
    set_MainText("St 0");
    ST_State[num_cntrl]=state;
  }else if(state==ST_STATE_OFF){
    set_MainText("");
    Cntr_SetearOnOff(get_TipoControl(num_cntrl),num_cntrl); //seteo salida en ON-OFF
  }
}

//////////////// Funciones de seteo y obtencion de variables  ////////////
//Tipo de SelfTune
int get_SelfTun(byte num_ctrl){
  return eSelfTune[num_ctrl];
}

byte set_SelfTun(int st,byte num_ctrl){
  byte err;
  if(CNTR_getModSal(num_ctrl)==_MAN)
    return ERR_BUSY;
  err=EscribirByte((word)&eSelfTune[num_ctrl],st);
  if(!err){
    if(st==ST_ON)  
      CST_setState(ST_STATE_RUNNING,num_ctrl);
    else if(st==ST_OFF)
      CST_setState(ST_STATE_OFF,num_ctrl);   
  }
  return err;		 
}

int get_LimSup_SelfTun(void){
  return ST_MAX_VALUE;  
};

//Set Point de SelfTune
//Ancho de Banda de SelfTune
//Integral de SelfTune
//Derivada de SelfTune
