#include "PropGetterVisual.hpp"


/*
** ===================================================================
**     Method      :  PropVisual_getDescripcion 
**     Description :  Obtiene un string con la descripción de la
**                   propiedad
** ===================================================================
*/

const char * PropGetterVisual::getDescripcion(void * self){
  return constructor.descripcion;  
}

/*
** ===================================================================
**     Method      :  PropVisual_Print 
**     Description :  Forma en que imprime 
** ===================================================================
*/
void PropGetterVisual::print(OutputStream& os){
  char * str[5];
  sprintf(str,"%i",getVal());
  os.write(str);
}
