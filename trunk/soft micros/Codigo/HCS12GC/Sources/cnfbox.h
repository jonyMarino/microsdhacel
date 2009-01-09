#ifndef _BoxesStruct
#define _BoxesStruct
#include "PE_Types.h"
#include "stddef.h"
#include "parametros.h"
#include "Mydefines.h"

typedef void (**PunteroF)(void *);

typedef  struct{
  int (*get_VarNavegacion)(void);			/*Variable que determina los proximos estados. if FALSE, depende del primero*/		
	const PunteroF * Teclar;			//Proximo estado toque rapido	
}TSiguientes;

typedef PunteroF (*TSiguiente)(byte tecla);

/* definicion de boxes con variables de texto no en Rom*/
/*******************************************************/
typedef struct{
		void(*DirProc)(void *);		/* funcion que procesa al box*/
		char * TxtDpy;				    /* texto del titulo */
}TBox;

typedef struct{
		TBox Box;
		TDato * sDato;
		byte num_elementos;		
}TParametro;

typedef struct{
		TParametro  Parametro;
    const char  **TxtDpy0; 
}Ttextual;

typedef struct{ 		
 		Ttextual BaseTextual;
    PunteroF  Teclar;			//Proximo estado toque rapido
}Textual1;

typedef struct{
  Textual1 BoxText;
  PunteroF Teclaf;			//Proximo estado toque mantenido		
}Textual2;

typedef struct{ 		
 		Ttextual BaseTextual;
 		TSiguientes siguientes;  // Parámetro que determina los siguientes estados
}Textual3;

typedef struct{
  Textual3 BoxText;
  PunteroF Teclaf;			//Proximo estado toque mantenido	
}Textual4;

typedef struct{ 		
 		Ttextual BaseTextual;
    TSiguiente pf_siguiente;  /* Funcion que determina los siguientes estados*/
}TextualJumpCond;

/* definicion de boxes con variables numericas no en Rom*/
/********************************************************/
typedef struct{
		TParametro  Parametro;
		byte Dot;					          /* punto decimal a enc */
}TNumerico;

typedef struct{
    TNumerico BaseNumerico;
		PunteroF  Teclar;			//Proximo estado toque rapido
}Numerico1;

typedef struct{
    Numerico1  BoxNumerico;
		PunteroF  Teclaf;			//Proximo estado toque rapido
}Numerico2;

typedef struct{
    TNumerico BaseNumerico;
		TSiguientes siguientes;  /* Parámetro que determina los siguientes estados*/
}Numerico3;

typedef struct{
    Numerico3  BoxNumerico;
		PunteroF  Teclaf;			//Proximo estado toque rapido
}Numerico4;

typedef struct{
    TNumerico BaseNumerico;
		TSiguiente pf_siguiente;  /* Funcion que determina los siguientes estados*/
}NumericoJumpCond;

/* definicion de boxes con variables numericas no en Rom*/
/********************************************************/
typedef struct{
    TBox	Box;	
    int (*get) (byte);                 /* Funcion de obtencion de la variable*/	
		byte num_elementos;    
}TParametro_Read_Only;
		
typedef struct{
		TParametro_Read_Only parametro;
		byte Dot;					          /* punto decimal a enc */
}NumericoRO;

typedef struct{
		NumericoRO numerico_base;
   	PunteroF  Teclar;			//Proximo estado toque rapido
}NumericoRO1;

typedef struct{
		NumericoRO numerico_base;
  	TSiguiente pf_siguiente;  /* Parámetro que determina los siguientes estados*/
}NumRO_JmpCond;

	

/* definicion de boxes de titulo */
/*********************************/

typedef struct{
		TBox Box;
		char * TxtDpySup;			    /* texto del titulo */
		PunteroF  Teclar;			//Proximo estado toque rapido
    PunteroF  Teclaf;
}Titulo;


//////////////////////////////////////////////////////

//////////////////// INDICES DE LOS PARAMETROS DE LOS BOXES ///////////////////

// PARAMETROS QUE PUEDEN DEPENDER DE LA CANTIDAD DE CANALES(SUMAR 4 ENTRE ELLOS)

// DEFINICIONES PARAMETROS2
#define OFFSET_PAR2 300
#define PAR_SETPOINT 0
#define PAR_AL 4	 /*dir AL1A. AL2A=AL1A+1 */
#define PAR_LIM_INF 8 /*dir lim Inf */
#define PAR_LIM_SUP 12  /*dir lim sup */
#define PAR_RESET  16

#define R_H1  0
#define R_HA1  4
#define R_Sensor 8 /* direccion en Flash del TipoSensor1 */
#define R_Decimales 12 /*direccion de la cantidad de decimales */
#define R_Tcontrol1  16
#define R_Pra 20
#define R_Stn 24
#define R_Programa 28
#define R_Segmento 32
#define R_TieSeg  36

#define PAR_FILTRO 0
#define PAR_PERIOD 4
#define PAR_OFFSET 8
#define PAR_GAN     12 /* direccion en Flash del TipoSensor1 */
#define PAR_ACT 16
#define PAR_AGT 20
#define PAR_ACP 24
#define PAR_AGP 28
#define PAR_AANL_LOW 32
#define PAR_AANL_HI  36				
#define PAR_IN 40
#define R_DR1 44
#define R_T_AL 48
#define R_Talar1 52
#define R_Pot_Inf 56 /*dir lim Inf */
#define R_Pot_Sup 60  /*dir lim sup */
#define R_Tsalcont 64 //salida control
#define R_Potman 68
#define R_SetC 72
#define R_Ver  73
#define R_Id   74 /* direccion del Id del aparato*/
#define R_ATA  75

#define R_VP_Time 152
#define R_VP_DeadB 156
// PARAMETROS INDIVIDUALES DE CONGIGURACION (EMPIEZA EN EL INDICE 220 PARA DEJAR LUGAR A LOS ANTERIORES)
#define R_adq  223
#define R_Ano	 224
#define R_mes	 225
#define R_dia	 226
#define R_Hora 227
#define R_int	 228


////////////////////Boxes info //////////////////
#define DECIMALES_CANAL4   255
#define DECIMALES_CANAL3   254
#define DECIMALES_CANAL2   253
#define DECIMALES_CANAL1   252

////////////////////////////////////////////



extern const NumericoJumpCond Principal1;

#endif