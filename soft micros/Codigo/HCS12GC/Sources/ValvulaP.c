#include <stdlib.h>
#include "PE_Types.h"
#include "Cpu.h"
#include "Mydefines.h"
#include "Timer.h"
#include "cnfbox.h"
#include "Grabacion.h"
#include "PWM.h"
#include "IFsh10.h"
#include "ValvulaP.h"

void VP_OnActualizacion(word diferencia);
void VP_OnInitClose(void);
void close(void);								 

#pragma CONST_SEG PARAMETERS_PAGE
volatile const int VP_Time=10;
volatile const int VP_DeadBand=1;
#pragma CONST_SEG DEFAULT

typedef enum{
  VP_OPEN,
  VP_CLOSE,
  VP_STOP
}T_VP_State;

static T_VP_State vp_state;
static int set_duty;
static word ciclo;
static char times;

void VP_Init(void){
  PWM_Disable(VP_SALIDA_1);
  PWM_Disable(VP_SALIDA_2); //deshabilito salidas en modo PWM
  #ifndef debug
  close(); // ordeno cerrar la valvula
  times= ((long)VP_Time*1000*10*VP_CLOSE_FACTOR)/65535; //el 10 lo pasa a centecimas de s. times es veces de a 6 seg
  TimerRun(6554+CNTR_TIME_DISCONECT,NULL,UNICO_SET,VP_OnInitClose);
  #else
  TimerRun(20,NULL,UNICO_SET,VP_OnActualizacion);
  #endif
}


void close(void){
  PWM_ClrValue(VP_SALIDA_1);
  PWM_SetValue(VP_SALIDA_2);
  vp_state = VP_CLOSE;
}
void open(void){
  PWM_ClrValue(VP_SALIDA_2);
  PWM_SetValue(VP_SALIDA_1);
  vp_state = VP_OPEN;  
}

void stop(void){
  PWM_ClrValue(VP_SALIDA_1);
  PWM_ClrValue(VP_SALIDA_2);
  vp_state = VP_STOP;  
}

bool is_close(void){
  return vp_state == VP_CLOSE;
}
bool is_open(void){
  return vp_state == VP_OPEN;
}


void VP_SetDuty(int duty){
  set_duty=duty;
}

/*byte VP_setTime(int Time,byte s){
  VP_Time = Time;  
  return ERR_OK; 
}					

*/

int VP_getTime(void){
return VP_Time;  
}

int VP_getDeadBand(void){
return  VP_DeadBand; 
}

void VP_OnInitClose(void){
  if((--times)>0)
    TimerRun(6554,NULL,UNICO_SET,VP_OnInitClose);  
  else {
    stop();	 //valvula quieta
    TimerRun(20,NULL,UNICO_SET,VP_OnActualizacion);
  }
}
void VP_OnActualizacion(word diferencia){
bool dif_positiva;
long Time_set_duty,time_dif;
static long VP_tiempo;
static long time_duty_out_sim;
long max_time;  
  
  
  if(is_open())
    time_duty_out_sim+=diferencia+VP_tiempo;
  else if(is_close())
    time_duty_out_sim-=diferencia+VP_tiempo;
  
  if(time_duty_out_sim<0)time_duty_out_sim=0;
  max_time=(long)1000*VP_Time;
  if(time_duty_out_sim>max_time)time_duty_out_sim=max_time; 
  

  Time_set_duty=((long)set_duty)*VP_Time;
  dif_positiva=Time_set_duty>time_duty_out_sim;
  time_dif=(dif_positiva)?Time_set_duty-time_duty_out_sim:time_duty_out_sim-Time_set_duty;  
  
  if(time_dif &&((time_dif)>(VP_DeadBand*VP_Time))){
    VP_tiempo=time_dif; 
		if(time_dif-VP_ACT_TIME>40){			 //dejo 40 ms para despues asi me aseguro no pasarme por ingesar poco tiempo
		  VP_tiempo=VP_ACT_TIME; 
		  TimerRun(VP_ACT_TIME,NULL,UNICO_SET,&VP_OnActualizacion);  
		} else{
		  VP_tiempo=time_dif; 
	    TimerRun((word)VP_tiempo,NULL,UNICO_SET,&VP_OnActualizacion);	
		}
		if(dif_positiva)
      open();
    else 
      close();			
  }else{
    stop();	 //valvula quieta 
    TimerRun(VP_ACT_TIME,NULL,UNICO_SET,&VP_OnActualizacion); 
  }			
}

    
/**************** FUNCIONES GET & SET *******************************/    
/*  Tiempo  */
int get_VpTime(byte a){
  return VP_Time;
}

byte set_VpTime(int val, byte a){
  return EscribirWord((word)&VP_Time,val);
}

int get_LimInf_VpTime(byte a){
  return 1;
}

/*  Banda Muerta */
int get_VpDeadB(byte a){
  return VP_DeadBand;
}

byte set_VpDeadB(int val,byte a){
  return EscribirWord((word)&VP_DeadBand,val);
}

int get_LimInf_VpDeadB(byte a){
  return 0;
}


