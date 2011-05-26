#ifndef _BOX_PRINCIPAL_CONTROL_SD_HPP
#define _BOX_PRINCIPAL_CONTROL_SD_HPP

#include "Box.hpp"
#include "Propiedades/ConstructorPropiedadGetter.hpp"
#include "MessagesOut/MessagesOut.hpp"
#include "Timer/FlagTimer/FlagTimer.hpp"
#include "PE/include/PE_Types.h"
#include "Memoria/Prom/Flash/FlashBkp.hpp"
#include "Propiedades/PropiedadGetterVisual/PropGetterVisual.hpp"

#pragma DATA_SEG BoxPrincipalControlSD_DATA                                            
#pragma CODE_SEG BoxPrincipalControlSD_CODE                     
#pragma CONST_SEG DEFAULT       /* Constant section for this module */

#define CANTIDAD_CANALES 4                 

#define PRI_PAR_SECONDS  5000  //El parametro se muestra 5 segundos luego de 'u' o 'd'
#define REFRESH_SECONDS  2000 
#ifndef TIME_BETWEEN_PARS
  #define TIME_BETWEEN_PARS 2000
#endif

struct ConstructorBoxPrincipalControlSD{
  struct ConstructorBox super;
  Getter ** snsrs; 
  MessagesOut * msjs[CANTIDAD_CANALES]; 
  FlashBkp * flash;   
   
};

class BoxPrincipalControlSD:public Box{
  public:
    BoxPrincipalControlSD(struct ConstructorBoxPrincipalControlSD * constructor);
    virtual ~BoxPrincipalControlSD();
    virtual Box * procesarTecla(uchar tecla,TEstadoBox& estado);
    
  protected:
    struct ConstructorBoxPrincipalControlSD * constructor;
    FlagTimer timerPri;		// Timer de refresco
    FlagTimer timerRefresh;
    
    uint msj_index[CANTIDAD_CANALES];       // indice del msj a mostrar
    
 // private:
   // bool _refrescar;  
    
};

struct BoxPrincipalControlSDFactory:public BoxFactory{
  virtual Box& getBox(const void*args,void*obj,uchar numObjeto)const{
    return *new BoxPrincipalControlSD((struct ConstructorBoxPrincipalControlSD *)args);
  }
};

extern const struct BoxPrincipalControlSDFactory boxPrincipalControlSDFactory; 

                        
#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT                     
                   
                        





#endif