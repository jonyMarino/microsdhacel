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
#include "vistaAutoSintonia.hpp"
#include "CoordinadorControladorSintonizador.hpp"

void conectarSalidas(void * a);
void OnTipoSalChange(void * b);

const LedsSalida::LedConfig configuracionLedsSalida[]= {
  &PTIP,1<<3,0,
  &PTIP,1<<1,1, 
  &PTIP,1<<5,2,
  &PTIP,1<<7,3
};
const LedsSalida::LedConfig* pConfiguracionLedsSalida[]={
  &configuracionLedsSalida[0],
  &configuracionLedsSalida[1],
  &configuracionLedsSalida[2],
  &configuracionLedsSalida[3]
};


#pragma CONST_SEG PARAMETERS_PAGE
 

/*  Tiempo inicial en el que el control permanece desconectado  */
#ifdef _COLADA_CALIENTE  
  #define SALIDA_TIEMPO_DESCONECTADA 20000 
#else
  #define SALIDA_TIEMPO_DESCONECTADA 3000   //tiene que alcanzar para hacer 2 mediciones
#endif


volatile const ConfiguracionControlPID::ControlConf control_config[CANTIDAD_CANALES]={
   ControlDefaultConf,
   #if CANTIDAD_CANALES>1
   ControlDefaultConf
   #endif
};
  
volatile const ConfiguracionAlarmas::AlarmConf alar_conf[CANTIDAD_SAL_ALARMA]={
  4,1,
  #if CANTIDAD_SAL_ALARMA>1 
    4,1,
      #if CANTIDAD_SAL_ALARMA>2
        4,1,
        #if CANTIDAD_SAL_ALARMA>3
          4,1,
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
 
volatile const TConfPWM confPWM[CANTIDAD_CANALES+CANTIDAD_SAL_ALARMA]={
0,
0,
#if CANTIDAD_CANALES>1 || CANTIDAD_SAL_ALARMA>1
0,
#if CANTIDAD_CANALES>1 || CANTIDAD_SAL_ALARMA>2
0,
#endif
#endif

};               
 
 volatile const int ta=0;
 #ifdef NDEBUG
  volatile const int codigo = 1234;
 #else 
  volatile const int codigo = 0;
 #endif



#pragma CONST_SEG DEFAULT


FlashBkpMitad flash((void*)0x4200);

class Init{
  public:
  Init(){
    
    Timer::setBaseTimerDefault(*BaseTimers_1ms_40ms::getInstance());
    SensorTermoPT100::setConfiguracionTemperaturaAmbiente((int*)&ta);
  }
}ini;


 
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

PWMHard23 pwm23(flash,confPWM[0]);  // pwm control 0
PWMTimer pwm2(flash,confPWM[1],1);  // pwm alarma 1 o si es de 2 canales pwm control 1
PWMTimer pwm3(flash,confPWM[2],4);  // pwm alarma 2 o si es de 2 canales pwm alarma 1(canal 1)
PWMTimer pwm4(flash,confPWM[3],7);  // pwm alarma 3 o si es de 2 canales alarma 1(canal 2)


const ConfiguracionControlPID configuraControl0(*(ConfiguracionControlPID::ControlConf*)&control_config[0],flash); 
//ControlPID control0(sensor0,pwm23,configuraControl0);
CoordinadorControladorSintonizador control0(sensor0,pwm23,configuraControl0);

#if CANTIDAD_CANALES>1 
const ConfiguracionControlPID configuraControl1(*(ConfiguracionControlPID::ControlConf*)&control_config[1],flash);
ControlPID control1(sensor1,pwm2,configuraControl1);
#endif
MessagesOut mjsCambioTipoSalida;


ConfiguracionLazoAlarmas configuracionLazoAlarmas0(*(ConfiguracionLazoAlarmas::LazoAlarmConf*)&lazo_alar_conf[0],flash);
ConfiguracionAlarmas configuracionAlarma0(*(ConfiguracionAlarmas::AlarmConf*)&alar_conf[0],flash);
ConfiguracionRetransm configuracionRetrans0(*(ConfiguracionRetransm::RetConf*)&ret_conf[0],flash);
ConfiguracionAdapSalida configuracionAdapSalida0(*(ConfiguracionAdapSalida::AdapSalConf*)&adapSal_conf[0],flash);
ConfiguracionValorControlado configuracionValorAlarma0(*(ConfiguracionValorControlado::ValorControlConf*)&alarmaSP_conf[0],flash);

CoordinadorLazosAlCntrRet alarma0(configuracionLazoAlarmas0,configuracionAlarma0,configuracionValorAlarma0,configuracionAdapSalida0,configuracionRetrans0,(*(ControlPID*)(control0.getControl())),pwm3);

#if CANTIDAD_SAL_ALARMA>1 && CANTIDAD_CANALES==1  
ConfiguracionLazoAlarmas configuracionLazoAlarmas1(*(ConfiguracionLazoAlarmas::LazoAlarmConf*)&lazo_alar_conf[1],flash);
ConfiguracionAlarmas configuracionAlarma1(*(ConfiguracionAlarmas::AlarmConf*)&alar_conf[1],flash);
ConfiguracionRetransm configuracionRetrans1(*(ConfiguracionRetransm::RetConf*)&ret_conf[1],flash);
ConfiguracionAdapSalida configuracionAdapSalida1(*(ConfiguracionAdapSalida::AdapSalConf*)&adapSal_conf[1],flash);
ConfiguracionValorControlado configuracionValorAlarma1(*(ConfiguracionValorControlado::ValorControlConf*)&alarmaSP_conf[1],flash);

CoordinadorLazosAlCntrRet alarma1(configuracionLazoAlarmas1,configuracionAlarma1,configuracionValorAlarma1,configuracionAdapSalida1,configuracionRetrans1,control0,pwm2);
#elif CANTIDAD_CANALES>1
ConfiguracionLazoAlarmas configuracionLazoAlarmas1(*(ConfiguracionLazoAlarmas::LazoAlarmConf*)&lazo_alar_conf[1],flash);
ConfiguracionAlarmas configuracionAlarma1(*(ConfiguracionAlarmas::AlarmConf*)&alar_conf[1],flash);
ConfiguracionRetransm configuracionRetrans1(*(ConfiguracionRetransm::RetConf*)&ret_conf[1],flash);
ConfiguracionAdapSalida configuracionAdapSalida1(*(ConfiguracionAdapSalida::AdapSalConf*)&adapSal_conf[1],flash);
ConfiguracionValorControlado configuracionValorAlarma1(*(ConfiguracionValorControlado::ValorControlConf*)&alarmaSP_conf[1],flash);

CoordinadorLazosAlCntrRet alarma1(configuracionLazoAlarmas1,configuracionAlarma1,configuracionValorAlarma1,configuracionAdapSalida1,configuracionRetrans1,control1,pwm4);
#endif

#if CANTIDAD_SAL_ALARMA>2

ConfiguracionLazoAlarmas configuracionLazoAlarmas2(*(ConfiguracionLazoAlarmas::LazoAlarmConf*)&lazo_alar_conf[2],flash);
ConfiguracionAlarmas configuracionAlarma2(*(ConfiguracionAlarmas::AlarmConf*)&alar_conf[2],flash);
ConfiguracionRetransm configuracionRetrans2(*(ConfiguracionRetransm::RetConf*)&ret_conf[2],flash);
ConfiguracionAdapSalida configuracionAdapSalida2(*(ConfiguracionAdapSalida::AdapSalConf*)&adapSal_conf[2],flash);
ConfiguracionValorControlado configuracionValorAlarma2(*(ConfiguracionValorControlado::ValorControlConf*)&alarmaSP_conf[2],flash);
 
CoordinadorLazosAlCntrRet alarma2(configuracionLazoAlarmas2,configuracionAlarma2,configuracionValorAlarma2,configuracionAdapSalida2,configuracionRetrans2,control0,pwm4);

#endif

#if CANTIDAD_CANALES==1  
//potencia
const struct FstBoxPointer potInst0={
  (const struct ConstructorBox*)&cBoxPotInst,&control0,0
};  
const struct FstBoxPointer potMan0={
  (const struct ConstructorBox*)&cBoxPotMan,&control0,0
};  

#else
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

#endif

#if CANTIDAD_CANALES==1 


  #if CANTIDAD_SAL_ALARMA>1
//SP_alarma
    const struct FstBoxPointer SPal0={
      (const struct ConstructorBox*)&cBoxesSetPointAlarma,&alarma0,1
    };  
    const struct FstBoxPointer SPal1={
      (const struct ConstructorBox*)&cBoxesSetPointAlarma,&alarma1,2
    };  
   
  #else
    
     const struct FstBoxPointer SPal0={
      (const struct ConstructorBox*)&cBoxesSetPointAlarma,&alarma0,0
     };  
    
  #endif
   
  #if CANTIDAD_SAL_ALARMA>2
     const struct FstBoxPointer SPal2={
      (const struct ConstructorBox*)&cBoxesSetPointAlarma,&alarma2,3
     };  
   
  #endif

#else
    const struct FstBoxPointer SPal0={
      (const struct ConstructorBox*)&cBoxesSetPointAlarma,&alarma0,1
    };  
    const struct FstBoxPointer SPal1={
      (const struct ConstructorBox*)&cBoxesSetPointAlarma,&alarma1,2
    };  

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
  &potInst0,
  &potMan0,
  #if CANTIDAD_CANALES>1
  &potInst1, 
  &potMan1,
  #endif
  &SPal0,
  #if CANTIDAD_CANALES>1 || CANTIDAD_SAL_ALARMA>1
  &SPal1,
  #endif
  #if CANTIDAD_SAL_ALARMA>2
  &SPal2,
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

const struct FstBoxPointer autoSintonia0={
  (const struct ConstructorBox*)&cBoxModos,&control0,0
}; 

#if CANTIDAD_CANALES==1  

const struct FstBoxPointer reset0={
  (const struct ConstructorBox*)&cBoxesReset,&control0,0
};
const struct FstBoxPointer aparatoConf0={
  (const struct ConstructorBox*)&cBoxesSintonia,&control0,0
};
const struct FstBoxPointer periodo0={
  (const struct ConstructorBox*)&cBoxPeriodo,&pwm23,0
};
const struct FstBoxPointer histAlarma0={
  (const struct ConstructorBox*)&cBoxesHistAlarma,&alarma0,0
};


#else
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
const struct FstBoxPointer periodo0={
  (const struct ConstructorBox*)&cBoxPeriodo,&pwm23,1
};
const struct FstBoxPointer periodo1={
  (const struct ConstructorBox*)&cBoxPeriodo,&pwm2,2
};
#endif
#if CANTIDAD_SAL_ALARMA>1 && CANTIDAD_CANALES>1 
const struct FstBoxPointer histAlarma0={
  (const struct ConstructorBox*)&cBoxesHistAlarma,&alarma0,1
};
const struct FstBoxPointer histAlarma1={
  (const struct ConstructorBox*)&cBoxesHistAlarma,&alarma1,2
};
#if CANTIDAD_SAL_ALARMA>2
const struct FstBoxPointer histAlarma2={
  (const struct ConstructorBox*)&cBoxesHistAlarma,&alarma2,3
};
#endif
#endif

static const struct FstBoxPointer *const tunArray[]={
  &autoSintonia0,
  &reset0,
  &periodo0,
  &aparatoConf0,
  &histAlarma0,
  #if CANTIDAD_CANALES>1 
  &reset1,
  &periodo1, 
  &aparatoConf1,
  #endif
  #if CANTIDAD_SAL_ALARMA>1 && CANTIDAD_CANALES>1 
  &histAlarma1,
  #if CANTIDAD_SAL_ALARMA>2
  &histAlarma2
  #endif
  #endif
    
};

static const NEW_BOX_LIST(tun,tunArray,"SintoniA");
 
//CAL
#if CANTIDAD_CANALES==1 
const struct FstBoxPointer sensor1List0={
  (const struct ConstructorBox*)&cBoxesSensor,&sensor0,0
};
const struct FstBoxPointer retAlmLimInf0={
  (const struct ConstructorBox*)&cBoxesRetLimInf,&alarma0,0
};
const struct FstBoxPointer retAlmLimSup0={
  (const struct ConstructorBox*)&cBoxesRetLimSup,&alarma0,0
};
#else
const struct FstBoxPointer sensor1List0={
  (const struct ConstructorBox*)&cBoxesSensor,&sensor0,1
};
const struct FstBoxPointer sensor1List1={
  (const struct ConstructorBox*)&cBoxesSensor,&sensor1,2
};
const struct FstBoxPointer retAlmLimInf0={
  (const struct ConstructorBox*)&cBoxesRetLimInf,&alarma0,0
};
const struct FstBoxPointer retAlmLimSup0={
  (const struct ConstructorBox*)&cBoxesRetLimSup,&alarma0,0
};
#endif
#if CANTIDAD_SAL_ALARMA>1  || CANTIDAD_CANALES>1 
const struct FstBoxPointer retAlmLimInf1={
  (const struct ConstructorBox*)&cBoxesRetLimInf,&alarma1,2
};
const struct FstBoxPointer retAlmLimSup1={
  (const struct ConstructorBox*)&cBoxesRetLimSup,&alarma1,2
};
#if CANTIDAD_SAL_ALARMA>2
const struct FstBoxPointer retAlmLimInf2={
  (const struct ConstructorBox*)&cBoxesRetLimInf,&alarma2,3
};
const struct FstBoxPointer retAlmLimSup2={
  (const struct ConstructorBox*)&cBoxesRetLimSup,&alarma2,3
};
#endif
#endif

static const struct FstBoxPointer *const calArray[]={
  &sensor1List0,
  #if CANTIDAD_CANALES>1
  &sensor1List1,
  #endif 
  &retAlmLimInf0,
  &retAlmLimSup0,
  
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
const struct FstBoxPointer setCList={
  (const struct ConstructorBox*)&(VistaSetContrasenia::cBoxSetContrasenia),(void *)&vistaSetContrasenia,0 
  };
#if CANTIDAD_CANALES==1
const struct FstBoxPointer modosSalida0={
  (const struct ConstructorBox*)&cBoxModoSalida,&control0,0
};
#else
const struct FstBoxPointer modosSalida0={
  (const struct ConstructorBox*)&cBoxModoSalida,&control0,1
};
const struct FstBoxPointer modosSalida1={
  (const struct ConstructorBox*)&cBoxModoSalida,&control1,2
};    
#endif
const struct FstBoxPointer tipoLazoAlarma0={
  (const struct ConstructorBox*)&cBoxesTipoLazo,&alarma0,1
};
const struct FstBoxPointer modosAlarma0={
  (const struct ConstructorBox*)&cBoxesAlarma,&alarma0,1
};
const struct FstBoxPointer ctrlAlarma0={
  (const struct ConstructorBox*)&cBoxesAlarmaCtrl,&alarma0,1
};
#if CANTIDAD_SAL_ALARMA>1 || CANTIDAD_CANALES>1
const struct FstBoxPointer tipoLazoAlarma1={
  (const struct ConstructorBox*)&cBoxesTipoLazo,&alarma1,2
}; 
const struct FstBoxPointer modosAlarma1={
  (const struct ConstructorBox*)&cBoxesAlarma,&alarma1,2
};
const struct FstBoxPointer ctrlAlarma1={
  (const struct ConstructorBox*)&cBoxesAlarmaCtrl,&alarma1,2
};
#if CANTIDAD_SAL_ALARMA>2
const struct FstBoxPointer tipoLazoAlarma2={
  (const struct ConstructorBox*)&cBoxesTipoLazo,&alarma2,3
};
const struct FstBoxPointer modosAlarma2={
  (const struct ConstructorBox*)&cBoxesAlarma,&alarma2,3
};
const struct FstBoxPointer ctrlAlarma2={
  (const struct ConstructorBox*)&cBoxesAlarmaCtrl,&alarma2,3
};
#endif
#endif

static const struct FstBoxPointer *const setArray[]={
  &modosSalida0,
  #if CANTIDAD_CANALES>1
  &modosSalida1,
  #endif
  &tipoLazoAlarma0,
  &modosAlarma0,
  &ctrlAlarma0,
  #if CANTIDAD_SAL_ALARMA>1 || CANTIDAD_CANALES>1 
  &tipoLazoAlarma1,
  &modosAlarma1,
  &ctrlAlarma1,
  #if CANTIDAD_SAL_ALARMA>2
  &tipoLazoAlarma2,
  &modosAlarma2,
  &ctrlAlarma2,
  #endif
  #endif
  &setCList
    
};

static const NEW_BOX_LIST(set,setArray,"ConFigurAcion");

//LIMITES        
#if CANTIDAD_CANALES==1 
const struct FstBoxPointer limites0={
  (const struct ConstructorBox*)&cBoxesLimites,&control0,0
};
#else
const struct FstBoxPointer limites0={
  (const struct ConstructorBox*)&cBoxesLimites,&control0,1
};
const struct FstBoxPointer limites1={
  (const struct ConstructorBox*)&cBoxesLimites,&control1,2
};
#endif

static const struct FstBoxPointer *const limArray[]={
  &limites0,
  #if CANTIDAD_CANALES>1
  &limites1,
  #endif
  
    
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
  
  #if CANTIDAD_CANALES>1  
  BoxPrincipalControl::MostrarGetter((ConstructorPropGetterVisual *)&cPropiedadGetSensor1,&control1); 
  #else
  BoxPrincipalControl::MostrarProp((ConstructorPropGetterVisual *)&cPropiedadSetPoint,&control0);
  #endif
  RlxMTimer timerConexionSalidas(SALIDA_TIEMPO_DESCONECTADA,timerSalida);
  timer=&timerConexionSalidas;
  DiagramaNavegacion d(&opList,&accessList,FrenteDH::getInstancia());
  PE_low_level_init();
  #if CANTIDAD_CANALES==1
   //control0.addOnTipoSalidaListener(cambioTipoSalida);
   (*(ControlPID*)(control0.getControl())).addOnTipoSalidaListener(cambioTipoSalida);
  #elif CANTIDAD_CANALES==2 
  control1.addOnTipoSalidaListener(cambioTipoSalida);
  #endif
  
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
 
  ((RlxMTimer *)timer)->stop();
   pwm23.setConectada(TRUE);
   pwm23.setPeriodo(pwm23.getPeriodo());        // seteo el periodo inicial
   pwm2.setConectada(TRUE);
   pwm2.setTipoSalida(SALIDA_ONOFF);
   
   #if CANTIDAD_SAL_ALARMA>1 || CANTIDAD_CANALES>1 
   pwm3.setConectada(TRUE);
   pwm3.setTipoSalida(SALIDA_ONOFF);
   
   #endif 
   #if CANTIDAD_SAL_ALARMA>2 || CANTIDAD_CANALES>1
    pwm4.setConectada(TRUE);
    pwm4.setTipoSalida(SALIDA_ONOFF);
    
   #endif 
}



void OnTipoSalChange(void * b){
  #if CANTIDAD_CANALES == 1 
  static MessagesOut::Message msj_on_sal_change;  
  if((*(ControlPID*)(control0.getControl())).getModoSalida()==ControlPID::_MAN/*control0.getModoSalida()==ControlPID::_MAN*/){
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
  #elif CANTIDAD_CANALES == 2 
  if(control1.getModoSalida()==ControlPID::_MAN){
    pwm2.setTipoSalida(SALIDA_PROPORCIONAL);   
     
  }else{
    pwm2.setTipoSalida(SALIDA_ONOFF);
    
  }
  #endif
}

