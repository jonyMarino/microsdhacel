#ifndef _BT_FECHA_PERSISTENTE_H
#define _BT_FECHA_PERSISTENTE_H


#include "BaseTiempo.h"
#include "BTFPConf.h"

/*C++ 
class BTFechaPersistente:public BaseTiempo
{
 public:
    BTFechaPersistente(BTFPConf* conf);
  private:
    BTFPConf * conf;
}
*/
struct BTFechaPersistente {
  struct BaseTiempo super;
  struct BTFPConf * conf;
};

extern const struct BaseTiempoClass BTFechaPersistente;


#endif
