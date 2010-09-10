#ifndef _BOX_PRINCIPAL_VF_HPP
#define _BOX_PRINCIPAL_VF_HPP

#include "BoxPrincipal.hpp"
#include "Propiedades/PropiedadGetterVisual/PropGetterVisual.hpp"

#pragma DATA_SEG BoxPrincipalVF_DATA                                            
#pragma CODE_SEG BoxPrincipalVF_CODE                     
#pragma CONST_SEG DEFAULT       /* Constant section for this module */
                  

struct ConstructorBoxPrincipalVF{
  struct ConstructorBoxPrincipal super;   
};

class BoxPrincipalVF:public BoxPrincipal{
  public:
    BoxPrincipalVF(struct ConstructorBoxPrincipalVF * constructor);
    virtual ~BoxPrincipalVF();
    virtual Box * procesarTecla(uchar tecla,TEstadoBox& estado);
    static void MostrarGetter(const ConstructorPropGetterVisual *_getter,void * obj);
    static void MostrarProp( const ConstructorPropGetterVisual* _prop, void * obj);
    static void Refresh(void);
    static void setRefresh(void);
    
  protected:
    
    static bool priIsProp;       // TRUE: es propiedad, FALSE: es getter
    static bool propCambio;
    static bool propRefres;
    FlagTimer timerProp;
    FlagTimer timerGrab;
    FlagTimer timerRefresh;
    FlagTimer timerMsjDysSup;
    uchar par_seconds;
    static bool isPropGeter;
    static PropGetterVisual * parametroAMostrar;
  
    
};

struct BoxPrincipalVFFactory:public BoxFactory{
  virtual Box& getBox(const void*args,void*obj,uchar numObjeto)const{
    return *new BoxPrincipalVF((struct ConstructorBoxPrincipalVF *)args);
  }
};

extern const struct BoxPrincipalVFFactory boxPrincipalVFFactory; 

                        
#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT                     
                   
                        





#endif