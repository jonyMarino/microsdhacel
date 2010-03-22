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
#include "PWMTimer.hpp"
#include "configuracionControlPID.hpp"
#include "SensorTermoPT100.hpp"
#include "VistaPWM.hpp"
#include "BoxPrincipalControl.hpp"
#include "MessagesOut.hpp"
#include "LedSalida.hpp"
#include "configuracionAlarmas.hpp"
#include "configuracionLazoAlarmas.hpp"
#include "ConfiguracionRetransmision.hpp"
#include "ConfiguracionAdapSalida.hpp"
#include "configuracionValorControl.hpp"
#include "VistaAlarmas.hpp"
#include "AlarmaControl.hpp"

void conectarSalidas(void * a);
void OnTipoSalChange(void * b);


#pragma CONST_SEG PARAMETERS_PAGE
 

const LedsSalida::LedConfig configuracionLedsSalida[]= {
  &PTIP,1<<1,0,
  &PTIP,1<<3,1, 
  &PTIP,1<<5,2,
  &PTIP,1<<7,3
};
const LedsSalida::LedConfig* pConfiguracionLedsSalida[]={
  &configuracionLedsSalida[0],
  &configuracionLedsSalida[1],
  &configuracionLedsSalida[2],
  &configuracionLedsSalida[3]
};


/*  Tiempo inicial en el que el control permanece desconectado  */
#ifdef _COLADA_CALIENTE  
  #define SALIDA_TIEMPO_DESCONECTADA 20000 
#else
  #define SALIDA_TIEMPO_DESCONECTADA 3000   //tiene que alcanzar para hacer 2 mediciones
#endif


volatile const ConfiguracionControlPID::ControlConf control_config={
   ControlDefaultConf,
};
  
volatile const ConfiguracionAlarmas::AlarmConf alar_conf[CANTIDAD_SAL_ALARMA]={
  0,1,
  #if CANTIDAD_SAL_ALARMA>1 
    0,1,
      #if CANTIDAD_SAL_ALARMA>2
        0,1,
        #if CANTIDAD_SAL_ALARMA>3
          0,1,
        #endif
      #endif
  #endif
};
  
volatile const ConfiguracionLazoAlarmas::LazoAlarmConf lazo_alar_conf[CANTIDAD_SAL_ALARMA]={
  0,
  #if CANTIDAD_SAL_ALARMA>1 
    0,
      #if CANTIDAD_SAL_ALARMA>2
        0,
        #if CANTIDAD_SAL_ALARMA>3
          0,
        #endif
      #endif
  #endif
};
  
  
volatile const ConfiguracionRetransm::RetConf ret_conf[CANTIDAD_SAL_ALARMA]={
  0,100,
  #if CANTIDAD_SAL_ALARMA>1 
    0,100,
      #if CANTIDAD_SAL_ALARMA>2
        0,100,
        #if CANTIDAD_SAL_ALARMA>3
          0,100,
        #endif
      #endif
  #endif
};  
  
volatile const ConfiguracionAdapSalida::AdapSalConf adapSal_conf[CANTIDAD_SAL_ALARMA]={
  -2,0,
  #if CANTIDAD_SAL_ALARMA>1 
    -2,0,
      #if CANTIDAD_SAL_ALARMA>2
        -2,0,
        #if CANTIDAD_SAL_ALARMA>3
          -2,0,
        #endif
      #endif
  #endif
};  
    

volatile const ConfiguracionValorControlado::ValorControlConf alarmaSP_conf[CANTIDAD_SAL_ALARMA]={
  10,
  #if CANTIDAD_SAL_ALARMA>1 
    10,
      #if CANTIDAD_SAL_ALARMA>2
        10,
        #if CANTIDAD_SAL_ALARMA>3
          10,
        #endif
      #endif
  #endif
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
PWMManager01_45::PWMHard45 pwm1(flash,confPWM01);
//PWMTimer pwm1(flash,confPWM01,1);
const ConfiguracionControlPID configuraControl0(*(ConfiguracionControlPID::ControlConf*)&control_config,flash); 
ControlPID control0(sensor0,pwm,configuraControl0);
#if CANTIDAD_CANALES>1 
const ConfiguracionControlPID configuraControl1(*(ConfiguracionControlPID::ControlConf*)&control_config,flash);
ControlPID control1(sensor1,pwm,configuraControl1);
#endif
MessagesOut mjsCambioTipoSalida;


ConfiguracionLazoAlarmas configuracionLazoAlarmas0(*(ConfiguracionLazoAlarmas::LazoAlarmConf*)&lazo_alar_conf[0],flash);
ConfiguracionAlarmas configuracionAlarma0(*(ConfiguracionAlarmas::AlarmConf*)&alar_conf[0],flash);
ConfiguracionRetransm configuracionRetrans0(*(ConfiguracionRetransm::RetConf*)&ret_conf[0],flash);
ConfiguracionAdapSalida configuracionAdapSalida0(*(ConfiguracionAdapSalida::AdapSalConf*)&adapSal_conf[0],flash);
ConfiguracionValorControlado configuracionValorAlarma0(*(ConfiguracionValorControlado::ValorControlConf*)&alarmaSP_conf[0],flash);

CoordinadorLazosAlCntrRet alarma0(configuracionLazoAlarmas0,configuracionAlarma0,configuracionValorAlarma0,configuracionAdapSalida0,configuracionRetrans0,control0,pwm1);

#if CANTIDAD_SAL_ALARMA>1 && CANTIDAD_CANALES==1  
ConfiguracionLazoAlarmas configuracionLazoAlarmas1(*(ConfiguracionLazoAlarmas::LazoAlarmConf*)&lazo_alar_conf[1],flash);
ConfiguracionAlarmas configuracionAlarma1(*(ConfiguracionAlarmas::AlarmConf*)&alar_conf[1],flash);
ConfiguracionRetransm configuracionRetrans1(*(ConfiguracionRetransm::RetConf*)&ret_conf[1],flash);
ConfiguracionAdapSalida configuracionAdapSalida1(*(ConfiguracionAdapSalida::AdapSalConf*)&adapSal_conf[1],flash);
ConfiguracionValorControlado configuracionValorAlarma1(*(ConfiguracionValorControlado::ValorControlConf*)&alarmaSP_conf[1],flash);

CoordinadorLazosAlCntrRet alarma1(configuracionLazoAlarmas1,configuracionAlarma1,configuracionValorAlarma1,configuracionAdapSalida1,configuracionRetrans1,control0,pwm);
#elif CANTIDAD_CANALES>1
ConfiguracionLazoAlarmas configuracionLazoAlarmas1(*(ConfiguracionLazoAlarmas::LazoAlarmConf*)&lazo_alar_conf[1],flash);
ConfiguracionAlarmas configuracionAlarma1(*(ConfiguracionAlarmas::AlarmConf*)&alar_conf[1],flash);
ConfiguracionRetransm configuracionRetrans1(*(ConfiguracionRetransm::RetConf*)&ret_conf[1],flash);
ConfiguracionAdapSalida configuracionAdapSalida1(*(ConfiguracionAdapSalida::AdapSalConf*)&adapSal_conf[1],flash);
ConfiguracionValorControlado configuracionValorAlarma1(*(ConfiguracionValorControlado::ValorControlConf*)&alarmaSP_conf[1],flash);

CoordinadorLazosAlCntrRet alarma1(configuracionLazoAlarmas1,configuracionAlarma1,configuracionValorAlarma1,configuracionAdapSalida1,configuracionRetrans1,control1,pwm);

#if CANTIDAD_SAL_ALARMA>2
ConfiguracionLazoAlarmas configuracionLazoAlarmas2(*(ConfiguracionLazoAlarmas::LazoAlarmConf*)&lazo_alar_conf[2],flash);
ConfiguracionAlarmas configuracionAlarma2(*(ConfiguracionAlarmas::AlarmConf*)&alar_conf[2],flash);
ConfiguracionRetransm configuracionRetrans2(*(ConfiguracionRetransm::RetConf*)&ret_conf[2],flash);
ConfiguracionAdapSalida configuracionAdapSalida2(*(ConfiguracionAdapSalida::AdapSalConf*)&adapSal_conf[2],flash);
ConfiguracionValorControlado configuracionValorAlarma2(*(ConfiguracionValorControlado::ValorControlConf*)&alarmaSP_conf[2],flash);
 
CoordinadorLazosAlCntrRet alarma2(configuracionLazoAlarmas2,configuracionAlarma2,configuracionValorAlarma2,configuracionAdapSalida2,configuracionRetrans2,control0,pwm);
#endif
#endif

 
//potencia
const struct FstBoxPointer potInst={
  (const struct ConstructorBox*)&cBoxPotInst,&control0,0  
};

const struct FstBoxPointer potMan={
  (const struct ConstructorBox*)&cBoxPotMan,&control0,0  
};

//SP_alarma
const struct FstBoxPointer SPal0={
  (const struct ConstructorBox*)&cBoxesSetPointAlarma,&alarma0,0  
};
#if CANTIDAD_SAL_ALARMA>1 || CANTIDAD_CANALES>1 
const struct FstBoxPointer SPal1={
  (const struct ConstructorBox*)&cBoxesSetPointAlarma,&alarma1,1  
};
#if CANTIDAD_SAL_ALARMA>2
const struct FstBoxPointer SPal2={
  (const struct ConstructorBox*)&cBoxesSetPointAlarma,&alarma2,2  
};
#endif
#endif

struct ConstructorBoxPrincipalControl cBoxPri={
      &boxPrincipalControlFactory,							/* funcion que procesa al box*/
      &sensor0,      
      &mjsCambioTipoSalida,
      &flash						
};

const struct FstBoxPointer principal={
  (const ConstructorBox*)&cBoxPri,NULL,0  
};

const struct FstBoxPointer *const opArray[]={
  &principal,
  &potInst,
  &potMan,
  &SPal0,
  #if CANTIDAD_SAL_ALARMA>1 || CANTIDAD_CANALES>1 
  &SPal1,
  #if CANTIDAD_SAL_ALARMA>2
  &SPal2
  #endif
  #endif
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

const struct FstBoxPointer histAlarma0={(const struct ConstructorBox*)&cBoxesHistAlarma,&alarma0,0};
#if CANTIDAD_SAL_ALARMA>1 || CANTIDAD_CANALES>1 
const struct FstBoxPointer histAlarma1={(const struct ConstructorBox*)&cBoxesHistAlarma,&alarma1,1};
#if CANTIDAD_SAL_ALARMA>2
const struct FstBoxPointer histAlarma2={(const struct ConstructorBox*)&cBoxesHistAlarma,&alarma2,2};
#endif
#endif

static const struct FstBoxPointer *const tunArray[]={
  &reset,
  &periodo,
  &aparatoConf,
  &histAlarma0,
  #if CANTIDAD_SAL_ALARMA>1 || CANTIDAD_CANALES>1 
  &histAlarma1,
  #if CANTIDAD_SAL_ALARMA>2
  &histAlarma2
  #endif
  #endif
    
};

static const NEW_BOX_LIST(tun,tunArray,"SintoniA");
 
//CAL
const struct FstBoxPointer sensor1List={(const struct ConstructorBox*)&cBoxesSensor,&sensor0,1};

const struct FstBoxPointer retAlmLimInf0={(const struct ConstructorBox*)&cBoxesRetLimInf,&alarma0,0};
const struct FstBoxPointer retAlmLimSup0={(const struct ConstructorBox*)&cBoxesRetLimSup,&alarma0,0};
#if CANTIDAD_SAL_ALARMA>1  || CANTIDAD_CANALES>1 
const struct FstBoxPointer retAlmLimInf1={(const struct ConstructorBox*)&cBoxesRetLimInf,&alarma1,1};
const struct FstBoxPointer retAlmLimSup1={(const struct ConstructorBox*)&cBoxesRetLimSup,&alarma1,1};
#if CANTIDAD_SAL_ALARMA>2
const struct FstBoxPointer retAlmLimInf2={(const struct ConstructorBox*)&cBoxesRetLimInf,&alarma2,2};
const struct FstBoxPointer retAlmLimSup2={(const struct ConstructorBox*)&cBoxesRetLimSup,&alarma2,2};
#endif
#endif

static const struct FstBoxPointer *const calArray[]={
  &sensor1List,
  &retAlmLimInf0,
  &retAlmLimSup0
  #if CANTIDAD_SAL_ALARMA>1 || CANTIDAD_CANALES>1 
  &retAlmLimInf1,
  &retAlmLimSup1,
  #if CANTIDAD_SAL_ALARMA>2
  &retAlmLimInf2,
  &retAlmLimSup2
  #endif
  #endif  
};

static const NEW_BOX_LIST(cal,calArray,"CALibrAcion");

//SET
const VistaSetContrasenia vistaSetContrasenia={
  (const int *)&codigo,
  &flash
};
const struct FstBoxPointer setCList={(const struct ConstructorBox*)&VistaSetContrasenia::cBoxSetContrasenia,(void*)&vistaSetContrasenia,0};

const struct FstBoxPointer modosSalida={(const struct ConstructorBox*)&cBoxModoSalida,&control0,0};    

const struct FstBoxPointer tipoLazoAlarma={(const struct ConstructorBox*)&cBoxesTipoLazo,&alarma0,0};

const struct FstBoxPointer modosAlarma0={(const struct ConstructorBox*)&cBoxesAlarma,&alarma0,0};
const struct FstBoxPointer ctrlAlarma0={(const struct ConstructorBox*)&cBoxesAlarmaCtrl,&alarma0,0};
#if CANTIDAD_SAL_ALARMA>1 || CANTIDAD_CANALES>1 
const struct FstBoxPointer modosAlarma1={(const struct ConstructorBox*)&cBoxesAlarma,&alarma1,1};
const struct FstBoxPointer ctrlAlarma1={(const struct ConstructorBox*)&cBoxesAlarmaCtrl,&alarma1,1};
#if CANTIDAD_SAL_ALARMA>2
const struct FstBoxPointer modosAlarma2={(const struct ConstructorBox*)&cBoxesAlarma,&alarma2,2};
const struct FstBoxPointer ctrlAlarma2={(const struct ConstructorBox*)&cBoxesAlarmaCtrl,&alarma2,2};
#endif
#endif

static const struct FstBoxPointer *const setArray[]={
  &modosSalida,
  &tipoLazoAlarma,
  &modosAlarma0,
  &ctrlAlarma0,
  #if CANTIDAD_SAL_ALARMA>1 || CANTIDAD_CANALES>1 
  &modosAlarma1,
  &ctrlAlarma1,
  #if CANTIDAD_SAL_ALARMA>2
  &modosAlarma2,
  &ctrlAlarma2,
  #endif
  #endif
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


NEW_ARRAY(arrayLedConfig,pConfiguracionLedsSalida);

const LedsSalida leds (arrayLedConfig,*(FrenteDH::getInstancia()));

void * timer=NULL;

struct Method timerSalida={
&conectarSalidas,NULL
}; 

struct Method cambioTipoSalida={
&OnTipoSalChange,NULL
};                                              


void main(void) {
  
  BoxPrincipalControl::MostrarProp((ConstructorPropGetterVisual *)&cPropiedadSetPoint,&control0);
  RlxMTimer timerConexionSalidas(SALIDA_TIEMPO_DESCONECTADA,timerSalida);
  timer=&timerConexionSalidas;
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
   pwm.setConectada(TRUE);
   pwm1.setConectada(TRUE);
    
}



void OnTipoSalChange(void * b){
  static MessagesOut::Message msj_on_sal_change;  
  if(control0.getModoSalida()==ControlPID::_MAN){
    if(!msj_on_sal_change)
      msj_on_sal_change = mjsCambioTipoSalida.addMessage("Pot "); 
     BoxPrincipalControl::MostrarProp((ConstructorPropGetterVisual *)&cPropiedadPotManual,&control0);   
  }else{
    if(msj_on_sal_change){

      mjsCambioTipoSalida.deleteMessage(msj_on_sal_change);
      BoxPrincipalControl::MostrarProp((ConstructorPropGetterVisual *)&cPropiedadSetPoint,&control0);
      msj_on_sal_change=NULL; 
    }                          
  } 
}

