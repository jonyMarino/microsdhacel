#include "stddef.h"
#include "stdtypes.h"
#include "Mensajes.h"
#include "Mydefines.h"

/***    DEFINICION DE MENSAJES    ***/
#define CANTIDAD_MENSAJES 26 // Los mensajes van del 1 a	 CANTIDAD_MENSAJES
const char * (MENSAJES[CANTIDAD_MENSAJES]) ={
"ESPEEd",             /* This device does not work in the active speed mode. */
"ErrRAn",             /* Parameter out of range. */
"ErrVAL",             /* Parameter of incorrect value. */
"Err OF",             /* Timer overflow. */
"ErrMat",             /* Overflow during evaluation. */
"",                   /* Device is enabled. */
"",                   /* Device is disabled. */
"ErbuSY",             /* Device is busy. */
"",                   /* Requested value or method not available. */
"rXEMtY",             /* No data in receiver. */
"tXFULL",             /* Transmitter is full. */
"buSnAv",             /* Bus not available. */
"ErrOvr",             /* Overrun error is detected. */
"ErrFrA",             /* Framing error is detected. */
"ErrPAr",             /* Parity error is detected. */
"EnoiSe",             /* Noise error is detected. */
"",                   /* Idle error is detected. */
"",                   /* Fault error is detected. */
"",                   /* Break char is received during communication. */
"ErrCrC",             /* CRC error is detected. */
"ErrArv",             /* A node losts arbitration. This error occurs if two nodes start transmission at the same time. */
"ErrPro",             /* Protection error is detected. */
"Err UF",             /* Underflow error is detected. */
"ErrUnd",             /* Underrun error is detected. */
"ECmmon",             /* Common error of a device. */
"ErSYnC"              /* LIN synchronization error is detected. */
};
/************************************/

byte Mensaje[CANTIDAD_DISPLAYS];
bool MostrarMensaje[CANTIDAD_DISPLAYS]; 


byte SetMessage (byte Display,byte iMensaje){ 
  
  if(Display>CANTIDAD_DISPLAYS-1 || iMensaje>CANTIDAD_MENSAJES) 
    return ERR_ARGS; //Display inexistente
  if(Mensaje[Display]!=0 && iMensaje>Mensaje[Display]) 
    return ERR_PRIORIDAD; //El mensaje a mostrar es de menor prioridad que el mostrado
  Mensaje[Display]=iMensaje;
  return ERR_OK; 
}

char * GetMessage(byte Display){
   if(Mensaje[Display]==0)
	   return NULL;
   return MENSAJES[Mensaje[Display]-1]; // Los mensajes van del 1 a	 CANTIDAD_MENSAJES y el array empieza en 0
}