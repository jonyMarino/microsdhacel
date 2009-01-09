#ifndef _BOXES_SET_H
#define _BOXES_SET_H 

///////////VERSION/BLOQUEOS////////
typedef enum{
  VER_BL1,
  VER_BL2,
  VER_BL3,
  VER_BL4,
  VER_DIF,
  VER_RTSP
}TVersion;

#define MAX_VALUE_VERSION 3

//ModMain
int get_DirPar(byte a);
byte set_DirPar(int val,byte a);
int get_LimSup_DirPar(byte a);
int get_LimInf_DirPar(byte a);
// SetC
int get_SetC(void);
byte set_SetC(int val, byte a);			
// Version
int get_Version(void);
byte set_Version(int val, byte a);		 	 
int get_LimSup_Version(void);
// retorna la direccion del parametro a mostrar en Main
int get_DirPar(byte a);


#endif