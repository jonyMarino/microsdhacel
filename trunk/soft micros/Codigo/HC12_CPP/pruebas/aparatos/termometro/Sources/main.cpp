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

void conectarSalidas(void * a);

#pragma CONST_SEG PARAMETERS_PAGE
 
  /*volatile const Salida::confSalida salida_config={
    0,            //potencia inicial
    FALSE,        //inicia desconectada 
    SALIDA_ONOFF  //tipo de salida inicial
  };*/
  
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
  volatile const TConfPWM confPWM01;
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

PWMHard23 pwm(flash,confPWM01);
const ConfiguracionControlPID configuraControl(*(ConfiguracionControlPID::ControlConf*)&control_config,flash); 
ControlPID control0(sensor0,pwm,configuraControl); 
  

//potencia
const struct FstBoxPointer potInst={
  (const struct ConstructorBox*)&cBoxPotInst,&control0,0  
};

const struct FstBoxPointer potMan={
  (const struct ConstructorBox*)&cBoxPotMan,&control0,0  
};

const struct ConstructorBoxPrincipalControl cBoxPri={
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

RlxMTimer timerConexionSalidas(SALIDA_TIEMPO_DESCONECTADA,Method(conectarSalidas,NULL));

void main(void) {
  
  BoxPrincipalControl::MostrarProp((ConstructorPropGetterVisual *)&cPropiedadSetPoint,&control0);
  DiagramaNavegacion d(&opList,&accessList,FrenteDH::getInstancia());
  PE_low_level_init();
  
  for(;;){
    
    if((timerConexionSalidas.isFinished()))
       timerConexionSalidas.stop();
    
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
  timerConexionSalidas->stop();
 
  pwm.setConectada(TRUE);
  
   //configurar leds
   //LedsSalida_init(&ledsSalida);
   
}
  