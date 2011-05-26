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

#pragma CONST_SEG PARAMETERS_PAGE
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

const struct ConstructorBoxPrincipal cBoxPri={
      &boxPrincipalFactory,                                                     /* funcion que procesa al box*/
      &sensor0,      
      NULL                                              
};

const struct FstBoxPointer principal={
  (const ConstructorBox*)&cBoxPri,NULL,0  
};

const struct FstBoxPointer *const opArray[]={
  &principal  
};

/*const struct BoxList opList ={
  &opArray,
  1,
  FALSE,
  ""  
};*/
const NEW_BOX_LIST(opList,opArray,"");


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

static const struct FstBoxPointer *const setArray[]={
  &setCList  
};

static const NEW_BOX_LIST(set,setArray,"ConFigurAcion");
  
// Acceso comun
const struct BoxList *const boxListArray[]={
  &cal,
  &set
};

const NEW_ACCESS(accesoComun,boxListArray,"Cod",(const int*)&codigo);

const struct Access *const accessArray[]={
  &accesoComun
};

const NEW_ARRAY(accessList,accessArray);

 

void main(void) {
  DiagramaNavegacion d(&opList,&accessList,FrenteDH::getInstancia());
  PE_low_level_init();
  
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
  