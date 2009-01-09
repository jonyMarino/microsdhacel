
/* TestControl.c*/
#include <stddef.h>

#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "Object.h"
#include "ClassADC.h"
#include "Grabacion.h"
#include "PWM.h"
#include "DiagramaNavegacion.h"
#include "PWM_Hmi.h"
#include "SnsHmi.h"
#include "BoxProp.h"
#include "Sets.h"
#include "Sensores.h"
#include "SensorTPT_Class.h"
#include "ControlPID.h"
#include "PidHmi.h"
#include "PropNumPV.h"
#include "MessagesOut.h"
#include "ModBusHmi.h"
#include "com_events.h"
#include "BoxPrincipalNC.h"
#include "FlashBkpEnFlash.h"
#include "Termometro.h"
#include "timer_interrupt.h"
#include "FstBoxPointer.h"
#include "BoxList.h"
#include "Access.h"
#include "AlarmaControl.h"
#include "RlxMTimer.h"
#include "LedsSalida.h"
#include "ThreadAdjuntable.h"
#include "Thread.h"
#include "AlarmaControlVista.h"
#include "PWMPeriodoEvent.h"
#include "SensorSimulado.h"
#include "ManejadorImpresionPersistente.h"
#include "System.h"
#include "OutputStream.h"
#include "dateTimeVista.h"
#include "manejadorImpresionVista.h"
#include "PWMManager01_45.h"
#include "termio.h"
#include "MIPConf.h"
#include "EPM203Manejador.h"
#include "EPM203ManejadorVista.h"

/* Definiciones */

/*  Tiempo inicial en el que el control permanece desconectado  */
#ifdef _COLADA_CALIENTE  
  #define SALIDA_TIEMPO_DESCONECTADA 20000 
#else
  #define SALIDA_TIEMPO_DESCONECTADA 3000   //tiene que alcanzar para hacer 2 mediciones
#endif

/* Prototipos */
void SD100_conectarSalidas(void * self);

/* Variables */
struct Termometro termometro;

#pragma CONST_SEG PARAMETERS_PAGE
volatile const TConfPWM pwm_config[CANTIDAD_SAL_ALARMA+CANTIDAD_SAL_CONTROL];
volatile const ConfiguracionTermometro termometro_config={
  STPT_DEF_CONF
};
volatile const ControlConf control_conf[CANTIDAD_SAL_CONTROL]={
  ControlDefaultConf
};
volatile const struct AlarmaCntrConf alar_conf[CANTIDAD_SAL_ALARMA];
volatile const struct MIPConf mIConf={
  5,
  FALSE
};
volatile const struct EPM203Conf EPMConf={
  0,1
};

#pragma CONST_SEG DEFAULT



struct PWM * pwm[CANTIDAD_SAL_ALARMA+CANTIDAD_SAL_CONTROL];
struct PWMPeriodoEvent pwmConEventoPeriodo[CANTIDAD_SAL_CONTROL];
struct TAdc  AD1[CANTIDAD_CANALES];
struct AlarmaControl alarma[CANTIDAD_SAL_ALARMA];
struct ControlPID control[CANTIDAD_SAL_CONTROL]; 



struct ManejadorImpresionPersistente manejadorImpresion;
					

       
static struct MessageOut msj[CANTIDAD_SAL_CONTROL];
struct EPM203Manejador os;

const struct BlockConstBoxPri1c CBox_Pri={
      &BoxPri1c,							/* funcion que procesa al box*/
      &termometro.sensor[0],      
      msj						
};

/*  Diagrama de navegacion  */
//Operador
//Principal
static const NEW_FST_BOX_POINTER(Principal,&CBox_Pri,NULL,0);
//Control
static const NEW_FST_BOX_POINTER(Cntrl1OP1,&PID_HMI_FST_OP_BOX,&control[0],0);
static const NEW_FST_BOX_POINTER(Cntrl1OP2,&PID_HMI_SCND_OP_BOX,&control[0],0);
//Alarma
static const NEW_FST_BOX_POINTER(AL1OP,&ALARMA_DE_SENSOR_HMI_FST_OP,&alarma[0],0);

//Printer  
static const NEW_FST_BOX_POINTER(PrnHabilitar,&MANEJADOR_IMPRESION_BOX_HABILITAR,&manejadorImpresion,0);

static const struct FstBoxPointer *const OpArray[]={
  &Principal,
  &Cntrl1OP1,
  &Cntrl1OP2,    
  &AL1OP,  
  &PrnHabilitar 
};


static const NEW_BOX_LIST(OpList,OpArray,"op");

//PRN
static const NEW_FST_BOX_POINTER(DateTimeList,&DATE_TIME_BOX,&baseTiempo,0);
static const NEW_FST_BOX_POINTER(manejadorImprList,&MANEJADOR_IMPRESION_BOX,&manejadorImpresion,0);
static const NEW_FST_BOX_POINTER(manejadorepm203,&MANEJADOR_EPM_203_BOX,&os,0);

static const struct FstBoxPointer *const PrnArray[]={
  &DateTimeList,
  &manejadorImprList,
  &manejadorepm203
};

static const NEW_BOX_LIST(Prn,PrnArray,"iMPreSion");

//CAL
static const NEW_FST_BOX_POINTER(Sensor1List,&SNS_HMI_FST_BOX,&termometro.sensor[0],0);
  
static const struct FstBoxPointer *const CalArray[]={
  &Sensor1List   
};

static const NEW_BOX_LIST(Cal,CalArray,"CAL");

//TUN
static const NEW_FST_BOX_POINTER(Cntrl1Tun1,&PID_HMI_FST_TUN_BOX,&control[0],0);
static const NEW_FST_BOX_POINTER(Cntrl1Tun2,&PID_HMI_SCND_TUN_BOX,&control[0],0);
static const NEW_FST_BOX_POINTER(PWM1Tun,&PWM_VISTA_FST_TUN_BOX,&pwmConEventoPeriodo[0],0);


  //Alarma
static const NEW_FST_BOX_POINTER(AL1TUN,&ALARMA_DE_SENSOR_HMI_FST_TUN,&alarma[0],0);
  
static const struct FstBoxPointer *const TunArray[]={
  &Cntrl1Tun1, 
  &PWM1Tun,
  &Cntrl1Tun2, 
  &AL1TUN,
};

static const NEW_BOX_LIST(Tun,TunArray,"tun");

//SET
  //Control
static const NEW_FST_BOX_POINTER(Cntrl1Set,&PID_HMI_FST_SET_BOX,&control[0],0);

  //Alarma
static const NEW_FST_BOX_POINTER(AL1SET,&ALARMA_DE_SENSOR_HMI_FST_SET,&alarma[0],0);

  //Comunicacion
static const NEW_FST_BOX_POINTER(ModBusSet,&MOD_BUS_HMI_FST_BOX_SET,0,0);
  //SetC
static const NEW_FST_BOX_POINTER(SetsSet,&SETS_FST_BOX_SET,0,0);
  

static const struct FstBoxPointer *const SetArray[]={
  &Cntrl1Set, 
  &AL1SET,
  &ModBusSet,
  &SetsSet  
};

static const NEW_BOX_LIST(Set,SetArray,"SEt");

//LIM
static const NEW_FST_BOX_POINTER(Cntrl1Lim,&PID_HMI_FST_LIM_BOX,&control[0],0);

static const struct FstBoxPointer *const LimArray[]={
  &Cntrl1Lim 
};

static const NEW_BOX_LIST(Lim,LimArray,"Lim");

// Acceso comun
static const struct BoxList *const BoxListArray[]={
  &Prn,
  &Tun,
  &Cal,
  &Set,
  &Lim
};

static const NEW_ACCESS(accesoComun,BoxListArray,"Cod",CONTENEDOR_CODIGO);

static const struct Access *const AccessArray[]={
  &accesoComun
};

static const NEW_ARRAY_LIST(AccessList,AccessArray);


/****************/


NEW_FLASH_BKP_EN_FLASH(flash,0x4400);
struct ManejadorMemoria *const pFlash= &flash;

void OnTSalChange(void * self, void * controlSender){
  extern const struct ConstrGetterNum GetterPIDPot;
  extern const struct ConstPropNumPV ParSP;
  static Message msj_on_sal_change[CANTIDAD_SAL_CONTROL];
  int numControl= ((int)control - (int)controlSender)/sizeof(struct ControlPID) ;
  
  
  if(PID_getModSal(controlSender)==_MAN){
    BoxPri1c_ShowGetter(&GetterPIDPot,&control[0]);			 // no muestro 
    if(!msj_on_sal_change[numControl])
      msj_on_sal_change[numControl]=MessageOut_AddMessage(&msj[numControl],"MAn ");    
  }else{
        BoxPri1c_ShowProp(&ParSP,&control[0]);
    if(msj_on_sal_change[numControl]){
      MessageOut_DeleteMessage(&msj[numControl],msj_on_sal_change[numControl]);
      msj_on_sal_change[numControl]=NULL;
    }
  } 
}

struct RlxMTimer timerConexionSalidas;

struct ThreadAdjuntable mainThread;

void pthread_create(void * _self,void * attr,void*(*pf)(void*),void* args){
  _self = new(&Method,pf,args);
  ThreadAdjuntable_Adjuntar(&mainThread,_self);  
}


const LedConfig configuracionLedsSalida[]= {
  &PTIP,1<<1,0,
  &PTIP,1<<5,2 
};


NEW_LEDS_SALIDA(ledsSalida,configuracionLedsSalida);


void ControlSD100_procesar(uchar tecla){
  int i;
  if(tecla == 'k'){
      for(i=0;i<CANTIDAD_SAL_ALARMA;i++) {
        
        struct Lazo * lazo=_AlarmaControl_getLazo(&alarma[i]);
        if(instanceOf(lazo,&LazoAlarmaControl)){
          struct AdaptacionSalida * adaptador = _LazoControl_getAdaptadorSaldia(lazo);
          if(instanceOf(adaptador,&SalidaRetenida))
            SalidaRetenida_liberar((struct SalidaRetenida *)adaptador);   
        }
      }
  }
  
  DN_Proc(tecla);
}


void main (void){
  char tecla; 
  bool prevVal;
  byte i;
  
  newAlloced(&termometro,Termometro,&termometro_config,&flash);
  Teclas_Init();
  Display_Init(); // Inicializacion del display
  System_init();
  TERMIO_Init();

  add1msListener(DpyAndSwitch,NULL);

  //for(i=0;i<CANTIDAD_SAL_ALARMA+CANTIDAD_SAL_CONTROL;i++)
  //  newAlloced(&pwm[i],PWM,&pwm_config[i],i);
  /*PWM0*/
  newAlloced(&pwmConEventoPeriodo[0],&PWMPeriodoEvent,PWMManager01_45_get01(&pwm_config[0]));
  pwm[0]= &pwmConEventoPeriodo[0];
  /*PWM1*/
  pwm[1]=PWMManager01_45_get45(&pwm_config[1]);
  
  
  newAlloced(&mainThread,ThreadAdjuntable);
 
/*  {
    struct AdjuntadorAHilo* adj= ThreadAdjuntable_getAdjuntador(&mainThread);
    for(i=0;i<CANTIDAD_SAL_CONTROL+CANTIDAD_SAL_ALARMA;i++){      
      newAlloced(&sen[i],SensorSimulado,0,adj,1000,"Sen1");
      SensorSimulado_setValue(&sen[i],100);
    }
    deleteAndNil(&adj);
  }
  */
  
  for(i=0;i<CANTIDAD_SAL_CONTROL;i++)
    newAlloced(&control[i],ControlPID,&control_conf[i],&termometro.sensor[i],pwm[i]);

  for(i=0;i<CANTIDAD_SAL_ALARMA;i++)
    newAlloced(&alarma[i],&AlarmaControlClass,&alar_conf[i],&control[i],pwm[i+CANTIDAD_SAL_CONTROL]);

  newAlloced(&os,&EPM203Manejador,&EPMConf);
  newAlloced(&manejadorImpresion,&ManejadorImpresionPersistente,&os,&mIConf);
  LinkedList_add(&manejadorImpresion,&termometro.sensor[0]);
 
  for(i=0;i<CANTIDAD_SAL_CONTROL;i++){   
    newAlloced(&msj[i],MessageOut);
    PID_AddOnTSalChange(&control[i],OnTSalChange,NULL); 
  }

   
   
  //Conectar salidas dentro de SALIDA_TIEMPO_DESCONECTADA ms
  newAlloced(&timerConexionSalidas,&RlxMTimer,(ulong)SALIDA_TIEMPO_DESCONECTADA,SD100_conectarSalidas,NULL);
  //configurar leds
  LedsSalida_init(&ledsSalida);
   
  //Diagrama de navegacion
  DN_staticInit(&OpList,&AccessList);
														 
  for(;;){
    tecla=get_key();  
    //Eventos
    
    ControlSD100_procesar(tecla);

    Termometro_mainLoop(&termometro);
    
    RlxMTimer_Handler();
    
    MethodContainer_execute(&mainThread);
  }
}


void SD100_conectarSalidas(void * self){
  byte i;
  for(i=0;i<CANTIDAD_SAL_ALARMA+CANTIDAD_SAL_CONTROL;i++)
    setConectada(pwm[i],TRUE);
  
  Timer_Stop(&timerConexionSalidas);  
}



