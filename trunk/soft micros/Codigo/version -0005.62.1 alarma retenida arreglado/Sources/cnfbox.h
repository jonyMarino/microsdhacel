#ifndef _BoxesStruct
#define _BoxesStruct

#include "PE_Types.h"
#include "stddef.h"
#include "Mydefines.h"

typedef void (**PunteroF)(void);
#define NO_FUNCTION NULL
/* definicion de la estructura de dato de los Boxes*/         
/*******************************************************/
typedef const struct{
  int * Fdir;							      /* Direccion del parámetro a Escribir*/
  byte (*OnWrite)(int,byte);		/* Funcion a ejecutar Luego de la escritura del parámetro*/
  int * Inf,* Sup;			        /* Limites inferior y superior */
  byte chan;										// canal
}TDato;
			
/* definicion de boxes con variables de texto no en Rom*/
/*******************************************************/
typedef struct{
		void(*DirProc)(void);		/* funcion que procesa al box*/
		TDato * sDato;             /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
		char * TxtDpy;				  /* texto del titulo */
    const char  **TxtDpy0;
 		int * VdeNavegacion;	/*Variable que determina los proximos estados. if FALSE, depende del primero*/		
		const PunteroF * Teclar; //Proximo estado toque rapido
		PunteroF   Teclaf; //Proximo estado toque mantenido

}Textual;

/* definicion de boxes con variables numericas no en Rom*/
/********************************************************/
typedef struct{
		void(*DirProc)(void);		    /* funcion que procesa al box*/
		TDato * sDato;                 /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/	
		char * TxtDpy;				    /* texto del titulo */
		byte Dot;					          /* punto decimal a enc */
		int * VdeNavegacion;			/*Variable que determina los proximos estados. if FALSE, depende del primero*/		
		const PunteroF * Teclar;			//Proximo estado toque rapido
		PunteroF   Teclaf;			//Proximo estado toque mantenido		 	
}Numerico;

/* definicion de boxes con variables numericas no en Rom*/
/********************************************************/
typedef struct{
		void(*DirProc)(void);		    /* funcion que procesa al box*/
		int * Dato;                 /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/	
		char * TxtDpy;				    /* texto del titulo */
		byte Dot;					          /* punto decimal a enc */
		int * VdeNavegacion;			/*Variable que determina los proximos estados. if FALSE, depende del primero*/		
		const PunteroF * Teclar;			//Proximo estado toque rapido
		PunteroF   Teclaf;			//Proximo estado toque mantenido		 	
}NumericoRO;

/* definicion de boxes de titulo */
/*********************************/

typedef struct{
		void(*DirProc)(void);		    /* funcion que procesa el box. DirProc es un puntero a una funcion que no tiene parametros y que regresa void */
		char * TxtDpy;				      /* texto del titulo */
		char * TxtDpySup;			    /* texto del titulo */
		int * VdeNavegacion;			/*Variable que determina los proximos estados. if FALSE, depende del primero*/
		const PunteroF * Teclar;			/* Toque Rapido*/
		PunteroF   Teclaf;			/* Toque Prolongado*/
}Titulo;

/* Puntero a los Boxes*/
typedef union{
	Numerico * Num;
	NumericoRO * NumRO;
	Textual	* Txt;
	Titulo * Tit;	
}TPtrBox;
///VALORES DE LOS TEXTOS////////////
//////////AUTO SINTONIA/////////////
#define St_OFF 0
#define Stc 1
#define St_Ok 4
#define St_Err 5

//////////TIPO SEGMENTO/////////////
#define			End		0
#define     rMPt  1
#define     rMPV	2								
#define			MSt		3
#define			SteP  4
#define			JMP		5

//////////TIPO TEMPERATURA INICIAL///
#define SEt 0
#define AMb 1	

//////////TIPO DE CONTROL/////////////
#define _onoff 0
#define _pid 1								

///////////TOLERANCIAS//////////////
      
#define	OFF  0
#define	Lo   1
#define	Hi   2
#define	bAnd 3			
#define	no   4

//////////CONDICION DE EMERGENCIA///
#define cc   0
#define rS   1
#define rP   2
#define EndP 3
#define no   4

//////////ALARMAS//////////////////
#ifdef _APARATO_VIEJO
#define _e 0
#define _d 1
#define _eret 2
#define _dret 3
#define _dbloq 4
#define _RET 5
#else
#define _e 0
#define _d 1
#define _eret 2
#define _dret 3
#define _dbloq 4
#define _eprop 5
#define _dprop 6
#define _RET 7
#endif
///////////////////////////////////

//////////////////////////////////////////////////////////////////

//////////////////// INDICES DE LOS PARAMETROS DE LOS BOXES ///////////////////

// PARAMETROS QUE PUEDEN DEPENDER DE LA CANTIDAD DE CANALES(SUMAR 4 ENTRE ELLOS)
#define R_SetPoint 0
#define R_AL 4	 /*dir AL1A. AL2A=AL1A+1 */
#define R_H1  12
#define R_HA1  16
#define R_Per 20
#define R_Sensor 24 /* direccion en Flash del TipoSensor1 */
#define R_Decimales 28 /*direccion de la cantidad de decimales */
#define R_Offset  32 /* direccion en Flash del TipoSensor1 */
#define R_Gan     36 /* direccion en Flash del TipoSensor1 */
#define R_ACT 40
#define R_AGT 44
#define R_ACP 48
#define R_AGP 52
#define R_AAnlLow 56
#define R_AAnlHi  60
#define R_Lim_Inf 64 /*dir lim Inf */
#define R_Lim_Sup 68  /*dir lim sup */				
#define R_Tcontrol1  76
#define R_Reset  80
#define R_IN1 88
#define R_DR1 92
#define R_Pra 96
#define R_Pot_Inf 104 /*dir lim Inf */
#define R_Pot_Sup 108  /*dir lim sup */
#define R_Tsalcont 112 //salida control
#define R_Potman 116
#define R_Stn 120
#define R_Programa 124
#define R_T_AL 128
#define R_Segmento 132
#define R_Talar1 136
#define R_Filtro1 144
#define R_TieSeg  148
#define R_Pss 152
#define R_Tss 153
#define R_SPlim 154
#define R_SPst 155
#define R_SPsb 156
#define R_Indf 157
#define R_Drdf 158
#define R_Abdf 159
#define R_SPlimst 160

// PARAMETROS INDIVIDUALES DE CONGIGURACION (EMPIEZA EN EL INDICE 220 PARA DEJAR LUGAR A LOS ANTERIORES)

#define R_Vrmp 215
#define R_Tmpm  216
#define R_Tiem  217



#define R_Topn 218
#define R_Dbnd 219
#define R_SetC 220
#define R_Ver  221
#define R_Id   222 /* direccion del Id del aparato*/
#define R_adq  223
#define R_Ano	 224
#define R_mes	 225
#define R_dia	 226
#define R_Hora 227
#define R_int	 228
#define R_ATA  229

///////////VERSION/BLOQUEOS////////
typedef enum{BL1,BL2,BL3,BL4,VER_DIF}TVersion;

////////////////////Boxes info //////////////////
#define DECIMALES_CANAL4   255
#define DECIMALES_CANAL3   254
#define DECIMALES_CANAL2   253
#define DECIMALES_CANAL1   252

////////////////////////////////////////////

extern volatile const int PRom[];
extern const Numerico Principal1;
extern const Numerico C1SP;
#ifdef programador
extern const Numerico Segmento1;
#endif
extern const TDato Parametros[PARAMETROS];
extern int Lim_Dec[CANTIDAD_CANALES];
extern int Lim_Inf_ch[CANTIDAD_CANALES];
extern int Lim_Sup_ch[CANTIDAD_CANALES];
extern int	 segmento_ingresado, temperatura_inicial,  tipo_segmento, temperatura_f,
	   tiempo, tolerancia,tolerancia_gral, condicion_emer,condicion_emer_gral,tipo_tolerancia,tipo_tolerancia_gral,tipo_temperatura_inicial;
extern int next_tiempo,next_tol,next_prog;
extern int Lim_Segmento1;	 /* Para el prog nuevo, pantalla de ingreso de programa*/
extern int Lim_Segmento2[CANTIDAD_SAL_CONTROL];  /* Limite para el segmento que se puede cambiar mientras corre*/
extern int Lim_TieSeg[CANTIDAD_SAL_CONTROL];
extern const PunteroF R_Emergencia[2];

extern int Lim_Inf_ch[CANTIDAD_CANALES],Lim_Sup_ch[CANTIDAD_CANALES];
extern int Lim_Dec[CANTIDAD_CANALES];
extern const int Lim_m9999;
extern const int Lim_m1999;
extern const int Lim_m1;
extern const int Lim_0;
extern const int Lim_1;
extern const int Lim_2;
extern const int Lim_3;
extern const int Lim_4;
extern const int Lim_5;
extern const int Lim_6;
extern const int Lim_7;
extern const int Lim_8;
extern const int Lim_9;
extern const int Lim_10;
extern const int Lim_24;
extern const int Lim_255;
extern const int Lim_600;
extern const int Lim_1000;
extern const int Lim_9999;
#ifdef jony_28_06
extern const int Lim_32767;
#endif
#endif