#ifndef _SENSOR_H
#define _SENSOR_H


#include "Getter.hpp"
#include "MethodContainer.hpp"

class Method;

class Sensor : public Getter {
  public:
    void addOnNuevoValorListener(const struct Method* metodo);
    void deleteOnNuevoValorListener(const struct Method * metodo);

    unsigned char getDecimales();

    

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
