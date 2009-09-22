#ifndef _BoxesStruct
#define _BoxesStruct
#include "PE_Types.h"


typedef void (**PunteroF)(void);

/* definicion de boxes con variables de texto no en Rom*/
/*******************************************************/
typedef struct{
		void(*DirProc)(void);		/* funcion que procesa al box*/
		byte * Fdir;             /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
		char TxtDpy[7];				  /* texto del titulo */
		byte CantTxts;				    /* cantidad de textos posibles */
    const char  (*TxtDpy0)[7];
 		byte * VdeNavegacion;	/*Variable que determina los proximos estados. if FALSE, depende del primero*/		
		const PunteroF * Teclar; //Proximo estado toque rapido
		PunteroF   Teclaf; //Proximo estado toque mantenido

}Textual;

/* definicion de boxes con variables numericas no en Rom*/
/********************************************************/
typedef struct{
		void(*DirProc)(void);		    /* funcion que procesa al box*/
		long  * Fdir;                 /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/	
		char TxtDpy[7];				    /* texto del titulo */
		byte Dot;					          /* punto decimal a enc */
		const long * Inf;					          /* Limites inferiores y superiores fijos */
		const long * Sup;
		byte * VdeNavegacion;			/*Variable que determina los proximos estados. if FALSE, depende del primero*/		
		const PunteroF * Teclar;			//Proximo estado toque rapido
		PunteroF   Teclaf;			//Proximo estado toque mantenido		 
	
}Numerico;


/* definicion de boxes de titulo */
/*********************************/

typedef struct{
		void(*DirProc)(void);		    /* funcion que procesa el box. DirProc es un puntero a una funcion que no tiene parametros y que regresa void */
		char TxtDpy[7];				      /* texto del titulo */
		char TxtDpySup[7];			    /* texto del titulo */
		byte * VdeNavegacion;			/*Variable que determina los proximos estados. if FALSE, depende del primero*/
		const PunteroF * Teclar;			/* Toque Rapido*/
		PunteroF   Teclaf;			/* Toque Prolongado*/
}Titulo;

////////////////////Boxes info //////////////////
#define DECIMALES_CANAL4   255
#define DECIMALES_CANAL3   254
#define DECIMALES_CANAL2   253
#define DECIMALES_CANAL1   252

////////////////////////////////////////////

extern void TitleHandler(void);//manejador boxes de titulos
extern void NumHandler(void);  //manejador boxes tipo numérico
extern void TxtHandler(void);  //manejador boxes tipo textual
extern void MainHandler(void); //acciones Pantalla principal
extern void DiaHandler(void);  //manejador boxes tipo numérico
extern void HoraHandler(void);  //manejador boxes tipo numérico
	
///VALORES DE LOS TEXTOS////////////
/*Tipo de Sensor*/
#define MICROSWITCH 0
#define TRANSISTOR  1
/*Modo de Set Point*/
#define EXCESO  0
#define DEFECTO 1
/*Modo de Rele*/
#define AUTOMATICO 0
#define MANUAL		 1
/*Reset de Totalizadores*/
#define Ok 0
#define rESEt 1 	
/* RPM */
typedef enum {NO,SI}T_NO_SI;
#endif