#include "Mydefines.h"
#include "cnfbox.h"
#ifdef _BUTTON_CHANEL_HMI 
#include "boxes_HMI2.h"
#endif
#include "boxes.h"

#include "Programador.h"
#include "PE_Types.h"
//#include "boxestun.h"
#include "friend_parametros.h"


#pragma CONST_SEG DEFAULT 
#pragma STRING_SEG DEFAULT

//dan1001

//dan1001
#ifdef _APARATO_VIEJO
 /*  Auto sintonias aparato viejo*/
/*********************************/


//andy
/*
const char * Selftune[6]={
      "oFF ",									
			"Ston",
			"StoK",
			"SErr",
			"StoK",
			"SErr"
};
*/
const char * const Selftune[4]={
      "oFF ",									
			"on  ",
			"Auto",
			"SP  "
};


const Textual1 C1STN=
      {ProcTextual1,						         /* funcion que procesa al box*/
			"St 1",									         //nombre display
			&ParSelfTun,							 /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			CANTIDAD_SAL_CONTROL,
			Selftune,                        // Array donde estan los textos
			(PunteroF)&Principal1				//enter rap,enter mant			
 			};
#else
/*  Auto sintonias aparato nuevo*/
/********************************/
const PunteroF R_C1STN1[8]={
(PunteroF)&C1HA1,
(PunteroF)&C1HA1,
(PunteroF)&C1PRA1,
(PunteroF)&C1PRA1,
(PunteroF)&C1HA1,
(PunteroF)&C1HA1,
(PunteroF)&C1HA1,
(PunteroF)&Principal1
};

const PunteroF R_C1STN2[8]={
(PunteroF)&C1HA2,
(PunteroF)&C1HA2,
(PunteroF)&C1PRA2,
(PunteroF)&C1PRA2,
(PunteroF)&C1HA2,
(PunteroF)&C1HA2,
(PunteroF)&C1HA2,
&Principal1
};

const PunteroF R_C1STN3[8]={
(PunteroF)&C1HA3,
(PunteroF)&C1HA3,
(PunteroF)&C1PRA3,
(PunteroF)&C1PRA3,
(PunteroF)&C1HA3,
(PunteroF)&C1HA3,
(PunteroF)&C1HA3,
&Principal1
};

const char * const Selftune[6]={
      "oFF ",									
			"Ston",
			"StoK",
			"SErr",
			"StoK",
			"SErr"
};


const Textual3 C1STN=
      {ProcTextual3,						              /* funcion que procesa al box*/
			"St 1",									              //nombre display
			&ParSelfTun,											    /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			Selftune,                      // Array donde estan los textos
			get_TipoAlarma1,						    //parametro que modifica.
			R_C1STN1		                      //enter rap,enter mant
 			};
#endif
//dan1001


//dan1001
#ifdef _APARATO_VIEJO
/*  Histeresis/AnchoBanda Alarma1 para aparato viejo*/
/****************************************************/
const Numerico1 C1ABA1 =	                   //nombre variable
      {ABAHandler,						             /* funcion que procesa al box*/
			"AbA1",							                 //nombre display
      &ParHA,											   /* direccion en la E2Prom */
			CANTIDAD_SAL_ALARMA,
			DECIMALES_CANAL1,										 //pos punto dec
			(PunteroF)&C1STN				//enter rap,enter mant			
			};
#else
/*  Histeresis/AnchoBanda Alarma1 para aparato nuevo*/
/****************************************************/
const Numerico C1HA1 =	                    //nombre variable
      {NumHandler,						              /* funcion que procesa al box*/
      &ParHA,											    /* direccion en la E2Prom */
			"HA 1",							                  //nombre display
			DECIMALES_CANAL1,											//pos punto dec
      #if ALARMAS_CH1 > 1
 			(int *)&PRom[R_Talar1+1],						  //parametro que modifica.
			R_C1STN2,NULL		                      //enter rap,enter mant
      #else
			NULL,							                    //parametro que modifica. 
			(PunteroF)&Principal1,NULL		//enter rap,enter mant
      #endif
			};
			
const Numerico C1ABA1 =	                   //nombre variable
      {NumHandler,						             /* funcion que procesa al box*/
      &ParHA,											   /* direccion en la E2Prom */
			"AbA1",							                 //nombre display
			DECIMALES_CANAL1,										 //pos punto dec
      #if ALARMAS_CH1 > 1
 			(int *)&PRom[R_Talar1+1],						    //parametro que modifica.
			R_C1STN2,NULL		                      //enter rap,enter mant
      #else
			NULL,							                        //parametro que modifica. 
			(PunteroF)&Principal1,NULL				//enter rap,enter mant			
      #endif
			};

#endif
//dan1001

//dan1001
/*
#ifdef _APARATO_VIEJO
//  Histeresis/AnchoBanda Alarma2 para aparato viejo/
/ **************************************************** /
const Numerico1 C1ABA2 =	                   //nombre variable
      {ABAHandler,						             /* funcion que procesa al box/
			"AbA2",							                 //nombre display
      &Parametros1[R_HA1+1],											   /* direccion en la E2Prom /
			CANTIDAD_SAL_ALARMA,
			DECIMALES_CANAL1,										 //pos punto dec
      #if ALARMAS_CH1 > 2
			(PunteroF)&C1ABA3				//enter rap,enter mant			
      #else
			(PunteroF)&C1STN				//enter rap,enter mant			
      #endif
			};
#else
  
const Numerico C1HA2 =	                    //nombre variable
      {NumHandler,						              /* funcion que procesa al box/
      &Parametros1[R_HA1+1],											    /* direccion en la E2Prom /
			"HA 2",							                  //nombre display
			DECIMALES_CANAL1,											//pos punto dec
      #if ALARMAS_CH1 > 2
 			(int *)&PRom[R_Talar1+2],						  //parametro que modifica.
			R_C1STN2,NULL		                      //enter rap,enter mant
      #else
			NULL,							                    //parametro que modifica. 
			(const PunteroF*)&Principal1,NULL		//enter rap,enter mant
      #endif
			};
			
const Numerico C1ABA2 =	                   //nombre variable
      {NumHandler,						             /* funcion que procesa al box/
      &Parametros1[R_HA1+1],											   /* direccion en la E2Prom /
			"AbA2",							                 //nombre display
			DECIMALES_CANAL1,										 //pos punto dec
      #if ALARMAS_CH1 > 2
 			(int *)&PRom[R_Talar1+2],						    //parametro que modifica.
			R_C1STN3,NULL		                      //enter rap,enter mant
      #else
			NULL,							                        //parametro que modifica. 
			(PunteroF*)&Principal1,NULL				//enter rap,enter mant			
      #endif
			};


#endif
//dan1001



//dan1001
#ifdef _APARATO_VIEJO
/*  Histeresis/AnchoBanda Alarma3 para aparato viejo* /
/**************************************************** /
const Numerico1 C1ABA3 =	                   //nombre variable
      {ABAHandler,						             /* funcion que procesa al box* /
			"AbA3",							                 //nombre display
      &Parametros1[R_HA1+2],											   /* direccion en la E2Prom * /
			DECIMALES_CANAL1,										 //pos punto dec
			(PunteroF*)&C1STN				//enter rap,enter mant			
			};
#else
/*  Histeresis/AnchoBanda Alarma3 para aparato nuevo* /
/**************************************************** /
const Numerico1 C1HA3 =	                    //nombre variable
      {ProcNumerico1,						              /* funcion que procesa al box/
			"HA 3",							                  //nombre display
      &Parametros1[R_HA1+2],											    /* direccion en la E2Prom /
			DECIMALES_CANAL1,											//pos punto dec
			&Principal1		//enter rap,enter mant
			};
			
const Numerico1 C1ABA3 =	                   //nombre variable
      {ProcNumerico1,						             /* funcion que procesa al box/
			"AbA3",							                 //nombre display
      &Parametros1[R_HA1+2],											   /* direccion en la E2Prom /
			DECIMALES_CANAL1,										 //pos punto dec
			&Principal1				//enter rap,enter mant			
			};
#endif
//dan1001
*/
/* Periodo Alarma1*/
/******************/
const Textual1 C1PRA1=
      {ProcTextual1,						             /* funcion que procesa al box*/
			"PrA1",									             //nombre display
			&ParPeriodoAlarma,											   /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			CANTIDAD_SAL_ALARMA,
			Periodos,                     //Array donde estan los textos
			(PunteroF)&C1ABA1			 //Proximos estados			
			};

/*
const Textual1 C1PRA2=
      {ProcTextual1,						             // funcion que procesa al box* /
			"PrA2",									             //nombre display
			&Parametros1[R_Pra+1],											 // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor* /
			Periodos,                     //Array donde estan los textos
			(PunteroF)&C1ABA2			 //Proximos estados			
			};

// Periodo Alarma3* /
/ ****************** /
const Textual1 C1PRA3=
      {ProcTextual1,						             // funcion que procesa al box* /
			"PrA3",									             //nombre display
			&Parametros1[R_Pra+2],											 // direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor* /
			Periodos,                     //Array donde estan los textos
			(PunteroF*)&C1ABA3			 //Proximos estados			
			};

*/

