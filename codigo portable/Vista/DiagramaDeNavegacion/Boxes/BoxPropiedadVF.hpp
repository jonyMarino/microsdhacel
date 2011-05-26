#ifndef _BOX_PROPIEDAD_VF_HPP
#define _BOX_PROPIEDAD_VF_HPP


#include "Box.hpp"
#include "Propiedades/PropiedadGetterVisual/PropGetterVisualVF.hpp"
#include "Propiedades/ConstructorPropiedadGetter.hpp"
#include "PE/include/PE_Types.h"
//#include "BoxPropiedadEntradaCondicional.hpp"

class BoxPropiedadVF:public Box{
  public:
    BoxPropiedadVF();
    virtual ~BoxPropiedadVF();
    /*
    ** ===================================================================
    **     Method      :  refresh 
    **     Description :  Funcion para refrescar los valores del Box
    ** ===================================================================
    */
    void refresh();
    /*
    ** ===================================================================
    **     Method      :  procesarTecla 
    **     Description :  Funcion que procesa la tecla del Box
    **     Returns:     - STAY_BOX Sigue el mismo Box (si la tecla es de salida
    **                    devuelve NULL ya que no tiene información del siguiente Box)
    **                  - EXIT_BOX si el Box esta en condición de salida.
    **                  - Constructor del siguiente box
    ** ===================================================================
    */
    virtual Box * procesarTecla(uchar tecla,TEstadoBox& estado);
    
    void printDescripcion(const char * str, OutputStream& os);
  protected:
    void setPropiedad(PropGetterVisualVF& propiedad,bool isIncrementable);
    PropGetterVisualVF * getPropiedad();
  
  private:
    PropGetterVisualVF * propiedad;
    bool isIncrementable;
    bool save;
    friend struct BoxPropiedadVFFactory;
    friend struct BoxPropGetterVFFactory;
    friend struct BoxPropiedadEntradaCondicionalFactory;
    friend struct BoxPropGetterEntradaCondicionalFactory;
};

struct ConstructorBoxPropiedadVF{
  struct ConstructorBox super;
  const struct ConstructorPropGetterVisualVF * propiedad;  
};

struct BoxPropiedadVFFactory:public BoxFactory{
  virtual Box& getBox(const void*args,void*obj,uchar numObjeto)const{
    BoxPropiedadVF&b = *new BoxPropiedadVF();
    struct ConstructorBoxPropiedadVF * c = (struct ConstructorBoxPropiedadVF *)args;
    b.setPropiedad(*(PropGetterVisualVF*)&c->propiedad->getPropiedad(obj,numObjeto),TRUE);
    return b;
  }
};

extern const struct BoxPropiedadVFFactory boxPropiedadVFFactory;

struct BoxPropGetterVFFactory:public BoxFactory{
  virtual Box& getBox(const void*args,void*obj,uchar numObjeto)const{
    BoxPropiedadVF &b = *new BoxPropiedadVF();
    struct ConstructorBoxPropiedadVF * c = (struct ConstructorBoxPropiedadVF *)args;
    b.setPropiedad(*(PropGetterVisualVF*)&c->propiedad->getPropiedad(obj,numObjeto),FALSE);
    return b;
  }
};
 
extern const struct BoxPropGetterFactory boxPropGetterFactory;    
#endif