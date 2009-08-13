#ifndef _BOX_PRINCIPAL_N_C_H
#define _BOX_PRINCIPAL_N_C_H


#include <stdtypes.h>

#include "ClassBox.h"
#include "Sensor.h"
#include "PropWithInc.h"
#include "MessagesOut.h"
#include "Timer.h"
#include "Mydefines.h"
#include "Array.h"

#pragma DATA_SEG BoxPrincipalNC_DATA                                            
#pragma CODE_SEG BoxPrincipalNC_CODE                     
#pragma CONST_SEG DEFAULT       /* Constant section for this module */
                  


struct BlockConstBoxPriNC{
  struct BlockBoxConstruct _base;
  struct Array * getters; 
  struct MessageOut * msjs; 
};

struct BoxPriNC{
  struct Box _box;
//Protected:  
  struct getter ** getters;
  struct MessageOut * msjs;		// manejador de mensajes
  uint msj_index[CANTIDAD_DISPLAYS];             // indice del msj a mostrar
  struct Timer timerPri;		// Timer de refresco
};

extern const struct BoxClass BoxPriNC;

#endif