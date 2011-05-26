#ifndef _SENSOR_HPP
#define _SENSOR_HPP


#include "Standard/Getter.hpp"
#include "MethodContainer/MethodContainer.hpp"
#include "OOC/lang/reflect/lib_cpp/Method.hpp"

class Sensor : public Getter {
  public:
    Sensor(){}
    void addOnNuevoValorListener(const struct Method* metodo);
    void deleteOnNuevoValorListener(const struct Method * metodo);

    virtual unsigned char getDecimales()=0;

    

      enum TSensorState {
        SENSOR_OK,
        SENSOR_OF,
        SENSOR_UF
      };
      
      
    TSensorState getEstado();
    
    int getLimiteInferior();

    int getLimiteSuperior();

  protected:
    void callOnNuevoValorListeners();
   
  private:
    MethodContainer listeners;




};
#endif
