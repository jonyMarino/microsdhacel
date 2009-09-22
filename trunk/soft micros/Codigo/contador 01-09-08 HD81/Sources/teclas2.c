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
/* definiciones del teclado */
#define KEY_RAMPA_INI	80
#define KEY_RAMPA_FIN	16
#define KEY_DELTA	8
#define NOR	1		// Set cuando se activo por tiempo ('f') y no debe el flanco ('r')
  
/* definiciones usadas en rutina */
#define _NO_KEY		0x0F
    
/* variables externas */
byte	KeyStt;					// tecla presionada. NULL: teclas liberadas
byte	KeyAnt;					// estado anterior
byte	KeyRampa;				// valor de recarga para ir acelerando
byte	KeyCnt;					// contador para generar el tiempo entre repeticiones
extern	byte	KeyEdge;				// teclas presionada. Reset en main
byte	KeyDeb;					// contador para el debounce
byte	SwAct;					// arma los bits del switch actual
extern	word	CNT1_RTI;				// usado en demora de 10 seg. en la navegacion  
byte	CntInt;					// contador de interrupciones para procesar cada 4
byte	KeyFlags;				// flags indicadores. ver detalle en main	

void Switches(byte Pulsador)
{

/* armo el SwAct cada 3 interrupciones rotando un registro */

  if(!PUL_GetVal()) SwAct|=Pulsador;
 // else SwAct&= (~Pulsador);

//	SwAct>>=1;				// rota un lugar
	CntInt++;
	if(CntInt==3)
	{	
		CntInt=0;				// reinicia...
	
		if(SwAct!=KeyAnt)
		{		// proceso del debounce
			KeyDeb=1;
			KeyAnt=SwAct;
		}
		if(KeyDeb!=0)
		{			// posible proceso de edge
			KeyDeb--;
			if(KeyDeb==0)
			{			// acaba de terminar el debounce
			 if(SwAct==0x04)  KeyEdge='u';
			 if(SwAct==0x02)  KeyEdge='d';
			 if(SwAct==0x01)  KeyEdge='r';
			}
			 // if((SwAct!=_NO_KEY)||(KeyStt==0x0E))
			 // {
			//	  KeyEdge= (KeyStt ^ SwAct) & (KeyStt ^ 2);
			//	  if( KeyEdge==0x04)KeyEdge='d';
			//	  if( KeyEdge==0x02)KeyEdge='u';
			//	  if((KeyEdge==0x01)&&(!(KeyFlags & NOR)))
			//	  {
			//	    KeyEdge='r';
			//	    KeyFlags&=0xfe;
			//	  }
			//	if(KeyEdge==0x01)KeyEdge='k';
			//	}
	/*		if (KeyStt==_NO_KEY)
			  KeyFlags&=0xfe;	// reset el flag de tecla larga
			if(KeyStt!=SwAct)
			  KeyCnt=KEY_RAMPA_INI;
			KeyStt=SwAct;
			CNT1_RTI=10000;					// contador de 10 segundos	
			}		*/
		}
	
	/* proceso que genera la rampa de repeticiones */
	/*  if(KeyCnt>KEY_RAMPA_FIN)
	    KeyCnt--;
	  else
	  {
	    KeyCnt=KeyRampa;
	    if(KeyStt==_NO_KEY)
	    {
	      if(KeyRampa<KEY_RAMPA_INI)
	      KeyRampa+=KEY_DELTA;
	    }
	    else
	    {				
	      if(KeyRampa>KEY_RAMPA_FIN)  KeyRampa-=KEY_DELTA;
			  if(KeyStt==0x0b)  KeyEdge='d';
			  if(KeyStt==0x0d)  KeyEdge='u';
			  if((KeyStt==0x0E)&&(KeyRampa<KEY_RAMPA_INI*3/4))
			  {
					KeyEdge='f';
					KeyRampa=KEY_RAMPA_INI;
					KeyFlags|=NOR;
			  }
			  CNT1_RTI=10000;					// contador de 10 segundos				
		  }
	  }			 */
	SwAct=0;
	}
         
}  
