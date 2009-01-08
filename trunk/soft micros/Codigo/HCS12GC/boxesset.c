/* PARAMETROS de "set" */
/***********************/
#include "Mydefines.h"
#include "cnfbox.h"
#ifdef _BUTTON_CHANEL_HMI 
#include "boxes_HMI2.h"
#endif
#include "boxes.h"
#include "IFsh10.h"

#include "Programador.h"
#include "PE_Types.h"
#include "Sensores.h"
#include "boxesset.h"
#include "friend_parametros.h"

#pragma CONST_SEG PARAMETERS_PAGE
volatile const int iSetC;
volatile const TVersion eVersion;
#pragma CONST_SEG DEFAULT


#pragma CONST_SEG DEFAULT 
#pragma STRING_SEG DEFAULT

const Textual1 C1CN;
const Textual1 C1TSC;
#ifdef _VP
  const Numerico1 BoxVpTime;
  const Numerico1 BoxVpDeadB;
#endif
const Textual1 C1AL1;
const Textual1 C1TAL1;
const Numerico1 Decimales1;
const Numerico1 ModMain;

const Textual1 Version1;
const Numerico1 Id;
const Numerico2 SetC;

/*Modo Control 1*/		
#ifndef _APARATO_VIEJO
const char * const T_Control[2]={
      "On-O",									
			"Pid ",
			};

const Textual1 C1CN=
      {
      ProcTextual1,						                  /* funcion que procesa al box*/
			"C  1",									                //nombre display
			&ParTipoControl,											/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/			
			CANTIDAD_SAL_CONTROL,
			T_Control,                       // Array donde estan los textos
			(PunteroF)&C1TSC					//Proximos estados
			};
#endif

/*Modo Salida 1*/		
const char * const T_Salcont[3]={
      "cAL ",									
			"rEF ",
			"MAn "
			};


const Textual1 C1TSC=
      {
      ProcTextual1,						                  /* funcion que procesa al box*/
			"C  1",									                //nombre display
			&ParTipoSalControl,											/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			CANTIDAD_SAL_CONTROL,
			T_Salcont,                       // Array donde estan los textos
			#ifdef _VP
			  (PunteroF)&BoxVpTime
			#else
			  (PunteroF)&C1AL1						//Proximos estados
			#endif
			};

#ifdef _VP
// Valvula Proporcional Tiempo///
const Numerico1 BoxVpTime={
      ProcNumerico1,
			"tIEMPo VALVuLA  ",
      &ParVpTime,
			1,
			0,
			(PunteroF)&BoxVpDeadB
			};
			
// Valvula Proporcional Dead Band///
const Numerico1 BoxVpDeadB={
      ProcNumerico1,
			"bAndA MuErtA  ",
      &ParVpDeadB,
			1,
			0,
			(PunteroF)&C1AL1
			};


#endif

/*Modo Alarma 1*/		

//dan1001
#ifdef _APARATO_VIEJO
/*Modos Alarma aparato viejo*/		
const char  * const T_Alar[6]={
      "E   ",									
			"d   ",
			"ErEt",
			"drEt",
			"dblk",
			"rEt "
			};
/*#define AL_EXCESO 0
#define AL_DEFECTO 1
#define _eret 2
#define _dret 3
#define _dbloq 4
#define _RET 5  */
#else
/*Modo Alarma aparato nuevo*/		
const char * const T_Alar[8]={
      "E   ",									
			"d   ",
			"ErEt",
			"drEt",
			"dbLK",
      "EPrP",
      "dPrP",
      "rEt "
			};
/*#define AL_EXCESO 0
#define AL_DEFECTO 1
#define _eret 2
#define _dret 3
#define _dbloq 4
#define _eprop 5
#define _dprop 6
#define _RET 7 */
#endif

//dan1001


const Textual1 C1AL1=
      {
      ProcTextual1,						                //funcion que procesa al box*/
			"A  1",									              //nombre display
			&ParTipoAlarma1,											//direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			CANTIDAD_SAL_ALARMA,
			T_Alar,                        //Array donde estan los textos
			(PunteroF)&C1TAL1				//Proximos estados
			};


/* Tipo de alarma 1*/
/*Tipo Alarma 1*/		
const char * const strs_Alarmas[6]={
	    "rEL ",									
			"AbS ",
			"rEFr",
			"bAn ",
			"SG  ",
			"EoC ",
};

#define REL 0
#define ABS 1
#define REFR 2
#define BAN 3
#define SEG 4
#define EOC 5


const Textual1 C1TAL1=
      {ProcTextual1,						            /* funcion que procesa al box*/
			"AL 1",									            //nombre display
			&ParTipoAlarma2,											/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			CANTIDAD_SAL_CONTROL,
			strs_Alarmas,
			(PunteroF)&Decimales1				//Proximos estados
			};



//dan
/*			#if CANTIDAD_CANALES>1
			&C2CN,NULL				//Proximos estados
			#else
			&Version1,NULL		//enter rap,enter mant
			#endif
*/
//dan
//			};


		
/* decimales1*///ATENCION!!! Siempre mostrarlos luego de elegir el sensor
const Numerico1 Decimales1={
      ProcNumerico1,					/* funcion que procesa al box*/
			"dec1",							//nombre display
      &ParDecimales,									/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			CANTIDAD_CANALES,
			0,									/* punto decimal a enc */
			(PunteroF)&Version1			//Proximos estados
};


/* version */	
static const char * const Bloqueos[6]={
		  "bL1 ",								 
			"bL2 ",
			"bL3 ",
			"bL4 ",
			"diF ",
		  "rtSP"
};

const Textual1 Version1=
      {ProcTextual1,					              /* funcion que procesa al box*/
			"VEr1",								              //nombre display
			&ParVersion,										    /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			1,
			Bloqueos,
			(PunteroF)&Id					//Proximos estados
			};
			


//Id///
const Numerico1 Id={
      ProcNumerico1,
			"id  ",
      &ParId,
			1,
			0,
			(PunteroF)&SetC
			};
			
/* Set Contraseña*/
/*****************/
const Numerico2 SetC={
      ProcNumerico1,
			"SetC",
      &ParSetC,
			1,
			0,
			(PunteroF)&Principal1,(PunteroF)&ModMain
			};
			
/* Para Cambiar Var a mostrar en dpy inferior*/
/*********************************************/
extern int SetPoint[],Dr; 
const int DirPar=(int)&SetPoint[0];
//const int DirPar=(int)&Dr;

#if defined(PROG_SIMPLE_RSTP)
  const Numerico2 ModMain={
#else
  const Numerico1 ModMain={
#endif 
      ProcNumerico1,
      "AMod",
      &ParVarMain,
			1,
			0,
			(PunteroF)&Principal1
			#if defined(PROG_SIMPLE_RSTP)
			,(PunteroF)&Programas
			#endif
};
			

/*    FUNCIONES DE SET											 */
/*********************************************/
//ModMain
int get_DirPar(byte a){
  return DirPar;
}

byte set_DirPar(int val,byte a){
  return EscribirWord((word)&DirPar,val);
}

int get_LimSup_DirPar(byte a){
  return 32767;
}

int get_LimInf_DirPar(byte a){
  return -32768;
}
//  SetC
int get_SetC(void){
  return iSetC;
}

byte set_SetC(int val, byte a){
  return EscribirWord((word)&iSetC,val);
}


			
// Version
int get_Version(void){
  return eVersion;
}

byte set_Version(int val, byte a){
  switch(val){
    #ifdef PROG_SIMPLE_RSTP
    case VER_RTSP:      //Ramp to Set Point 
      RMP_Init();  
      #endif
  }
  return EscribirByte((word)&eVersion,val);
}
		 
int get_LimSup_Version(void){
  return MAX_VALUE_VERSION;
}