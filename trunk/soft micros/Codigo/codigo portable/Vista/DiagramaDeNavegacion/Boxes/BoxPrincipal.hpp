#ifndef _BOX_PRINCIPAL_HPP
#define _BOX_PRINCIPAL_HPP


#include <stdtypes.h>

#include "Box.hpp"
#include "ConstructorPropiedadGetter.hpp"
#include "MessagesOut/MessagesOut.hpp"
#include "Timer/FlagTimer/FlagTimer.hpp"
#include "PE/include/PE_Types.h"
#include "Memoria/Prom/Flash/FlashBkp.hpp"

#pragma DATA_SEG BoxPrincipal_DATA                                            
#pragma CODE_SEG BoxPrincipal_CODE                     
#pragma CONST_SEG DEFAULT       /* Constant section for this module */
                  

struct ConstructorBoxPrincipal{
  struct ConstructorBox super;
  Getter * snsr1; 
  MessagesOut * msjs; 
  FlashBkp * flash;   
};

class BoxPrincipal:public Box{
  public:
    BoxPrincipal(struct ConstructorBoxPrincipal * constructor);
    virtual ~BoxPrincipal();
    virtual Box * procesarTecla(uchar tecla,TEstadoBox& estado);
  protected:
    struct ConstructorBoxPrincipal * constructor;
    uint msj_index;       // indice del msj a mostrar
    FlagTimer timerPri;		// Timer de refresco

};

struct BoxPrincipalFactory:public BoxFactory{
  virtual Box& getBox(const void*args,void*obj,uchar numObjeto)const{
    return *new BoxPrincipal((struct ConstructorBoxPrincipal *)args);
  }
};

extern const struct BoxPrincipalFactory boxPrincipalFactory; 

                        
#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT                     
                   
                        

#endif