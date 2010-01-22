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
//#include "mc9s12gc32.h"
#include "mc9s12gc32.h" 		
#include "PUL.h"
#include "TimerFlag.h"
#include "PE_Types.h"
#include "teclas.h"
//#include "Mydefines.h"
#include "Object.h"
#define TRETURN 30000 						 
/*  Definicion de nombre de tecla y su forma de ser invocada*/

typedef struct {
  char nombre;
  byte teclas;
}t_key;

const t_key keys[]={
  'c',KEY_UP | KEY_RESET,
  's',KEY_DOWN | KEY_RESET,
  'p',KEY_UP | KEY_DOWN | KEY_RESET,
  0,0
};

typedef struct {
  char nombre;				// se va a activar al soltar la tecla
  char nombre_hold;
  byte tecla;
  byte factor; //sobre 10
  bool restart;
}t_hold_key;

const t_hold_key hold_keys[]={
  'k','m',KEY_RESET,9,TRUE,
  'r','f',KEY_ENTER,9,TRUE,
  'u','u',KEY_UP,10,FALSE,
  'd','d',KEY_DOWN,10,FALSE,
  0,0,0,0
};

																
/* variables usadas */
struct TimerFlag TeclaTimer;  //Timer de ultima tecla presionada
byte	ValidKey=0;					// tecla presionada. NULL: teclas liberadas
byte	KeyAnt=0;					// estado anterior
byte  KeepKeyAnt=0;
byte	KeyRampa=0;				// valor de recarga para ir acelerando
byte	KeyEdge;				  // teclas presionada. Reset en main
byte	KeyCnt=0;					// contador para generar el tiempo entre repeticiones
	// teclas presionada. Reset en main
byte	KeyDeb=0;					// contador para el debounce
byte	SwAct=0;					// arma los bits del switch actual
byte	CntInt=0;					// contador de interrupciones para procesar cada 4
				

void Teclas_Init(void){
  newAlloced(&TeclaTimer,&TimerFlag,(ulong)TRETURN);  
}

void Switches(byte Pulsador)
{

	 byte i;
/* armo el SwAct cada 4 interrupciones insertando en un registro */
 
  if(!PUL_GetVal()) SwAct|=Pulsador;
                     
	CntInt++;
	if(CntInt==CANTIDAD_TECLAS){	  
	  CntInt=0;				// reinicia...
		
	  if(SwAct!=ValidKey) // proceso del debounce
	  {
		  KeyDeb=CANTIDAD_VALIDACIONES;
		  ValidKey=SwAct;
	  }
	  SwAct=0;
	  

	  if(KeyDeb!=0) {
	  	--KeyDeb;
	  //	return;		
	  }
	  
	//acaba de terminar la validacion
		
    else if (KeyAnt!=ValidKey){

  	   for(i=0;keys[i].nombre!=0;i++){
  	    if(keys[i].teclas==ValidKey){
  	     KeyEdge=keys[i].nombre;
  	     break;
  	    }
  	   }

  	  if(ValidKey==KEY_NULL){
  	    for(i=0;hold_keys[i].nombre!=0;i++){				 // Al soltar para los que tienen otra funcion en toque mantenido
    	    if(hold_keys[i].tecla==KeyAnt && hold_keys[i].nombre_hold!=KeepKeyAnt){
    	     KeyEdge=hold_keys[i].nombre;
    	     break;
    	    }
  	    }
  	    KeepKeyAnt=' ';
  	  }
  	  TimerFlag_reset(&TeclaTimer);
  	  Timer_Restart(&TeclaTimer);
  	  KeyAnt = ValidKey;
  	  KeyCnt=0;
  	  KeyRampa=KEY_RAMPA_INI;
    }
	  
	}
  /*  Parte de Teclas Sostenidas  */
  if(KeyAnt==0) return;
  if(KeyCnt<KeyRampa)
	  KeyCnt++;
  else{
	  KeyCnt=0;
	  if(KeyRampa>KEY_RAMPA_FIN)
		  KeyRampa-=KEY_DELTA;

		for(i=0;hold_keys[i].nombre!=0;i++){				 // Al soltar para los que tienen otra funcion en toque mantenido
  	    if(hold_keys[i].tecla==KeyAnt && KeyRampa<=(word)KEY_RAMPA_INI*hold_keys[i].factor/10){
  	     KeepKeyAnt=KeyEdge=hold_keys[i].nombre_hold;
  	     if(hold_keys[i].restart)
  	      KeyRampa=KEY_RAMPA_INI;
  	     break;
  	    }
		  }
	  TimerFlag_reset(&TeclaTimer);
	  Timer_Restart(&TeclaTimer);
  }
  //	SwAct=0;
}

/*  Obtiene la tecla presionada*/
char get_key(void){
char key;  
  Cpu_DisableInt();
  key= KeyEdge;
  KeyEdge =0;
  Cpu_EnableInt();
  
  return key;
}

/*  Avisa si paso el tiempo de espera de tecla */
bool Teclas_TimePass(void){
  return TimerFlag_getFlag(&TeclaTimer);
}

