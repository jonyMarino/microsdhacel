/* PARAMETROS de calibracion */
/*****************************/

#include "Mydefines.h"
#include "cnfbox.h"
#include "boxes.h"
#include "Programador.h"
#include "PE_Types.h"
#include "Sensores.h"
#include "boxescal.h"

#pragma CONST_SEG DEFAULT 
#pragma STRING_SEG DEFAULT

const Textual TipoSensor1;
const Numerico Offset1;
const Numerico Ganancia1;
//const Textual Filtro1;
const Numerico Filtro1;

#if  CANTIDAD_CANALES>1
const Textual TipoSensor2;
const Numerico Offset2;
const Numerico Ganancia2;
const Numerico Filtro2;
#endif

const Numerico ACT1;
const Numerico AGT1;
const Numerico ATA1;
const Numerico ACP1;
const Numerico AGP1;
const Numerico AAnlLow1;
const Numerico AAnlHi1;

#if  CANTIDAD_CANALES>1
const Numerico ACT2;
const Numerico AGT2;
const Numerico ACP2;
const Numerico AGP2;
#endif
/* tipo de sensor canal 1 */
/**************************/
#ifdef _APARATO_VIEJO 
const char  * const T_Sensores[NUM_SENSORES]={
      "Jb  ",
      "JA  ",									
			"n   ",/* Pltinel*/
			"kb  ",
			"kA  ",
			"S   ",
			"r   ",		/*K S r t Pt Lin1234*/
			"t   ",
			"Pt  ",
			#ifdef pirani
			"Pir ",
      "Pr1 ",
			#endif
			"Lin1",
			"Lin2",
			"Lin3",
			"Lin4",
			"MiLV",
};
#else
const char  * const T_Sensores[NUM_SENSORES]={
      "J   ",									
			"n   ",
			"k   ",
			"S   ",
			"r   ",
			"t   ",
			"Pt  ",
			#ifdef pirani
			"Pir ",
			#endif
			"Lin ",
			"MiLV",
};
#endif
const Textual TipoSensor1=
      {
      TxtHandler,						            /* funcion que procesa al box*/
			&Parametros[R_Sensor],					  /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"SEn1",									          //nombre display
			T_Sensores,                       // Array donde estan los textos
			NULL,						                  //parametro que modifica.
			(PunteroF*)&Offset1.DirProc,NULL	//Proximos estados
			};
			

/* offset canal1*/
const Numerico Offset1={
      NumHandler,					              /* funcion que procesa al box*/
      &Parametros[R_Offset],						/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"oFS1",							              //nombre display
			DECIMALES_CANAL1,									/* punto decimal a enc */
			NULL,					                    //parametro que modifica.
 			(PunteroF*)&Ganancia1.DirProc,NULL//Proximos estados
			};
			
			
/* ganancia*/
const Numerico Ganancia1={
      NumHandler,						            /* funcion que procesa al box*/
      &Parametros[R_Gan],								/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"gAn1",								            //nombre display
			3,										            /* punto decimal a enc */
			NULL,						                  //parametro que modifica.
			(PunteroF*)&Filtro1.DirProc,&ACT1.DirProc	//Proximos estados
			};
		
/*ajuste cero canal 1*/
const Numerico ACT1={
      NumHandler,									      /* funcion que procesa al box*/
      &Parametros[R_ACT],								/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"AC 1",							              /* texto del titulo */
			DECIMALES_CANAL1,									/* punto decimal a enc */
			NULL,									            //Parametro que modifica
			(PunteroF*)&AGT1.DirProc,NULL			//Proximos estados
			};

/*ajuste gan canal 1*/
const Numerico AGT1={
      NumHandler,									      /* funcion que procesa al box*/
      &Parametros[R_AGT],								/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"Ag 1",							              /* texto del titulo */
			1,													      /* punto decimal a enc */
			NULL,									            //Parametro que modifica
			(PunteroF*)&ACP1.DirProc,NULL			//Proximos estados
			};

/*ajuste cero Pt100 canal 1*/			
const Numerico ACP1={
      NumHandler,									      /* funcion que procesa al box*/
      &Parametros[R_ACP],								/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"ACP1",							              /* texto del titulo */
			DECIMALES_CANAL1,									/* punto decimal a enc */
			NULL,									            //Parametro que modifica
			(PunteroF*)&AGP1.DirProc,NULL			//Proximos estados
			};

/*ajuste gan Pt100 canal 1*/		
const Numerico AGP1={
      NumHandler,									      /* funcion que procesa al box*/
      &Parametros[R_AGP],								/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"AGP1",							              /* texto del titulo */
			1,													      /* punto decimal a enc */
			NULL,									            //Parametro que modifica
//	(PunteroF*)&AAnlLow1.DirProc,NULL	//Proximos estados
  	(PunteroF*)&ATA1.DirProc,NULL			//Proximos estados

			};			

/*ajuste minimo retr alarma */		
const Numerico AAnlLow1={
      NumHandler,									      /* funcion que procesa al box*/
      &Parametros[R_AAnlLow],						/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"AnL ",							              /* texto del titulo */
//  	1,													      /* punto decimal a enc */
      DECIMALES_CANAL1,
			NULL,									            //Parametro que modifica
			(PunteroF*)&AAnlHi1.DirProc,NULL	//Proximos estados
			};			

/*ajuste maximo retr alarma */		
const Numerico AAnlHi1={
      NumHandler,									      /* funcion que procesa al box*/
      &Parametros[R_AAnlHi],						/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"AnH ",							              /* texto del titulo */
//		1,													      /* punto decimal a enc */
      DECIMALES_CANAL1,
			NULL,									            //Parametro que modifica
//	(PunteroF*)&ATA1.DirProc,NULL			//Proximos estados
    (PunteroF*)&Principal1.DirProc,NULL
			};			

/*ajuste temp ambiente*/		
const Numerico ATA1={
      NumHandler,									      /* funcion que procesa al box*/
      &Parametros[R_ATA],								/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"AtA ",							              /* texto del titulo */
			1,													      /* punto decimal a enc */
			NULL,									            //Parametro que modifica
			(PunteroF*)&Ganancia1.DirProc,NULL//Proximos estados
			};

/* filtro canal 1 */
const Numerico Filtro1={
      NumHandler,									      /* funcion que procesa al box*/
      &Parametros[R_Filtro1],						/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"FiL1",							              /* texto del titulo */
			1,													      /* punto decimal a enc */
			NULL,									            //Parametro que modifica
#if CANTIDAD_CANALES>1
			(PunteroF*)&TipoSensor2.DirProc,NULL//Proximos estados
#else

    	(PunteroF*)&AAnlLow1.DirProc,NULL	//Proximos estados
//  	(PunteroF*)&Principal1.DirProc,NULL //Proximos estados
#endif
			};
  
#if CANTIDAD_CANALES>1

/* tipo de sensor canal 2*/		
const Textual TipoSensor2=
      {TxtHandler,						          /* funcion que procesa al box*/
			&Parametros[R_Sensor+1],					/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"SEn2",									          //nombre display
			T_Sensores,                       // Array donde estan los textos
			NULL,							                //parametro que modifica.
			(PunteroF*)&Offset2.DirProc,NULL	//Proximos estados
			};
	
/* offset canal2*/
const Numerico Offset2={
      NumHandler,					              /* funcion que procesa al box*/
      &Parametros[R_Offset+1],					/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"oFS2",							              //nombre display
			DECIMALES_CANAL2,									/* punto decimal a enc */
			NULL,					                    //parametro que modifica.
			(PunteroF*)&Ganancia2.DirProc,NULL//Proximos estados
			};

/* ganancia canal 2*/
const Numerico Ganancia2={
      NumHandler,						            /* funcion que procesa al box*/
      &Parametros[R_Gan+1],							/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"gAn2",								            //nombre display
			3,										            /* punto decimal a enc */
			NULL,						                  //parametro que modifica.
			(PunteroF*)&Filtro2.DirProc,&ACT2.DirProc//Proximos estados
			};

/* filtro canal 2 */
const Numerico Filtro2={
      NumHandler,									      /* funcion que procesa al box*/
      &Parametros[R_Filtro1+1],					/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"FiL2",							              /* texto del titulo */
			1,													      /* punto decimal a enc */
			NULL,									            //Parametro que modifica
//	(PunteroF*)&Principal1.DirProc,NULL//Proximos estados
  	(PunteroF*)&AAnlLow1.DirProc,NULL	//Proximos estados

			};

/*ajuste cero canal 2*/
const Numerico ACT2={
      NumHandler,									      /* funcion que procesa al box*/
      &Parametros[R_ACT+1],							/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"AC 2",							              /* texto del titulo */
			DECIMALES_CANAL2,									/* punto decimal a enc */													      /* punto decimal a enc */
			NULL,									            //Parametro que modifica
			(PunteroF*)&AGT2.DirProc,NULL			//Proximos estados
			};

/*ajuste gan canal 2*/			
const Numerico AGT2={
      NumHandler,									      /* funcion que procesa al box*/
      &Parametros[R_AGT+1],							/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"Ag 2",       							      /* texto del titulo */
			1,													      /* punto decimal a enc */
			NULL,									            //Parametro que modifica
			(PunteroF*)&ACP2.DirProc,NULL			//Proximos estados
			};


/*ajuste cero Pt100 canal 2*/		
const Numerico ACP2={
      NumHandler,									      /* funcion que procesa al box*/
      &Parametros[R_ACP+1],							/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"ACP2",							              /* texto del titulo */
			DECIMALES_CANAL2,						      /* punto decimal a enc */
			NULL,									            //Parametro que modifica
			(PunteroF*)&AGP2.DirProc,NULL			//Proximos estados
			};


/*ajuste gan Pt100 canal 2*/		
const Numerico AGP2={
      NumHandler,									      /* funcion que procesa al box*/
      &Parametros[R_AGP+1],							/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"AGP2",							              /* texto del titulo */
			1,													      /* punto decimal a enc */
			NULL,									            //Parametro que modifica
			(PunteroF*)&Ganancia2.DirProc,NULL//Proximos estados
			};
#endif			