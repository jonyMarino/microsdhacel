#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "timer_interrupt.h"
#include "Adc.hpp"
#include "IAdc.hpp"
#include "Termometro.hpp"
#include "OutputStream.hpp"
#include "Cpu.h"
#include "WDog1.h"
//#include "object_r.h"
//#include "Object.h"
#include "FrenteDH.hpp"
#include "Timer/Timer.hpp"
#include "Timer/interrup_1ms_40ms/BaseTimers_1ms_40ms.hpp"
#include "Memoria/Prom/Flash/FlashBkpMitad/FlashBkpMitad.hpp"
#include "PropiedadGetter.hpp"
#include "ConstructorPropiedadGetter.hpp"
#include "vistasensortermopt100.hpp"
#include "BoxPrincipal.hpp"
#include "FstBoxPointer.hpp"
#include "BoxList.hpp"
#include "Access.hpp"
#include "DiagramaNavegacion.hpp"
#include "VistaSetContrasenia.hpp"
#include "VistaControl.hpp"
#include "Salida.hpp"
#include "IPWM.hpp"
#include "PWM.hpp"
#include "PWMHard.hpp"
#include "PWMHard23.hpp"
#include "PWMManager01_45.hpp"
#include "configuracionControlPID.hpp"
#include "SensorTermoPT100.hpp"
#include "VistaPWM.hpp"
#include "BoxPrincipalControl.hpp"
#include "MessagesOut.hpp"

void conectarSalidas(void * a);
void OnTipoSalChange(void * b);
void alternaIndicacion(void * c);

#pragma CONST_SEG PARAMETERS_PAGE
 
  /*volatile const Salida::confSalida salida_config={
    0,            //potencia inicial
    FALSE,        //inicia desconectada 
    SALIDA_ONOFF  //tipo de salida inicial
  };*/
  
/*volatile const TConfPWM confPWM01[CANTIDAD_SAL_ALARMA]={
  0,
  #if CANTIDAD_SAL_ALARMA>1 
    0,
      #if CANTIDAD_SAL_ALARMA>2
        0,
        #if CANTIDAD_SAL_ALARMA>3
          0
        #endif
      #endif
  #endif
};
         */

/*Tiempo de cambio en la indicacion del display inferior(caso tipo de salida manual)*/
#define TIEMPO_DE_ALTERNADO 2000

/*  Tiempo inicial en el que el control permanece desconectado  */
#ifdef _COLADA_CALIENTE  
  #define SALIDA_TIEMPO_DESCONECTADA 20000 
#else
  #define SALIDA_TIEMPO_DESCONECTADA 3000   //tiene que alcanzar para hacer 2 mediciones
#endif

volatile const ConfiguracionControlPID::ControlConf control_config={
   ControlDefaultConf,
};
  
  volatile const SensorTermoPT100::TConfSensor sensor_config[CANTIDAD_CANALES]= {
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
 };
 int ta=0;
 #ifdef NDEBUG
  volatile const int codigo = 1234;
 #else 
  volatile const int codigo = 0;
 #endif



#pragma CONST_SEG DEFAULT



class Init{
  public:
  Init(){
    Timer::setBaseTimerDefault(*BaseTimers_1ms_40ms::getInstance());
    SensorTermoPT100::setConfiguracionTemperaturaAmbiente(&ta);

  }
}ini;

FlashBkpMitad flash((void*)0x4200);
 
Termometro termometro(flash); 

#if CANTIDAD_CANALES == 1     
Adc  ad0(0);
SensorTermoPT100 sensor0(ad0,sensor_config[0],flash);
#else
Adc  ad0(0);
Adc  ad1(1);
SensorTermoPT100 sensor0(ad0,sensor_config[0],flash);
SensorTermoPT100 sensor1(ad1,sensor_config[1],flash);
#endif 

TConfPWM confPWM01={
0};
PWMHard23 pwm(flash,confPWM01);
const ConfiguracionControlPID configuraControl(*(ConfiguracionControlPID::ControlConf*)&control_config,flash); 
ControlPID control0(sensor0,pwm,configuraControl);
MessagesOut mjsCambioTipoSalida;

//potencia
const struct FstBoxPointer potInst={
  (const struct ConstructorBox*)&cBoxPotInst,&control0,0  
};

const struct FstBoxPointer potMan={
  (const struct ConstructorBox*)&cBoxPotMan,&control0,0  
};

struct ConstructorBoxPrincipalControl cBoxPri={
      &boxPrincipalControlFactory,							/* funcion que procesa al box*/
      &sensor0,      
      NULL,
      &flash						
};

const struct FstBoxPointer principal={
  (const ConstructorBox*)&cBoxPri,NULL,0  
};

const struct FstBoxPointer *const opArray[]={
  &principal,
  &potInst,
  &potMan
  
  
};

/*const struct BoxList opList ={
  &opArray,
  1,
  FALSE,
  ""  
};*/
const NEW_BOX_LIST(opList,opArray,"");

//TUN        

const struct FstBoxPointer reset={(const struct ConstructorBox*)&cBoxesReset,&control0,0};

const struct FstBoxPointer aparatoConf={(const struct ConstructorBox*)&cBoxesSintonia,&control0,0};

const struct FstBoxPointer periodo={(const struct ConstructorBox*)&cBoxPeriodo,&pwm,0};


static const struct FstBoxPointer *const tunArray[]={
  &reset,
  &periodo,
  &aparatoConf
    
};

static const NEW_BOX_LIST(tun,tunArray,"SintoniA");
 
//CAL
const struct FstBoxPointer sensor1List={(const struct ConstructorBox*)&cBoxesSensor,&sensor0,1};

static const struct FstBoxPointer *const calArray[]={
  &sensor1List  
};

static const NEW_BOX_LIST(cal,calArray,"CALibrAcion");

//SET
const VistaSetContrasenia vistaSetContrasenia={
  (const int *)&codigo,
  &flash
};
const struct FstBoxPointer setCList={(const struct ConstructorBox*)&VistaSetContrasenia::cBoxSetContrasenia,(void*)&vistaSetContrasenia,0};

const struct FstBoxPointer modosSalida={(const struct ConstructorBox*)&cBoxModoSalida,&control0,0};

static const struct FstBoxPointer *const setArray[]={
  &modosSalida,
  &setCList
    
};

static const NEW_BOX_LIST(set,setArray,"ConFigurAcion");

//LIMITES        

const struct FstBoxPointer limites={(const struct ConstructorBox*)&cBoxesLimites,&control0,0};

static const struct FstBoxPointer *const limArray[]={
  &limites,
  
    
};

static const NEW_BOX_LIST(lim,limArray,"LimitES");
 


  
// Acceso comun
const struct BoxList *const boxListArray[]={
  &tun,
  &cal,
  &set,
  &lim
};

const NEW_ACCESS(accesoComun,boxListArray,"Cod",(const int*)&codigo);

const struct Access *const accessArray[]={
  &accesoComun
};

const NEW_ARRAY(accessList,accessArray);

void * timer=NULL;
void * timerAlterna=NULL;
bool alternar=TRUE; 
MessagesOut::Message msj_on_sal_change;  

struct Method timerSalida={
&conectarSalidas,NULL
}; 

struct Method cambioTipoSalida={
&OnTipoSalChange,NULL
};                                              

struct Method timerDeAlternado={
&alternaIndicacion,NULL
}; 



//RlxMTimer timerConexionSalidas(SALIDA_TIEMPO_DESCONECTADA,timerSalida);

void main(void) {
  
  BoxPrincipalControl::MostrarProp((ConstructorPropGetterVisual *)&cPropiedadSetPoint,&control0);
  RlxMTimer timerConexionSalidas(SALIDA_TIEMPO_DESCONECTADA,timerSalida);
  timer=&timerConexionSalidas;
  RlxMTimer timerDeAlternadoDisplay(TIEMPO_DE_ALTERNADO,timerDeAlternado);
  timerDeAlternadoDisplay.stop(); //inicia detenido
  timerAlterna=&timerDeAlternadoDisplay;
  DiagramaNavegacion d(&opList,&accessList,FrenteDH::getInstancia());
  PE_low_level_init();
  control0.addOnTipoSalidaListener(cambioTipoSalida);
  
  for(;;){
    
    byte tecla = FrenteDH::getInstancia()->getTecla();
    termometro.mainLoop();
    d.procesar(tecla);
   //for(i=0;i<CANTIDAD_CANALES;i++)
   #if CANTIDAD_CANALES == 1 
    sensor0.checkADC();
   #else
    sensor0.checkADC();
    sensor1.checkADC();
   #endif 
    
  }
    
  
  /* please make sure that you never leave main */
}
 
 
void conectarSalidas(void * a){
 byte i;
  ((RlxMTimer *)timer)->stop();
  
  //for(i=0;i<CANTIDAD_SAL_ALARMA;i++)
   // pwm.setConectada(TRUE);
  
  // pwm.setConectada(TRUE);
   
   //configurar leds
   //LedsSalida_init(&ledsSalida);
   
}



void OnTipoSalChange(void * b){
  
  if(control0.getModoSalida()==ControlPID::_MAN){
    if(!msj_on_sal_change)
      msj_on_sal_change = mjsCambioTipoSalida.addMessage("Pot "); 
     BoxPrincipalControl::MostrarProp((ConstructorPropGetterVisual *)&cPropiedadGetPotenciaInst,&control0);   
     ((RlxMTimer *)timerAlterna)->restart();
  }else{
    if(msj_on_sal_change){
      ((RlxMTimer *)timerAlterna)->stop();
      mjsCambioTipoSalida.deleteMessage(msj_on_sal_change);
      BoxPrincipalControl::MostrarProp((ConstructorPropGetterVisual *)&cPropiedadSetPoint,&control0);
      msj_on_sal_change=NULL;
      cBoxPri.super.msjs=&mjsCambioTipoSalida;  
    }                          
  } 
}

void alternaIndicacion(void * c){
  
  if(alternar){
    alternar=FALSE;
    if(msj_on_sal_change){
      mjsCambioTipoSalida.deleteMessage(msj_on_sal_change);
      msj_on_sal_change=NULL;
      cBoxPri.super.msjs=NULL;
    }
    BoxPrincipalControl::MostrarProp((ConstructorPropGetterVisual *)&cPropiedadGetPotenciaInst,&control0);
  }else{
    alternar=TRUE;
    if(!msj_on_sal_change){
      msj_on_sal_change = mjsCambioTipoSalida.addMessage("Pot ");
      cBoxPri.super.msjs=&mjsCambioTipoSalida;
    }
  }
} 