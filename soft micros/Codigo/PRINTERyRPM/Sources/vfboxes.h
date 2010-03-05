#ifndef _VF_BOXES_H
#define _VF_BOXES_H 

#define REP_TIME  6    //tiempo de repeticion de carteles en segundos
 void vitroFusionHandler(void);
 
 void ProcesoTeclasVF(void);
 
 bool cartelesHandler (void);
 
 void muestraUnaVez (char * msj);
 
 extern const Numerico Vrmp1;
 extern const Numerico Vrmp2;
 extern const Numerico Vrmp3;
 extern const Numerico Vrmp4;
 extern const Numerico Vrmp5;
 extern const Numerico Vrmp6;
 extern const Numerico Vrmp7;
 extern const Numerico Vrmp8;
 extern const Numerico Vrmp9;
 extern const Numerico Vrmp10;
 extern const Numerico Tmpm1;
 extern char flagCartel;
 extern char tecla_d;
 extern char flagComCartel;
#endif