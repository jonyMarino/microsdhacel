#ifndef _LAZOALARMACONTROL_H
#define _LAZOALARMACONTROL_H


#include "LazoControl.hpp"
#include "SalidaRetenida.hpp"
#include "SalidaBanda.hpp"
#include "CntrProporcionalInv.hpp"
#include "CntrRelativo.hpp"
#include "CntrBanda.hpp"

struct ConfLazoCntrAlCntr;

class LazoAlarmaControl : public LazoControl {
  private:
    ConfLazoCntrAlCntr * configuracion;

    union AdaptadorSalidaPool {
      private:
        byte[sizeof(SalidaRetenida)] salidaRetenida;

        byte[sizeof(SalidaBanda)] salidaBanda;

    };
    
    AdaptadorSalidaPool adaptadorSalidaPool;

    union ValorControlPool {
      private:
        byte[sizeof(CntrProporcionalInv)] cntrProporcionalInv;

        byte[sizeof(CntrRelativo)] cntrRelativo;

        byte[sizeof(CntrBanda)] cntrBanda;

    };
    
    ValorControlPool valorControlPool;

};
#endif
