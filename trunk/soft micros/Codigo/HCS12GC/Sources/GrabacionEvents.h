#ifndef _GRABACION_EVENTS_H
#define _GRABACION_EVENTS_H

#include "stdtypes.h"

/*#include "Mydefines.h"

#ifdef _ADQUISIDOR
#include "Adquisidor.h"
  #define EraseEvents(Addr) Adq_OnErase(Addr)
#else
  #define EraseEvents(Addr)
#endif
*/
//////////////////////////
void PreWrite(void);

void OnWrite(void);  // Evento a llamar al terminar una grabación en la FLASH

void OnErase(uint Page); // Evento a llamar al terminar el borrado de una pagina de FLASH

#endif 