#ifndef _SENSOR_HPP
#define _SENSOR_HPP


#include "Standard/Getter.hpp"
#include "MethodContainer/MethodContainer.hpp"

class Sensor : public Getter {
  public:
    Sensor(){}
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
