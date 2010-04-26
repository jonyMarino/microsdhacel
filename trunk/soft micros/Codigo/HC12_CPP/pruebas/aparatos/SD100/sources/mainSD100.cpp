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
#include "FrenteSD.hpp"
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
#include "BoxPrincipalControlSD.hpp"
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
  &PTT+1,1,5,
  &PTT+1,1<<1,2, //Hard
  &PTT+1,1<<2,6,
  &PTT+1,1<<3,4, //Hard
  &PTT+1,1<<4,3,
  &PTT+1,1<<5,0,
  &PTT+1,1<<6,1,
  &PTT+1,1<<7,7
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


volatile const ConfiguracionControlPID::ControlConf control_config[CANTIDAD_CANALES]={
   ControlDefaultConf,
   ControlDefaultConf,
   ControlDefaultConf,
   ControlDefaultConf,
};
  
volatile const ConfiguracionAlarmas::AlarmConf alar_conf[CANTIDAD_SAL_ALARMA]={
  0,1,
  0,1,
  0,1,
  0,1,
      
};
  
volatile const ConfiguracionLazoAlarmas::LazoAlarmConf lazo_alar_conf[CANTIDAD_SAL_ALARMA]={
  0,
  0,
  0,
  0,
};
  
  
volatile const ConfiguracionRetransm::RetConf ret_conf[CANTIDAD_SAL_ALARMA]={
  0,100,
  0,100,
  0,100,
  0,100,
};  
  
volatile const ConfiguracionAdapSalida::AdapSalConf adapSal_conf[CANTIDAD_SAL_ALARMA]={
  -2,0,
  -2,0,
  -2,0,
  -2,0,
};  
    

volatile const ConfiguracionValorControlado::ValorControlConf alarmaSP_conf[CANTIDAD_SAL_ALARMA]={
  10,
  10,
  10,
  10,
};  
  
  volatile const SensorTermoPT100::TConfSensor sensor_config[CANTIDAD_CANALES]= {
    STPT_DEF_CONF,
    STPT_DEF_CONF,
    STPT_DEF_CONF,
    STPT_DEF_CONF,
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


Adc  ad0(0);
Adc  ad1(1);
Adc  ad2(2);
Adc  ad3(3);
SensorTermoPT100 sensor0(ad0,sensor_config[0],flash);
SensorTermoPT100 sensor1(ad1,sensor_config[1],flash);
SensorTermoPT100 sensor2(ad2,sensor_config[2],flash);
SensorTermoPT100 sensor3(ad3,sensor_config[3],flash);

const Getter * gettersAMostrar[]={
  &sensor0,
  &sensor1,
  &sensor2,
  &sensor3
};					


TConfPWM confPWM[CANTIDAD_CANALES+CANTIDAD_SAL_ALARMA]={
0,
0,
0,
0,
0,
0,
0,
0,

};

//PWMHard23 pwm23(flash,confPWM[0]);
PWMTimer pwm1(flash,confPWM[0],0);
PWMTimer pwm2(flash,confPWM[1],1);
PWMTimer pwm3(flash,confPWM[2],2);
PWMTimer pwm4(flash,confPWM[3],3);
PWMTimer pwm5(flash,confPWM[4],4);
PWMTimer pwm6(flash,confPWM[5],5);
PWMTimer pwm7(flash,confPWM[6],6);
PWMTimer pwm8(flash,confPWM[7],7);

const ConfiguracionControlPID configuraControl0(*(ConfiguracionControlPID::ControlConf*)&control_config[0],flash); 
ControlPID control0(sensor0,pwm1,configuraControl0);

const ConfiguracionControlPID configuraControl1(*(ConfiguracionControlPID::ControlConf*)&control_config[1],flash);
ControlPID control1(sensor1,pwm2,configuraControl1);

const ConfiguracionControlPID configuraControl2(*(ConfiguracionControlPID::ControlConf*)&control_config[2],flash); 
ControlPID control2(sensor2,pwm3,configuraControl2);

const ConfiguracionControlPID configuraControl3(*(ConfiguracionControlPID::ControlConf*)&control_config[3],flash);
ControlPID control3(sensor3,pwm4,configuraControl3);



MessagesOut mjsCambioTipoSalida;


ConfiguracionLazoAlarmas configuracionLazoAlarmas0(*(ConfiguracionLazoAlarmas::LazoAlarmConf*)&lazo_alar_conf[0],flash);
ConfiguracionAlarmas configuracionAlarma0(*(ConfiguracionAlarmas::AlarmConf*)&alar_conf[0],flash);
ConfiguracionRetransm configuracionRetrans0(*(ConfiguracionRetransm::RetConf*)&ret_conf[0],flash);
ConfiguracionAdapSalida configuracionAdapSalida0(*(ConfiguracionAdapSalida::AdapSalConf*)&adapSal_conf[0],flash);
ConfiguracionValorControlado configuracionValorAlarma0(*(ConfiguracionValorControlado::ValorControlConf*)&alarmaSP_conf[0],flash);

CoordinadorLazosAlCntrRet alarma0(configuracionLazoAlarmas0,configuracionAlarma0,configuracionValorAlarma0,configuracionAdapSalida0,configuracionRetrans0,control0,pwm5);

ConfiguracionLazoAlarmas configuracionLazoAlarmas1(*(ConfiguracionLazoAlarmas::LazoAlarmConf*)&lazo_alar_conf[1],flash);
ConfiguracionAlarmas configuracionAlarma1(*(ConfiguracionAlarmas::AlarmConf*)&alar_conf[1],flash);
ConfiguracionRetransm configuracionRetrans1(*(ConfiguracionRetransm::RetConf*)&ret_conf[1],flash);
ConfiguracionAdapSalida configuracionAdapSalida1(*(ConfiguracionAdapSalida::AdapSalConf*)&adapSal_conf[1],flash);
ConfiguracionValorControlado configuracionValorAlarma1(*(ConfiguracionValorControlado::ValorControlConf*)&alarmaSP_conf[1],flash);

CoordinadorLazosAlCntrRet alarma1(configuracionLazoAlarmas1,configuracionAlarma1,configuracionValorAlarma1,configuracionAdapSalida1,configuracionRetrans1,control1,pwm6);


ConfiguracionLazoAlarmas configuracionLazoAlarmas2(*(ConfiguracionLazoAlarmas::LazoAlarmConf*)&lazo_alar_conf[2],flash);
ConfiguracionAlarmas configuracionAlarma2(*(ConfiguracionAlarmas::AlarmConf*)&alar_conf[2],flash);
ConfiguracionRetransm configuracionRetrans2(*(ConfiguracionRetransm::RetConf*)&ret_conf[2],flash);
ConfiguracionAdapSalida configuracionAdapSalida2(*(ConfiguracionAdapSalida::AdapSalConf*)&adapSal_conf[2],flash);
ConfiguracionValorControlado configuracionValorAlarma2(*(ConfiguracionValorControlado::ValorControlConf*)&alarmaSP_conf[2],flash);
 
CoordinadorLazosAlCntrRet alarma2(configuracionLazoAlarmas2,configuracionAlarma2,configuracionValorAlarma2,configuracionAdapSalida2,configuracionRetrans2,control2,pwm7);

ConfiguracionLazoAlarmas configuracionLazoAlarmas3(*(ConfiguracionLazoAlarmas::LazoAlarmConf*)&lazo_alar_conf[2],flash);
ConfiguracionAlarmas configuracionAlarma3(*(ConfiguracionAlarmas::AlarmConf*)&alar_conf[2],flash);
ConfiguracionRetransm configuracionRetrans3(*(ConfiguracionRetransm::RetConf*)&ret_conf[2],flash);
ConfiguracionAdapSalida configuracionAdapSalida3(*(ConfiguracionAdapSalida::AdapSalConf*)&adapSal_conf[2],flash);
ConfiguracionValorControlado configuracionValorAlarma3(*(ConfiguracionValorControlado::ValorControlConf*)&alarmaSP_conf[2],flash);
 
CoordinadorLazosAlCntrRet alarma3(configuracionLazoAlarmas3,configuracionAlarma3,configuracionValorAlarma3,configuracionAdapSalida3,configuracionRetrans3,control3,pwm8);



const struct FstBoxPointer potInst0={
  (const struct ConstructorBox*)&cBoxPotInst,&control0,1
};  

const struct FstBoxPointer potMan0={
  (const struct ConstructorBox*)&cBoxPotMan,&control0,1
};

const struct FstBoxPointer potInst1={
  (const struct ConstructorBox*)&cBoxPotInst,&control1,2
};  

const struct FstBoxPointer potMan1={
  (const struct ConstructorBox*)&cBoxPotMan,&control1,2
}; 

const struct FstBoxPointer potInst2={
  (const struct ConstructorBox*)&cBoxPotInst,&control2,3
};  

const struct FstBoxPointer potMan2={
  (const struct ConstructorBox*)&cBoxPotMan,&control2,3
};

const struct FstBoxPointer potInst3={
  (const struct ConstructorBox*)&cBoxPotInst,&control3,4
};  

const struct FstBoxPointer potMan3={
  (const struct ConstructorBox*)&cBoxPotMan,&control3,4
};  
  
 

//SP_alarma
    const struct FstBoxPointer SPal0={
      (const struct ConstructorBox*)&cBoxesSetPointAlarma,&alarma0,1
    };  
    
    const struct FstBoxPointer SPal1={
      (const struct ConstructorBox*)&cBoxesSetPointAlarma,&alarma1,2
    };  
   
    const struct FstBoxPointer SPal2={
      (const struct ConstructorBox*)&cBoxesSetPointAlarma,&alarma2,3
    };
    
    const struct FstBoxPointer SPal3={
      (const struct ConstructorBox*)&cBoxesSetPointAlarma,&alarma3,4
    };  
   
 

struct ConstructorBoxPrincipalControlSD cBoxPri={
      &boxPrincipalControlSDFactory,							// funcion que procesa al box
      gettersAMostrar,      
      &mjsCambioTipoSalida,
      &flash						
};

const struct FstBoxPointer principal={
  (const ConstructorBox*)&cBoxPri,NULL,0
};  


const struct FstBoxPointer *const opArray[]={
  &principal,
  &potInst0,
  &potInst1,
  &potInst2,
  &potInst3,
  &potMan0,
  &potMan1,
  &potMan2,
  &potMan3,
  &SPal0,
  &SPal1,
  &SPal2,
  &SPal3,
};

/*const struct BoxList opList ={
  &opArray,
  1,
  FALSE,
  ""  
};*/


const NEW_BOX_LIST(opList,opArray,"");

//TUN        
const struct FstBoxPointer reset0={
  (const struct ConstructorBox*)&cBoxesReset,&control0,1
};
const struct FstBoxPointer aparatoConf0={
  (const struct ConstructorBox*)&cBoxesSintonia,&control0,1
};
const struct FstBoxPointer reset1={
  (const struct ConstructorBox*)&cBoxesReset,&control1,2
};
const struct FstBoxPointer aparatoConf1={
  (const struct ConstructorBox*)&cBoxesSintonia,&control1,2
};
const struct FstBoxPointer reset2={
  (const struct ConstructorBox*)&cBoxesReset,&control2,3
};
const struct FstBoxPointer aparatoConf2={
  (const struct ConstructorBox*)&cBoxesSintonia,&control2,3
};
const struct FstBoxPointer reset3={
  (const struct ConstructorBox*)&cBoxesReset,&control3,4
};
const struct FstBoxPointer aparatoConf3={
  (const struct ConstructorBox*)&cBoxesSintonia,&control3,4
};

const struct FstBoxPointer periodo0={
  (const struct ConstructorBox*)&cBoxPeriodo,&pwm1,1
};
const struct FstBoxPointer periodo1={
  (const struct ConstructorBox*)&cBoxPeriodo,&pwm2,2
};
const struct FstBoxPointer periodo2={
  (const struct ConstructorBox*)&cBoxPeriodo,&pwm3,3
};
const struct FstBoxPointer periodo3={
  (const struct ConstructorBox*)&cBoxPeriodo,&pwm4,4
};

const struct FstBoxPointer histAlarma0={
  (const struct ConstructorBox*)&cBoxesHistAlarma,&alarma0,1
};
const struct FstBoxPointer histAlarma1={
  (const struct ConstructorBox*)&cBoxesHistAlarma,&alarma1,2
};
const struct FstBoxPointer histAlarma2={
  (const struct ConstructorBox*)&cBoxesHistAlarma,&alarma2,3
};
const struct FstBoxPointer histAlarma3={
  (const struct ConstructorBox*)&cBoxesHistAlarma,&alarma3,4
};

static const struct FstBoxPointer *const tunArray[]={
  &reset0,
  &reset1,
  &reset2,
  &reset3,
  &periodo0,
  &periodo1,
  &periodo2,
  &periodo3,
  &aparatoConf0,
  &aparatoConf1,
  &aparatoConf2,
  &aparatoConf3,
  &histAlarma0,
  &histAlarma1,
  &histAlarma2,
  &histAlarma3,
    
};

static const NEW_BOX_LIST(tun,tunArray,"SintoniA");
 
//CAL

const struct FstBoxPointer sensor1List0={
  (const struct ConstructorBox*)&cBoxesSensor,&sensor0,1
};
const struct FstBoxPointer sensor1List1={
  (const struct ConstructorBox*)&cBoxesSensor,&sensor1,2
};
const struct FstBoxPointer sensor1List2={
  (const struct ConstructorBox*)&cBoxesSensor,&sensor2,3
};
const struct FstBoxPointer sensor1List3={
  (const struct ConstructorBox*)&cBoxesSensor,&sensor3,4
};
const struct FstBoxPointer retAlmLimInf0={
  (const struct ConstructorBox*)&cBoxesRetLimInf,&alarma0,0
};
const struct FstBoxPointer retAlmLimSup0={
  (const struct ConstructorBox*)&cBoxesRetLimSup,&alarma0,0
};
const struct FstBoxPointer retAlmLimInf1={
  (const struct ConstructorBox*)&cBoxesRetLimInf,&alarma1,2
};
const struct FstBoxPointer retAlmLimSup1={
  (const struct ConstructorBox*)&cBoxesRetLimSup,&alarma1,2
};
const struct FstBoxPointer retAlmLimInf2={
  (const struct ConstructorBox*)&cBoxesRetLimInf,&alarma2,3
};
const struct FstBoxPointer retAlmLimSup2={
  (const struct ConstructorBox*)&cBoxesRetLimSup,&alarma2,3
};
const struct FstBoxPointer retAlmLimInf3={
  (const struct ConstructorBox*)&cBoxesRetLimInf,&alarma3,4
};
const struct FstBoxPointer retAlmLimSup3={
  (const struct ConstructorBox*)&cBoxesRetLimSup,&alarma3,4
};


static const struct FstBoxPointer *const calArray[]={
  &sensor1List0,
  &sensor1List1,
  &sensor1List2,
  &sensor1List3,
  &retAlmLimInf0,
  &retAlmLimSup0,
  &retAlmLimInf1,
  &retAlmLimSup1,
  &retAlmLimInf2,
  &retAlmLimSup2,
  &retAlmLimInf3,
  &retAlmLimSup3, 
};

static const NEW_BOX_LIST(cal,calArray,"CALibrAcion");

//SET
const VistaSetContrasenia vistaSetContrasenia={
  (const int *)&codigo,
  &flash
};

const struct FstBoxPointer setCList={
  ((const struct ConstructorBox*)&VistaSetContrasenia::cBoxSetContrasenia),(void*)&vistaSetContrasenia,0
};

const struct FstBoxPointer modosSalida0={
  (const struct ConstructorBox*)&cBoxModoSalida,&control0,1
};
const struct FstBoxPointer modosSalida1={
  (const struct ConstructorBox*)&cBoxModoSalida,&control1,2
};
const struct FstBoxPointer modosSalida2={
  (const struct ConstructorBox*)&cBoxModoSalida,&control2,3
};
const struct FstBoxPointer modosSalida3={
  (const struct ConstructorBox*)&cBoxModoSalida,&control3,4
};    
    
const struct FstBoxPointer tipoLazoAlarma0={
  (const struct ConstructorBox*)&cBoxesTipoLazo,&alarma0,1
};
const struct FstBoxPointer modosAlarma0={
  (const struct ConstructorBox*)&cBoxesAlarma,&alarma0,1
};
const struct FstBoxPointer ctrlAlarma0={
  (const struct ConstructorBox*)&cBoxesAlarmaCtrl,&alarma0,1
};

const struct FstBoxPointer tipoLazoAlarma1={
  (const struct ConstructorBox*)&cBoxesTipoLazo,&alarma1,2
}; 
const struct FstBoxPointer modosAlarma1={
  (const struct ConstructorBox*)&cBoxesAlarma,&alarma1,2
};
const struct FstBoxPointer ctrlAlarma1={
  (const struct ConstructorBox*)&cBoxesAlarmaCtrl,&alarma1,2
};

const struct FstBoxPointer tipoLazoAlarma2={
  (const struct ConstructorBox*)&cBoxesTipoLazo,&alarma2,3
};
const struct FstBoxPointer modosAlarma2={
  (const struct ConstructorBox*)&cBoxesAlarma,&alarma2,3
};
const struct FstBoxPointer ctrlAlarma2={
  (const struct ConstructorBox*)&cBoxesAlarmaCtrl,&alarma2,3
};

const struct FstBoxPointer tipoLazoAlarma3={
  (const struct ConstructorBox*)&cBoxesTipoLazo,&alarma3,4
};
const struct FstBoxPointer modosAlarma3={
  (const struct ConstructorBox*)&cBoxesAlarma,&alarma3,4
};
const struct FstBoxPointer ctrlAlarma3={
  (const struct ConstructorBox*)&cBoxesAlarmaCtrl,&alarma3,4
};



static const struct FstBoxPointer *const setArray[]={
  &modosSalida0,
  &modosSalida1,
  &modosSalida2,
  &modosSalida3,
  &tipoLazoAlarma0,
  &modosAlarma0,
  &ctrlAlarma0,
  &tipoLazoAlarma1,
  &modosAlarma1,
  &ctrlAlarma1,
  &tipoLazoAlarma2,
  &modosAlarma2,
  &ctrlAlarma2,
  &tipoLazoAlarma3,
  &modosAlarma3,
  &ctrlAlarma3,
  &setCList
    
};

static const NEW_BOX_LIST(set,setArray,"ConFigurAcion");

//LIMITES        

const struct FstBoxPointer limites0={
  (const struct ConstructorBox*)&cBoxesLimites,&control0,1
};
const struct FstBoxPointer limites1={
  (const struct ConstructorBox*)&cBoxesLimites,&control1,2
};
const struct FstBoxPointer limites2={
  (const struct ConstructorBox*)&cBoxesLimites,&control2,3
};
const struct FstBoxPointer limites3={
  (const struct ConstructorBox*)&cBoxesLimites,&control3,4
};

static const struct FstBoxPointer *const limArray[]={
  &limites0,
  &limites1,
  &limites2,
  &limites3,
  
    
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

const LedsSalida leds (arrayLedConfig,*(FrenteSD::getInstancia()));

void * timer=NULL;

struct Method timerSalida={
&conectarSalidas,NULL
}; 

struct Method cambioTipoSalida={
&OnTipoSalChange,NULL
};                                              


void main(void) {
  
 
  RlxMTimer timerConexionSalidas(SALIDA_TIEMPO_DESCONECTADA,timerSalida);
  timer=&timerConexionSalidas;
  DiagramaNavegacion d(&opList,&accessList,FrenteSD::getInstancia());
  PE_low_level_init();
  control0.addOnTipoSalidaListener(cambioTipoSalida);
  
  for(;;){
    
    byte tecla = FrenteSD::getInstancia()->getTecla();
    termometro.mainLoop();
    d.procesar(tecla);
    sensor0.checkADC();
    sensor1.checkADC();
    sensor2.checkADC();
    sensor3.checkADC();
    
  }
    
  
  /* please make sure that you never leave main */
}
 
 
void conectarSalidas(void * a){
 
  ((RlxMTimer *)timer)->stop();
   pwm1.setConectada(TRUE);
   pwm1.setTipoSalida(SALIDA_ONOFF);
   pwm2.setConectada(TRUE);
   pwm2.setTipoSalida(SALIDA_ONOFF);
   pwm3.setConectada(TRUE);
   pwm3.setTipoSalida(SALIDA_ONOFF);
   pwm4.setConectada(TRUE);
   pwm4.setTipoSalida(SALIDA_ONOFF);
   pwm5.setConectada(TRUE);
   pwm5.setTipoSalida(SALIDA_ONOFF);
   pwm6.setConectada(TRUE);
   pwm6.setTipoSalida(SALIDA_ONOFF);
   pwm7.setConectada(TRUE);
   pwm7.setTipoSalida(SALIDA_ONOFF);
   pwm8.setConectada(TRUE);
   pwm8.setTipoSalida(SALIDA_ONOFF);
}



void OnTipoSalChange(void * b){
  static MessagesOut::Message msj_on_sal_change;  
  if(control0.getModoSalida()==ControlPID::_MAN){
    if(!msj_on_sal_change)
      msj_on_sal_change = mjsCambioTipoSalida.addMessage("Pot "); 
     BoxPrincipalControlSD::MostrarProp((ConstructorPropGetterVisual *)&cPropiedadPotManual,&control0);   
  }else{
    if(msj_on_sal_change){

      mjsCambioTipoSalida.deleteMessage(msj_on_sal_change);
      BoxPrincipalControlSD::MostrarProp((ConstructorPropGetterVisual *)&cPropiedadSetPoint,&control0);
      msj_on_sal_change=NULL; 
    }                          
  } 
}
