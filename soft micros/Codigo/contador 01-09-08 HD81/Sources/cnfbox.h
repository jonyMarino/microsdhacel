#ifndef _cnfbox_h
#define _cnfbox_h

#include "Mydefines.h"
#include "PE_Types.h"
#include "FormasConteo.h"
#include "BoxesStruct.h"
#include "boxes.h"
#pragma STRING_SEG DEFAULT


/* Definicion de las estructuras de los boxes de navegacion */
/************************************************************/
/*		void(*DirTask)(void);		funcion que ejecuta tareas especiales de c/box*/
#pragma DATA_SEG RAM_A_GRABAR
long Cuenta;
long TotCuenta;
long TotOnSPP;
long PreTotalizador;
byte ContFlags;
byte OverflowFlags;
word OverFlows;
#pragma DATA_SEG DEFAULT
long ValProc,ValDisp;

volatile const long SavedCuenta@0xC000;
volatile const long SavedTotCuenta@0xC004;
volatile const long SavedTotOnSPP@0xC008;
volatile const long SavedPreTotalizador@0xC00C;
volatile const byte SavedContFlags@0xC010;
volatile const byte SavedOverflowFlags@0xC011;
#pragma CONST_SEG ROM_VARS
volatile const long SP_Auxiliar=4;
volatile const long SP_Principal=3000;
volatile const long TiempoRele[2]={5000,5000};
volatile const long PuntoDecimal[1];
volatile const long FactorEscala[2]={10000,10000};		
volatile const long SetC;
volatile const long Id=1;
volatile const long PulsosXvuelta;
#pragma CONST_SEG ROM_BYTE
volatile const byte Sensor[1]=TRANSISTOR;
volatile const ModoSetPoint[2];
volatile const byte ModoRele[2];

volatile const byte RPM;
#pragma CONST_SEG DEFAULT
///VARIABLES EXTERNAS QUE UTILIZAN LOS BOXES //////////////
/////////////////////////////////
int Lim_Inf_ch[CANTIDAD_CANALES],Lim_Sup_ch[CANTIDAD_CANALES];
int Lim_Dec[CANTIDAD_CANALES];
const long Lim_m1999=-1999;
const long Lim_m1=-1;
const long Lim_0=0;
const long Lim_1=1;
const long Lim_5=5;
const long Lim_9=9;
const long Lim_10=10;
const long Lim_255=255;
const long Lim_600=600;
const long Lim_1000=1000;
const long Lim_9999=9999;
const long Lim_100000=100000;
const long Lim_999999=999999;

#ifdef adquisidor
const long Lim_12 = 12;
const long Lim_2006 = 2006;
const long Lim_2099 = 2099;
#endif

extern void CodHandler(void);

#ifdef TEST_MODE
extern long Entries;
#endif
//typedef void (**PunteroF)(void);
#define NULL ((void *) 0)


//tipos de boxes manipulados
union{
	Numerico * Num;
	Textual	* Txt;
	Titulo * Tit;	
	}PtrBox;

/* estas son las funciones que procesan el box correspondiente */
void TitleHandler(void);//manejador boxes de titulos
void NumHandler(void);  //manejador boxes tipo numérico
void Num_realtime_Handler(void);
void TxtHandler(void);  //manejador boxes tipo textual
void EstadoHandler(void); //manejador de las pantallas de estado
void MainHandler(void); //manejador Pantalla principal
void NumHandlerRam(void); //manejador de las pantallas numericas en ram
void TxtHandlerRam(void);

/************************************/
/* Definicion y armado de los boxes */
/************************************/
const Titulo B_Intro;
/*Principal*/
const Numerico B_Principal1;
const Numerico B_SP1;
const Numerico B_SP2;
const Numerico B_TOT1;
const Numerico B_TOT2;								
/*Cod*/
const Numerico B_Codigo;

/*Conf*/
const Titulo B_Configuracion;
const Textual B_TipoSensor1;
const Textual B_ModoSetPoint1;
const Textual B_ModoSetPoint2;
const Textual B_Rele1;
const Textual B_Rele2;
const Textual B_ModoCuenta1;
const Textual B_ModoCuenta2;
const Numerico B_TiempoRele1;
const Numerico B_TiempoRele2;
const Numerico B_PuntoDecimal1;
const Numerico B_FactorEscala1;
const Numerico B_FactorEscala2;

//#if !defined(_UN_SET_POINT)
#ifndef  _UN_SET_POINT
/*Entrada Set Point Auxiliar*/
const Textual Box_EntradaSPA;
/*Accion del Set Point Auxiliar*/
const Textual Box_AccionSPA;
#endif

/*Reset*/
const Titulo B_Reset;
const Textual B_ResetCuenta;
const Textual B_ResetTot1;
const Textual B_ResetTot2;
/*Set*/
const Titulo B_Set;
const Numerico B_SetC;
const Numerico B_Id;
/*RPM*/
const Titulo B_RPM_List;
const Textual B_RPM;
const Numerico B_Pulsos;

/*Intro*/
const Titulo B_Intro={ 
      TitleHandler,				/* funcion que procesa al box*/
			"- - - ",						//nombre display
			"dHACEL",						//nombre display
			NULL,								//parametro que modifica.
			NULL,NULL,					//Proximos estados
			};

/* pantalla principal */
/*****************************/

const Numerico B_Principal1={
      MainHandler,								  /* funcion que procesa al box*/
      #ifdef TEST_MODE
      &Entries,
      #else
      &SP_Principal,					        /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			#endif
			"Pri ",											  /* texto del titulo */
			DECIMALES_CANAL1,							/* punto decimal a enc */
			&Lim_0, &Lim_999999,					// Limites independientes
			NULL,								          // Parametro que decide el proximo estado
			(PunteroF*)&B_TOT1.DirProc,&B_Codigo.DirProc
};

/*Totalizadores y setpoints */			
/*****************************/

const Numerico B_TOT1={
      Num_realtime_Handler,					/* funcion que procesa al box*/
      &TotCuenta,					    /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"tot cu",							        /* texto del titulo */
			0,											      // pos punto dec
			&Lim_0, &Lim_999999,					// limites
			NULL,									        // Parametro que modifica
			(PunteroF*)&B_TOT2.DirProc,	NULL  // Proximos estados
			};
			
const Numerico B_TOT2={
      Num_realtime_Handler,					/* funcion que procesa al box*/
      &TotOnSPP,					    /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"tot  2",							        /* texto del titulo */
			0,											      // pos punto dec
			&Lim_0, &Lim_9999,						// limites
			NULL,									        // Parametro que modifica
			(PunteroF*)&B_SP1.DirProc,	NULL	//Proximos estados
			};
			

const Numerico B_SP1={
      NumHandler,									  /* funcion que procesa al box*/
      #ifdef _UN_SET_POINT
      &SP_Principal,
      "SP    ",
      #else
      &SP_Auxiliar,					        /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"SP1   ",
			#endif
			DECIMALES_CANAL1,							// pos punto dec
      #ifdef _UN_SET_POINT
      &Lim_0, &Lim_999999,
      #else
			&Lim_0, &SP_Principal,					// limites
			#endif
			NULL,									        // Parametro que modifica
			#ifdef _UN_SET_POINT
			(PunteroF*)&B_Principal1.DirProc,	NULL,	// Proximos estados
      #else
			(PunteroF*)&B_SP2.DirProc,	NULL				// Proximos estados
		  #endif	
			};


const Numerico B_SP2={
      NumHandler,									  /* funcion que procesa al box*/
      &SP_Principal,				          /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"SP2   ",							        /* texto del titulo */
			DECIMALES_CANAL1,							// pos punto dec
			&SP_Auxiliar, &Lim_999999,		// limites
			NULL,									        // Parametro que modifica
			(PunteroF*)&B_Principal1.DirProc,	NULL,	// Proximos estados
			};


/* Codigo */
/**********/

const Numerico B_Codigo={
     NumHandlerRam,				        /* funcion que procesa al box*/
       
     // CodHandler,


      &Lim_0,						            /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"Cod   ",				              // nombre display
			0,								            /* punto decimal a enc */
			&Lim_0, &Lim_9999,					  // limites
			NULL,						              // parametro que modifica.
			NULL,&B_Configuracion.DirProc	// Proximos estados en bl1, primero toque rápido luego toque prolongado
			
			
			};
			
						
/* Configuracion */
/*****************/
const Titulo B_Configuracion={ 
      TitleHandler,							    /* funcion que procesa al box*/
			" ConF ",										  // nombre display
			"  --  ",										  // nombre display
			NULL,								          // parametro que modifica.
			(PunteroF*)&B_TipoSensor1.DirProc,&B_Reset.DirProc,	//Proximos estados
			};

/*Tipo de Sensor*/
static const char TIPO_SENSOR[2][7]={
      "MicroS",
      "trAnS "									
};

 
const Textual B_TipoSensor1=
      {
      TxtHandler,						        // funcion que procesa al box
			(byte*)&Sensor[0],            // direccion en la E2Prom /
			"SEnSor",									    // nombre display
			2,											      // Cantidad de textos validos
			&TIPO_SENSOR[0],              // Array donde estan los textos
			NULL,						              // parametro que modifica.
			(PunteroF*)&B_ModoSetPoint1.DirProc,NULL					 //Proximos estados
			};
			
/*Accion del Set Point1*/
static const char ACCION_SET_POINT[2][7]={
      "EXcESo", 
      "dEFEct"									
};

 
const Textual B_ModoSetPoint1=
      {
      TxtHandler,						        // funcion que procesa al box
//			#ifdef _UN_SET_POINT
//      (byte*)&ModoSetPoint[1],      // direccion en la E2Prom /
//      #else
      (byte*)&ModoSetPoint[0],			/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
//			#endif
			
			"SEt P1",									    // nombre display
			2,											      // Cantidad de textos validos
			&ACCION_SET_POINT[0],         // Array donde estan los textos
			NULL,						              // parametro que modifica.
			#ifdef _UN_SET_POINT
			(PunteroF*)&B_Rele1.DirProc,NULL		      // Proximos estados
			#else
			(PunteroF*)&B_ModoSetPoint2.DirProc,NULL	// Proximos estados
			#endif
			};


/*Accion del Set Point2*/
const Textual B_ModoSetPoint2=
      {
      TxtHandler,						        // funcion que procesa al box
			(byte*)&ModoSetPoint[1],      // direccion en la E2Prom /
			"SEt P2",									    // nombre display
			2,											      // Cantidad de textos validos
			&ACCION_SET_POINT[0],         // Array donde estan los textos
			NULL,						              // parametro que modifica.
			(PunteroF*)&B_Rele1.DirProc,NULL		// Proximos estados
			};

/*Despegue Rele1*/
const PunteroF NEXT_RELE1[2]={
   &B_TiempoRele1.DirProc,
   #ifdef _UN_SET_POINT
   &B_ModoCuenta1.DirProc
   #else
   &B_Rele2.DirProc
   #endif
};

static const char DESPEGUE_RELE[2][7]={
      "Auto  ",
      "MAnuAL"									
};

 
const Textual B_Rele1=
      {
      TxtHandler,						        // funcion que procesa al box
			#ifdef _UN_SET_POINT
      (byte*)&ModoRele[0],          // direccion en la E2Prom /
      #else
     //(byte*)&ModoRele[1],				  /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
		  (byte*)&ModoRele[0],
			#endif
			"reLe 1",									    // nombre display
			2,											      // Cantidad de textos validos
			&DESPEGUE_RELE[0],            // Array donde estan los textos
			#ifdef _UN_SET_POINT
      (byte*)&ModoRele[0],          // direccion en la E2Prom /
      #else
      //(byte*)&ModoRele[1],				  /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
		  (byte*)&ModoRele[0],
			#endif
			NEXT_RELE1,NULL					      //Proximos estados
			};
			
/*Despegue Rele2*/
const PunteroF NEXT_RELE2[2]={
   &B_TiempoRele2.DirProc,
   &B_ModoCuenta1.DirProc
};
const Textual B_Rele2=
      {
      TxtHandler,						        // funcion que procesa al box
			(byte*)&ModoRele[1],          // direccion en la E2Prom /
			"reLe 2",									    // nombre display
			2,											      // Cantidad de textos validos
			&DESPEGUE_RELE[0],            // Array donde estan los textos
			(byte*)&ModoRele[1],					// parametro que modifica.
			NEXT_RELE2,NULL					      // Proximos estados
			};
/*Tiempo Despegue Rele1*/
const Numerico B_TiempoRele1={
      NumHandler,									  /* funcion que procesa al box*/
      #ifdef _UN_SET_POINT
      &TiempoRele[1],               // direccion en la E2Prom /
      #else
      &TiempoRele[0],				        /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			#endif
			"tiMe r",							        /* texto del titulo */
			3,											      // pos punto dec
			&Lim_1, &Lim_999999,					// limites
			NULL,									        // Parametro que modifica
			#ifdef _UN_SET_POINT
			(PunteroF*)&B_ModoCuenta1.DirProc,	NULL	// Proximos estados
      #else
			(PunteroF*)&B_Rele2.DirProc,NULL					//Proximos estados
			#endif
			};
/*Tiempo Despegue Rele2*/
const Numerico B_TiempoRele2={
      NumHandler,									  /* funcion que procesa al box*/
      &TiempoRele[1],					      /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"tiMe r",							        /* texto del titulo */
			3,											      // pos punto dec
			&Lim_1, &Lim_999999,					// limites
			NULL,									        // Parametro que modifica
			(PunteroF*)&B_ModoCuenta1.DirProc,	NULL	//Proximos estados
			};
			
/*Accion SPP*/
const PunteroF NEXT_MODO_CUENTA1[3]={
 		#if !defined(_UN_SET_POINT)
		  &Box_EntradaSPA.DirProc,	
		#else
		  &B_PuntoDecimal1.DirProc,	
		#endif
   &B_ModoCuenta2.DirProc,
   &B_ModoCuenta2.DirProc
};
static const char MODO_CUENTA[3][7]={
      "Contin",
      "StoP  ",									
			"AutorE"
};
extern volatile const TAccionSP AccionSPP;
extern volatile const TAccionSP AccionSPA;
const Textual B_ModoCuenta1={
      TxtHandler,						        // funcion que procesa al box
      (byte*)&AccionSPP,				/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"Cont 1",									    // nombre display
			3,											      // Cantidad de textos validos
			&MODO_CUENTA[0],              // Array donde estan los textos
			(byte*)&AccionSPP,				// parametro que modifica.
			NEXT_MODO_CUENTA1,NULL			  // Proximos estados
			};


/*Modo de cuenta*/
extern volatile const TModoCuenta ModoCuenta;

static const char MODO_CUENTA2[2][7]={
      "  UP  ",
      " down "								
};
const Textual B_ModoCuenta2={
      TxtHandler,						        // funcion que procesa al box
			(byte*)&ModoCuenta,       // direccion en la E2Prom /
			"Cont 2",									    // nombre display
			2,											      // Cantidad de textos validos
			&MODO_CUENTA2[0],             // Array donde estan los textos
			NULL,						              // parametro que modifica.
		//	#if !defined(_UN_SET_POINT)
			
			#ifndef _UN_SET_POINT
			  (PunteroF*)&Box_EntradaSPA.DirProc,NULL	// Proximos estados
			#else
			  (PunteroF*)&B_PuntoDecimal1.DirProc,NULL	// Proximos estados
			#endif
			};  

//#if !defined(_UN_SET_POINT)

#ifndef _UN_SET_POINT
/*Entrada Set Point Auxiliar*/
extern volatile const TModoSP_Auxiliar ModoSP_Auxiliar;
static const char strs_EntradaSPA[3][7]={
      "CuEnta",
      "tot cu",									
			"tot2  "
};

const PunteroF NEXT_MODO_CUENTA_SPA[3]={
   &B_PuntoDecimal1.DirProc,
   &Box_AccionSPA.DirProc,
   &Box_AccionSPA.DirProc
};

const Textual Box_EntradaSPA={
      TxtHandler,						        // funcion que procesa al box
      (byte*)&ModoSP_Auxiliar,				/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"AccSPA",									    // nombre display
			3,											      // Cantidad de textos validos
			strs_EntradaSPA,              // Array donde estan los textos
			(byte*)&ModoSP_Auxiliar,				// parametro que modifica.
			NEXT_MODO_CUENTA_SPA,NULL			  // Proximos estados
			};

/*Accion del Set Point Auxiliar*/
const Textual Box_AccionSPA={
      TxtHandler,						        // funcion que procesa al box
      (byte*)&AccionSPA,				/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"AccSPA",									    // nombre display
			3,											      // Cantidad de textos validos
			&MODO_CUENTA[0],              // Array donde estan los textos
			NULL,				// parametro que modifica.
			(PunteroF*)&B_PuntoDecimal1.DirProc,NULL			  // Proximos estados
			};

#endif
/*Punto Decimal*/
const Numerico B_PuntoDecimal1={
      NumHandler,									  /* funcion que procesa al box*/
      &PuntoDecimal[0],					    /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"Punto1",							        /* texto del titulo */
			0,											      // pos punto dec
			&Lim_0, &Lim_5,								// limites
			NULL,									        // Parametro que modifica
			(PunteroF*)&B_FactorEscala1.DirProc,	NULL	// Proximos estados
			};
/*Factor de Escala 1*/
const Numerico B_FactorEscala1={
      NumHandler,									  /* funcion que procesa al box*/
      &FactorEscala[0],	            // direccion en la E2Prom /
			"FAct 1",							        /* texto del titulo */
			4,											      // pos punto dec
			&Lim_0, &Lim_100000,				  // limites
			NULL,									        // Parametro que modifica
			(PunteroF*)&B_FactorEscala2.DirProc,	NULL						//Proximos estados
			};

/*Factor de Escala 2*/
const Numerico B_FactorEscala2={
      NumHandler,									  /* funcion que procesa al box*/
      &FactorEscala[1],					    /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"FAct 2",							        /* texto del titulo */
			4,											      // pos punto dec
			&Lim_0, &Lim_100000,					// limites
			NULL,									        // Parametro que modifica
			(PunteroF*)&B_Principal1.DirProc,	NULL	//Proximos estados
			};


/* Resets */
/**********/

const Titulo B_Reset={ 
      TitleHandler,							    /* funcion que procesa al box*/
			"rESEt ",										  // nombre display
			"  --  ",										  // nombre display
			NULL,								          // parametro que modifica.
			(PunteroF*)&B_ResetCuenta.DirProc,&B_Set.DirProc,	//Proximos estados
			};

static const char RESET[2][7]={
      "Ok    ",
      "rESEt "									
};

/*Reset Cuenta*/
const Textual B_ResetCuenta=
      {
      TxtHandlerRam,						// funcion que procesa al box
			(byte*)&Lim_0,// direccion en la E2Prom /
			"CuEntA",									//nombre display
			2,											//Cantidad de textos validos
			&RESET[0],             // Array donde estan los textos
			NULL,						 //parametro que modifica.
			(PunteroF*)&B_ResetTot1.DirProc,NULL					 //Proximos estados
			};
/*Reset Totalizador1*/
 
const Textual B_ResetTot1=
      {
      TxtHandlerRam,						// funcion que procesa al box
			(byte*)&Lim_0,            // direccion en la E2Prom /
			"tot cu",									//nombre display
			2,											//Cantidad de textos validos
			&RESET[0],             // Array donde estan los textos
			NULL,						 //parametro que modifica.
			(PunteroF*)&B_ResetTot2.DirProc,NULL					 //Proximos estados
			};

/*Reset Totalizador2*/
const Textual B_ResetTot2=
      {
      TxtHandlerRam,						// funcion que procesa al box
			(byte*)&Lim_0,// direccion en la E2Prom /
			"tot  2",									//nombre display
			2,											//Cantidad de textos validos
			&RESET[0],             // Array donde estan los textos
			NULL,						 //parametro que modifica.
			(PunteroF*)&B_Principal1.DirProc,NULL					 //Proximos estados
			};


/* Set */
/**********/
const Titulo B_Set={ 
      TitleHandler,							/* funcion que procesa al box*/
			" SEt  ",										//nombre display
			"  --  ",										//nombre display
			NULL,								//parametro que modifica.
			(PunteroF*)&B_SetC.DirProc,&B_Principal1.DirProc,					//Proximos estados
			};

/*SetC*/
const Numerico B_SetC={
      NumHandler,									/* funcion que procesa al box*/
      &SetC,					/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"SEtC  ",							        /* texto del titulo */
			0,										 //pos punto dec
			&Lim_0, &Lim_999999,								 //limites
			NULL,									      //Parametro que modifica
			(PunteroF*)&B_Id.DirProc,	NULL						//Proximos estados
			};
/*Id*/
const Numerico B_Id={
      NumHandler,									/* funcion que procesa al box*/
      &Id,					/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"Id    ",							        /* texto del titulo */
			0,										 //pos punto dec
			&Lim_1, &Lim_255,								 //limites
			NULL,									      //Parametro que modifica
			(PunteroF*)&B_Principal1.DirProc,	NULL						//Proximos estados
			};

/* RPM */
/**********/

const Titulo B_RPM_List={ 
      TitleHandler,							/* funcion que procesa al box*/
			" rPM  ",										//nombre display
			"  --  ",										//nombre display
			NULL,								//parametro que modifica.
			(PunteroF*)&B_RPM.DirProc,&B_Principal1.DirProc,					//Proximos estados
			};

/*RPM Si o No*/
const PunteroF NEXT_RPM[2]={
   &B_Principal1.DirProc,
   &B_Pulsos.DirProc,

};
static const char YES_NO[2][7]={
      "no    ",
      "Si    "
};
const Textual B_RPM={
      TxtHandler,						// funcion que procesa al box
			&RPM,          // direccion en la E2Prom /
			" rPM  ",							//nombre display
			2,										//Cantidad de textos validos
			&YES_NO[0],           // Array donde estan los textos
			&RPM,						 //parametro que modifica.
			NEXT_RPM,NULL					 //Proximos estados
			};

/*Pulsos por vuelta*/  
const Numerico B_Pulsos={
      NumHandler,									/* funcion que procesa al box*/
      &PulsosXvuelta,					/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			"PuLSoS",							        /* texto del titulo */
			0,										 //pos punto dec
			&Lim_0, &Lim_999999,								 //limites
			NULL,									      //Parametro que modifica
			(PunteroF*)&B_Principal1.DirProc,	NULL						//Proximos estados
			};


#endif
/* fin  */


