#ifndef _BOX_PRINCIPAL_CONTROL_HPP
#define _BOX_PRINCIPAL_CONTROL_HPP

#include "BoxPrincipal.hpp"
#include "Propiedades/PropiedadGetterVisual/PropGetterVisual.hpp"

#pragma DATA_SEG BoxPrincipalControl_DATA                                            
#pragma CODE_SEG BoxPrincipalControl_CODE                     
#pragma CONST_SEG DEFAULT       /* Constant section for this module */
                  

struct ConstructorBoxPrincipalControl{
  struct ConstructorBoxPrincipal super;
   
};

class BoxPrincipalControl:public BoxPrincipal{
  public:
    BoxPrincipalControl(struct ConstructorBoxPrincipalControl * constructor);
    virtual ~BoxPrincipalControl();
    virtual Box * procesarTecla(uchar tecla,TEstadoBox& estado);
    static void MostrarGetter(const ConstructorPropGetterVisual *_getter,void * obj);
    static void MostrarProp( const ConstructorPropGetterVisual* _prop, void * obj);
    static void Refresh(void);
    static void setRefresh(void);
  protected:
  //  struct ConstructorBoxPrincipalControl * constructor;
    static bool priIsProp;       // TRUE: es propiedad, FALSE: es getter
    static bool propCambio;
    static bool propRefres;
    FlagTimer timerProp;
    FlagTimer timerGrab;
    FlagTimer timerRefresh;
    uchar par_seconds;
    static PropGetterVisual * parametroAMostrar;
 // private:
   // bool _refrescar;  
    
};

struct BoxPrincipalControlFactory:public BoxFactory{
  virtual Box& getBox(const void*args,void*obj,uchar numObjeto)const{
    return *new BoxPrincipalControl((struct ConstructorBoxPrincipalControl *)args);
  }
};

extern const struct BoxPrincipalControlFactory boxPrincipalControlFactory; 

                        
#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT                     
                   
                        





#endif