#ifndef _BOX_PROPIEDAD_HPP
#define _BOX_PROPIEDAD_HPP


#include "Box.hpp"
#include "Propiedades/PropiedadGetterVisual/PropGetterVisual.hpp"
#include "Propiedades/ConstructorPropiedadGetter.hpp"
#include "PE/include/PE_Types.h"
//#include "BoxPropiedadEntradaCondicional.hpp"

class BoxPropiedad:public Box{
  public:
    BoxPropiedad();
    virtual ~BoxPropiedad();
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
    void setPropiedad(PropGetterVisual& propiedad,bool isIncrementable);
    PropGetterVisual * getPropiedad();
  
  private:
    PropGetterVisual * propiedad;
    bool isIncrementable;
    bool save;
    friend struct BoxPropiedadFactory;
    friend struct BoxPropGetterFactory;
    friend struct BoxPropiedadEntradaCondicionalFactory;
    friend struct BoxPropGetterEntradaCondicionalFactory;
};

struct ConstructorBoxPropiedad{
  struct ConstructorBox super;
  const struct ConstructorPropGetterVisual * propiedad;  
};

struct BoxPropiedadFactory:public BoxFactory{
  virtual Box& getBox(const void*args,void*obj,uchar numObjeto)const{
    BoxPropiedad&b = *new BoxPropiedad();
    struct ConstructorBoxPropiedad * c = (struct ConstructorBoxPropiedad *)args;
    b.setPropiedad(*(PropGetterVisual*)&c->propiedad->getPropiedad(obj,numObjeto),TRUE);
    return b;
  }
};

extern const struct BoxPropiedadFactory boxPropiedadFactory;

struct BoxPropGetterFactory:public BoxFactory{
  virtual Box& getBox(const void*args,void*obj,uchar numObjeto)const{
    BoxPropiedad&b = *new BoxPropiedad();
    struct ConstructorBoxPropiedad * c = (struct ConstructorBoxPropiedad *)args;
    b.setPropiedad(*(PropGetterVisual*)&c->propiedad->getPropiedad(obj,numObjeto),FALSE);
    return b;
  }
};
 
extern const struct BoxPropGetterFactory boxPropGetterFactory;    
#endif