//////////////////////////////////////////////////////////////
//
// rutina de escaneo. Actua cuando se libera la tecla. Si UP
// 					  se mantiene presionada un tiempo mayor
//					  a 1 seg, entonces es funcion.
//
// Uso: se debe declarar en main y como globales las variables
//		KeyStt y KeyEdge.
//
// IN:  nothing
// OUT: KeyStt:  tecla presionada, NULL teclas liberadas
//		KeyEdge: tecla presionada. Reset en main para asegurarme
//				 que fue debidamente tomada.
//
//////////////////////////////////////////////////////////////

/* archivos include */
#include "IO_Map.h" 		
#include "PUL.h"
#include "TECLAS3.h"
/* definiciones usadas en rutina */
#define CANTIDAD_TECLAS 3      /*Cantidad de pulsadores/teclas que se leen del intrumento*/
#define CANTIDAD_VALIDACIONES 4 /*Cantidad de ingresos iguales que hace falta para validar
                                o asegurar que una tecla fue presionado(si es 0 no corrobora)*/
/* definiciones del teclado */
#define KEY_RAMPA_INI	60 /*A los cuantos ingresos(la primera vez) iguales se repite la salida para ese pulsador*/
#define KEY_RAMPA_FIN	40  /*Maxima velociadad de ingresos iguales a los que se repite la salida para ese pulsador*/
#define KEY_DELTA	4  /*Variacion de velociadad una vez realizada la salida*/
																
/* variables externas */
byte	ValidKey=0;					// tecla presionada. NULL: teclas liberadas
byte	KeyAnt=0;					// estado anterior
byte	KeyRampa=0;				// valor de recarga para ir acelerando
extern	byte	KeyEdge;				// teclas presionada. Reset en main
extern	word	CNT1_RTI;				// usado en demora de 10 seg. en la navegacion  
byte	KeyCnt=0;					// contador para generar el tiempo entre repeticiones
	// teclas presionada. Reset en main
byte	KeyDeb=0;					// contador para el debounce
byte	SwAct=0;					// arma los bits del switch actual
byte	CntInt=0;					// contador de interrupciones para procesar cada 4
bool  Anterior_F=FALSE;
byte KeyFlags;				
void Switches(byte Pulsador)
{

/* armo el SwAct cada 3 interrupciones rotando un registro */

  if(!PUL_GetVal()) SwAct|=Pulsador;

	CntInt++;
	if(CntInt<CANTIDAD_TECLAS) return;
	CntInt=0;				// reinicia...

	if(SwAct!=ValidKey) // proceso del debounce
	{
		KeyDeb=CANTIDAD_VALIDACIONES;
		ValidKey=SwAct;
	}
	if(KeyDeb!=0) {
		--KeyDeb;
		return;		
	}
	//acaba de terminar la validacion

  if (KeyAnt!=ValidKey){

	  switch(ValidKey){
		  case 0x02: 
		    KeyEdge='d';
				break;
			case 0x04: 
			  KeyEdge='u';
				break;
			case 0x6: 
			  KeyEdge='k';
			}
	  if(KeyAnt==0x01 && ValidKey==0x00 && !Anterior_F) KeyEdge='r';

	  if(ValidKey==0) Anterior_F=FALSE;
	  CNT1_RTI=10000;
	  KeyAnt = ValidKey;
	  KeyCnt=0;
	  KeyFlags|=~KEY_NO_SOSTENIDA;
	  KeyRampa=KEY_RAMPA_INI;
  }
  else
  {
	  if(ValidKey==0) return;
	  KeyFlags&=KEY_NO_SOSTENIDA;
	  if(KeyCnt<KeyRampa)
		  KeyCnt++;
	  else{
		  KeyCnt=0;
		  if(KeyRampa>KEY_RAMPA_FIN)
			  KeyRampa-=KEY_DELTA;
		  switch(ValidKey){
			  case 0x02: KeyEdge='d';
				     break;
			  case 0x04: KeyEdge='u';
				     break;
			  case 0x01: 
			       if(KeyRampa<=KEY_RAMPA_INI*3/4){			       
			        KeyEdge='f';
				      KeyRampa=KEY_RAMPA_INI;
				      Anterior_F=TRUE;
			       }
			}
			CNT1_RTI=10000;
	  }


  }
	SwAct=0;
}


