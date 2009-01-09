/* TestControl.c*/
#include "stddef.h"
#include "stdtypes.h"
#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "Object.h"
#include "ClassADC.h"
#include "Grabacion.h"
#include "DiagramaNavegacion.h"
#include "SnsHmi.h"
#include "BoxProp.h"
#include "Sets.h"
#include "Sensores.h"
#include "SensorTPT_Class.h"
#include "RlxMTimer.h"
#include "Adquisidor.h"
#include "AdquisidorHmi.h"
#include "com_events.h"
#include "Terminal.h"
#include "termio.h"
#include "hidef.h"
#include "stdio.h"
#include "FlashBkpEnFlash.h"
#include "Termometro.h"
#include "timer_interrupt.h"
#include "ModBusHmi.h"
#include "BoxPriAdquisidor.h"
#include "AdquisidorSimple.h"
#include "System.h"
#include "dateTimeVista.h"

#define CNTR_TIME_DISCONECT 2000


#pragma CONST_SEG PARAMETERS_PAGE
volatile const ConfiguracionAdquisidorSimple adquisidor_config={
  STPT_DEF_CONF,
  #if CANTIDAD_CANALES>1 
    STPT_DEF_CONF,
      #if CANTIDAD_CANALES>2
        STPT_DEF_CONF,
        #if CANTIDAD_CANALES>3
          STPT_DEF_CONF,
        #endif
      #endif
  #endif
  ADQ_DEFAULT_CONF
};
#pragma CONST_SEG DEFAULT


NEW_FLASH_BKP_EN_FLASH(flash,0x4200);
const struct ManejadorMemoria * pFlash = &flash;

struct AdquisidorSimple adquisidorSimple;


const struct BlockConstBoxPri CBox_Pri={
      &BoxPriAdquisidor,							/* funcion que procesa al box*/
      adquisidorSimple.termometro.sensor,
      &adquisidorSimple.mensajes						
};

void AdquisidorSimple_on1ms(void * adquisidorSimple){
  DpyAndSwitch();
}

void enter_2num(int num , char * str){

  str[0]= num/10+'0';
  str[1]= num%10+'0'; 
}

void  AdquisidorSimple_actualizarTextos(void * self){
  struct AdquisidorSimple * _a=self;
  
  if(Adq_getActualState(&_a->adquisidor)==TRUE){
    _a->mensaje[7]='S';
    _a->mensaje[8]='i'; 
  }else{
    _a->mensaje[7]='n';
    _a->mensaje[8]='o';  
  }
  
  
  if(Adq_isTimeSet(&_a->adquisidor)){
    DATEREC date;
    TIMEREC tiempoRec;
    byte dia,mes;
    int anio,tiempo;
    
    Sys_getDate(&date);
    Sys_getTime(&tiempoRec);
    dia =date.Day;
    mes= date.Month;
    anio= date.Year;
    tiempo = tiempoRec.Hour*100+tiempoRec.Min;   
    
    
    
    enter_2num(dia,&_a->mensaje[17]);
    _a->mensaje[19]= '-';
    enter_2num(mes,&_a->mensaje[20]);
    _a->mensaje[22]= '-';
    enter_2num(anio%100,&_a->mensaje[23]); 
 
    enter_2num(tiempo/100,&_a->mensaje[31]);
    _a->mensaje[33]='.';
    enter_2num(tiempo%100,&_a->mensaje[34]);
    _a->mensaje[36]=' '; 
    _a->mensaje[37]=' ';  
  }else{
    memcpy(&_a->mensaje[17],"no ing.",7);    
    memcpy(&_a->mensaje[31],"no ing.",7);
  }
}

void main (void){

  char tecla; 

  newAlloced(&adquisidorSimple,&AdquisidorSimple,&adquisidor_config,&flash);
  newAlloced(&adquisidorSimple.mensajes,MessageOut);
   															 //012345678901234567890123456789012345678
  strcpy(adquisidorSimple.mensaje,"EStAdo no. FEchA no ing.  horA no ing. ");
  adquisidorSimple.textosMensajes= MessageOut_AddMessage(&adquisidorSimple.mensajes,adquisidorSimple.mensaje);
  
  Teclas_Init();
  Display_Init(); // Inicializacion del display
  com_Init();
  System_init();
  add1msListener(AdquisidorSimple_on1ms,&adquisidorSimple);
  
//  BoxPri1c_ShowGetter(&GetterState,&(adquisidorSimple.adquisidor));
  
  AdquisidorSimple_actualizarTextos(&adquisidorSimple);
  newAlloced(&(adquisidorSimple.timer),&RlxMTimer,(ulong)2000,AdquisidorSimple_actualizarTextos,&adquisidorSimple);

  
  
  DN_Init(&CBox_Pri);
  Sets_Init();
  dateTimeVista_addBoxes(&baseTiempo,"AdQ",0);
  AdqHmi_AddBoxes(&adquisidorSimple.adquisidor,0);
  SnsHmi_Add(adquisidorSimple.termometro.sensor,0);
  

  Sets_AddBoxes();
	ModBusHmi_AddBoxes();												 


  AdqHmi_ComuAdd(&adquisidorSimple.adquisidor,1050);
  
  
  
  for(;;){
		
		
    tecla=get_key();  
    //Eventos
    DN_Proc(tecla);
    
    AdquisidorSimple_mainLoop(&adquisidorSimple);
    
  }
}