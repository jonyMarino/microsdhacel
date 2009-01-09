#include "Mydefines.h"
#include "PE_Types.h"
#ifdef _BUTTON_CHANEL_HMI 
#include "boxes_HMI2.h"
#endif
#include "boxes.h"

#include "Programador.h"
#include "boxesprog.h"
#include "boxesadq.h"
#include "boxestun.h"
#include "boxescal.h"
#include "friend_boxesset.h"
#include "boxesset.h"
#include "boxeslim.h"
#include "cnfbox.h"
#include "friend_parametros.h"
#ifdef _COLADA_CALIENTE
  #include "ControlCC.h"
  #include "friend_boxes_cc.h"
#else
  #include "Control.h"
#endif

#include "Sensores.h"
#pragma CONST_SEG DEFAULT 
#pragma STRING_SEG DEFAULT


/* Definicion de las estructuras de los boxes de navegacion */
/************************************************************/
/*		void(*DirTask)(void);		funcion que ejecuta tareas especiales de c/box*/

/************************************/
/* Definicion y armado de los boxes */
/************************************/
const NumericoJumpCond Principal1;
const NumRO_JmpCond BoxPotActual;
const Numerico3 C1SP;
const Numerico1 C1POT;
const Numerico1 AL1;
const Numerico1 AL2;
const Numerico1 AL3;
const Numerico1 P1;
/*#ifndef prog_viejo
const NumericoRO Segmento1;
const NumericoRO SegundosSegmento1;
#else*/
const Numerico1 Segmento1;
const Numerico1 SegundosSegmento1;
/*#endif		 */

#if defined( PROG_SIMPLE_RSTP) && defined(jony_24_08)
const NumericoRO1 Box_RTSP_MinutosMeseta;
const Numerico1 Box_RTSP_Velocidad;
const Numerico1 Box_RTSP_Set_Point;	
const Numerico1 Box_RTSP_Tiempo;
#endif


#if  CANTIDAD_CANALES>1
const Numerico1 C2SP;
const Numerico1 C2POT;
const Numerico1 C2AL1;
const Numerico1 P2;
#endif

const Numerico2 Codigo1;

const Titulo Sintonia;

const Titulo Calibracion;

const Titulo Setting;

const Titulo Limites;

#ifdef _COLADA_CALIENTE
const Titulo Box_TitColada;
#endif

#ifdef _PROGRAMADOR
const Titulo Programas;
#endif

#ifdef adquisidor
const Titulo Adquisicion;

#endif							


								
/* pantalla principal */
/*****************************/
PunteroF Principal_siguiente (byte tecla){
  if(tecla=='r'){
    #ifdef PROG_SIMPLE_RSTP
      if(get_Version()==VER_RTSP)
        return (PunteroF)&Box_RTSP_MinutosMeseta;
      else  
    #endif
    
    #ifdef _PROGRAMADOR
      if(get_Programa(0)!=CONF_NO_PROGRAMA)
        return (PunteroF)&Segmento1;
      else
    #endif
      if (get_Version()==VER_BL2)
        return (PunteroF)&Sintonia;
      else
        return (PunteroF)&BoxPotActual;
  }
  return (PunteroF)&Codigo1; 
}

const NumericoJumpCond Principal1={
      MainHandler,								/* funcion que procesa al box*/
			"Pri ",											/* texto del titulo */
      &ParSP,					/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			1,
			DECIMALES_CANAL1,													/* punto decimal a enc */
			Principal_siguiente
			
};

PunteroF  PotActual_siguiente(byte tecla){
  if(tecla=='r'){
    if(CNTR_getModSal(0)==_MAN)
      return (PunteroF)&C1POT;
    return (PunteroF)&C1SP;
  }return NULL;
};
/*  Potencia Actual */
const NumRO_JmpCond BoxPotActual={
  		ProcNumRO_JmpCond,
  		"Pot ",
  		CNTR_getPotActual,
  		CANTIDAD_SAL_CONTROL,
  		1,  //digito
  		PotActual_siguiente
};
 
/*setpoints y alarmas*/			
/*****************************/
const PunteroF R_C1SP[3]={
      (PunteroF)&AL1,						                        //Proximos estados
			(PunteroF)&AL1,						                        //Proximos estados
			(PunteroF)&C1POT,						                      //Proximos estados
};
const Numerico3 C1SP={
      #ifdef pirani
      NumExpoHandler,
      #else
      ProcNumerico3,									                      /* funcion que procesa al box*/
      #endif
			"SP 1",							                              /* texto del titulo */
      &ParSP,					                      /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			CANTIDAD_SAL_CONTROL,
			DECIMALES_CANAL1,						                      //pos punto dec
			get_TipoControl1,									        //Parametro que modifica
			R_C1SP						                            //Proximos estados
			};

const Numerico1 C1POT={
      ProcNumerico1,									                      /* funcion que procesa al box*/
			"Pot1",							                              /* texto del titulo */
      &ParPotencia,					                        /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			CANTIDAD_SAL_CONTROL,
			1,											                          //pos punto dec
  	  (PunteroF)&AL1						  //Proximos estados
			};
			

const Numerico1 AL1=	                                  //nombre variable
      {
      #ifdef pirani
      NumExpoHandler,
      #else
      ProcNumerico1,									                      /* funcion que procesa al box*/
      #endif						                          // funcion que procesa al box
			"A  1",							                              //nombre display
      &ParAL,										                  // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor
			CANTIDAD_SAL_ALARMA,
			DECIMALES_CANAL1,								                  //pos punto dec
			#ifdef _PROGRAMADOR
			(PunteroF)&P1			 //enter rap,enter mant
			#else
			(PunteroF)&Principal1			          //enter rap,enter mant		
			#endif
			};
								 
#ifdef _PROGRAMADOR

const Numerico1 P1 =	                                    //nombre variable
      {ProcNumerico1,						                          // funcion que procesa al box
			"P  1",							                              //nombre display
      &ParPrograma,											          // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor
			CANTIDAD_SAL_CONTROL,
			0,											                          //pos punto dec				                                //parametro que modifica. 
			(PunteroF)&Principal1			 //enter rap,enter mant
			};


/*#ifndef prog_viejo 

const NumericoRO Segmento1 =	                                    //nombre variable
      {ProcNumerico,						                          // funcion que procesa al box
      &SegmentoActual[0],											          // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor
			"SEG1",							                              //nombre display
			0,											                          //pos punto dec	
			&SegundosSegmento1,NULL			 //enter rap,enter mant
			};

const NumericoRO SegundosSegmento1 =	                                    //nombre variable
      {Num_realtime_Handler,	                          // funcion que procesa al box
      ((int *)&SegundosSegmento[0])+1,										          // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor
			"tIE1",							                              //nombre display
			0,											                          //pos punto dec
			&AL1,NULL			 //enter rap,enter mant
			};

#else		*/

const Numerico1 Segmento1 =	                                    //nombre variable
      {ProcNumerico1,						                          // funcion que procesa al box
			"SEG1",							                              //nombre display
      &ParSegmento,											          // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor
			CANTIDAD_SAL_CONTROL,
			0,											                          //pos punto dec	
			(PunteroF)&SegundosSegmento1			 //enter rap,enter mant
			};

const Numerico1 SegundosSegmento1 =	                                    //nombre variable
      {TieSegHandler,	                          // funcion que procesa al box
			"tIE1",							                              //nombre display
      &ParTiempoSegActual,										          // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor
			CANTIDAD_SAL_CONTROL,
			0,											                          //pos punto dec
			(PunteroF)&AL1			 //enter rap,enter mant
			};			
/*#endif*/

#if defined( PROG_SIMPLE_RSTP)

const NumericoRO1 Box_RTSP_MinutosMeseta =	                                    //nombre variable
      {RMP_DwellHandler,	                          // funcion que procesa al box
			"tIEMPo MESEtA    ",							                              //nombre display
      get_RunningDwellTime,										          // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor
			1,
			0,											                          //pos punto dec
			(PunteroF)&Box_RTSP_Velocidad			 //enter rap,enter mant
			};


const Numerico1 Box_RTSP_Velocidad =	                                    //nombre variable
      {ProcNumerico1,	                          // funcion que procesa al box
      &ParRTSP_VEL,										          // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor
			"VeLocidAd",							                              //nombre display
			1,
			PROG_PRESICION_VEL,											                          //pos punto dec
			(PunteroF)&Box_RTSP_Set_Point			 //enter rap,enter mant
			};			

const Numerico1 Box_RTSP_Set_Point =	                                    //nombre variable
      {ProcNumerico1,	                          // funcion que procesa al box
			"Set Point",							                              //nombre display
      &ParRTSP_SP,										          // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor
			1,
			DECIMALES_CANAL1,											                          //pos punto dec
			(PunteroF)&Box_RTSP_Tiempo			 //enter rap,enter mant
			};			

const Numerico1 Box_RTSP_Tiempo =	                                    //nombre variable
      {ProcNumerico1,	                          // funcion que procesa al box
			"tIEMPo",							                              //nombre display
      &ParRTSP_VEL,										          // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor
			1,
			0,											                          //pos punto dec
			(PunteroF)&Principal1			 //enter rap,enter mant
			};			

#endif  


#endif
			


/* Codigo */
/**********/
const TDato dCodigo={
  	 get_Lim_0,		/* Direccion donde se encuentra el dato*/			 
  	 EmptyFunction,					/* Funcion a llamar luego de la escritura del dato*/
  	 get_Lim_0,get_Lim_max_display,
};

const Numerico2 Codigo1={
      CodHandler,				/* funcion que procesa al box*/
			"cod ",				    //nombre display
      &dCodigo,						/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			1,
			0,								/* punto decimal a enc */
			#ifdef _PROGRAMADOR
			NULL,(PunteroF)&Programas			//Proximos estados en bl1, primero toque rápido luego toque prolongado
			#else
			NULL,(PunteroF)&Sintonia			//Proximos estados en bl1, primero toque rápido luego toque prolongado
			#endif
			};
			
						
/* Definicion de los titulos */
/*****************************/
#ifdef adquisidor
 
const Titulo Adquisicion={ 
      ProcTitle,										// funcion que procesa al box
			"MEM ",													//nombre display
			" -- ",													//nombre display
			#ifdef _PROGRAMADOR
			(PunteroF)&Adqui_State,(PunteroF)&Programas	//Proximos estados	
			#else
			(PunteroF)&Adqui_State,(PunteroF)&Sintonia		//Proximos estados	
			#endif
			};

#endif

#ifdef _PROGRAMADOR

const Titulo Programas={ 
      #ifdef prog_viejo
      ProcTitleProg,
      #else
      ProcTitle,										/* funcion que procesa al box*/
			#endif
			"ProG",													//nombre display
			" -- ",													//nombre display
		 #ifdef prog_viejo
		 (PunteroF)&Temp_i,
		 #else
		 (PunteroF)&Program,
		 #endif
		 (PunteroF)&Sintonia		//Proximos estados
			};
#endif


const Titulo Sintonia={ 
      ProcTitle,							/* funcion que procesa al box*/
			"tun ",										//nombre display
			" -- ",										//nombre display
			(PunteroF)&C1RES,(PunteroF)&Calibracion,					//Proximos estados
			};

const Titulo Calibracion={ 
      ProcTitle,						/* funcion que procesa al box*/
			"cAL ",									//nombre display
			" -- ",									//nombre display
			(PunteroF)&TipoSensor1,(PunteroF)&Setting  //Proximos estados
			};

//dan1001
#ifdef _APARATO_VIEJO
/*Set aparato viejo*/
/*******************/
const Titulo Setting={ 
      ProcTitle,									/* funcion que procesa al box*/
			"SEt ",												//nombre display
			" -- ",												//nombre display
			(PunteroF)&C1TSC,(PunteroF)&Limites				//Proximos estados
			};
#else
/*Set aparato nuevo*/
/*******************/
const Titulo Setting={ 
      ProcTitle,									/* funcion que procesa al box*/
			"SEt ",												//nombre display
			" -- ",												//nombre display
			(PunteroF)&C1CN,(PunteroF)&Limites				//Proximos estados
			};

#endif
//dan1001

const Titulo Limites={ 
      ProcTitle,										/* funcion que procesa al box*/
			"LiM ",													//nombre display
			" -- ",													//nombre display
			(PunteroF)&LimiteInferior1,
			#ifdef _COLADA_CALIENTE
			  (PunteroF)&Box_TitColada		//Proximos estados
			#else
			  (PunteroF)&Principal1		//Proximos estados			
			#endif
			};

#ifdef _COLADA_CALIENTE
const Titulo Box_TitColada={ 
      ProcTitle,										/* funcion que procesa al box*/
			"CCAL",													//nombre display
			" -- ",													//nombre display
			(PunteroF)&Box_CCPot,(PunteroF)&Principal1		//Proximos estados			
			};
#endif

/* fin  */


