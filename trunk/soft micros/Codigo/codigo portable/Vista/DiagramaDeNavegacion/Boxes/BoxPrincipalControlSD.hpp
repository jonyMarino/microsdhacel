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
  MessagesOut * msjs; 
  FlashBkp * flash;   
   
};

class BoxPrincipalControlSD:public Box{
  public:
    BoxPrincipalControlSD(struct ConstructorBoxPrincipalControlSD * constructor);
    virtual ~BoxPrincipalControlSD();
    virtual Box * procesarTecla(uchar tecla,TEstadoBox& estado);
    static void MostrarGetter(const ConstructorPropGetterVisual *_getter,void * obj);
    static void MostrarProp( const ConstructorPropGetterVisual* _prop, void * obj);
    static void Refresh(void);
    static void setRefresh(void);
  protected:
    struct ConstructorBoxPrincipalControlSD * constructor;
    static bool priIsProp;       // TRUE: es propiedad, FALSE: es getter
    static bool propCambio;
    static bool propRefres;
    FlagTimer timerPri;		// Timer de refresco
    FlagTimer timerProp;
    FlagTimer timerGrab;
    FlagTimer timerRefresh;
    uchar par_seconds;
    uint msj_index;       // indice del msj a mostrar
    static PropGetterVisual * parametroAMostrar;
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