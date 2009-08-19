#ifndef _BOX_PRINCIPAL_H
#define _BOX_PRINCIPAL_H


#include <stdtypes.h>

#include "ClassBox.h"
#include "Sensor.h"
#include "PropWithInc.h"
#include "MessagesOut.h"
#include "TimerFlag.h"
#include "PE_Types.h"

#pragma DATA_SEG BoxPrincipal_DATA                                            
#pragma CODE_SEG BoxPrincipal_CODE                     
#pragma CONST_SEG DEFAULT       /* Constant section for this module */
                  


struct BlockConstBoxPri{
  struct BlockBoxConstruct _base;
  struct Getter * snsr1; 
  struct MessageOut * msjs; 
};

struct BoxPri{
  struct Box _box;
//Protected:  
  /*struct getter*/void * snsr1;
  /*struct MessageOut*/void * msjs;		// manejador de mensajes
  uint msj_index;             // indice del msj a mostrar
  struct TimerFlag timerPri;		// Timer de refresco
};

extern const struct BoxClass BoxPri;


/*
** ===================================================================
**     BOX PRINCIPAL 1 CONTROL
** ===================================================================
*/ 

struct BlockConstBoxPri1c{
  struct BlockConstBoxPri _base;
};

struct BoxPri1c{
  struct BoxPri _box;
//Protected:
  struct GetterVisual * _getter;
  uchar par_seconds;            // segundos que se muestra el parametro 
                                // luego de presionar la tecla ascendente 
                                // o descendente
  bool propCambio;  
  struct TimerFlag timerProp;		// Timer de refresco                            
};

extern const struct BoxClass BoxPri1c;


/*
** ===================================================================
**     Method      :  DataBox_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void BoxPri1c_Constructor(void* _self,
                        struct SensorVisual * sensor,
                        struct MessageOut *_msj);
/*
** ===================================================================
**     Method      :  BoxPri1c_ShowGetter 
**     Type        :  Static
**     Description :  Muestra el getter al display inferior
** ===================================================================
*/
void BoxPri1c_ShowGetter(const void * _getter,
                         void * Obj);

/*
** ===================================================================
**     Method      :  BoxPri1c_ShowProp 
**     Type        :  Static
**     Description :  Muestr la propiedad al display inferior
** ===================================================================
*/
void BoxPri1c_ShowProp( const void * _prop,
                        void * Obj);
                        
#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT                     
                   
                        

#endif