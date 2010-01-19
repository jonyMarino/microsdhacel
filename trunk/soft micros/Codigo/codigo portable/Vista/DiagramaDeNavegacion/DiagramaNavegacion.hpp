#ifndef _DIAGRAMA_NAVEGACION_HPP
#define _DIAGRAMA_NAVEGACION_HPP

#include "OOC/util/lib_cpp/Array.h"
#include "BoxList.hpp"
#include "Box.hpp"
#include "Timer/RlxMTimer/RlxMTimer.hpp"
#include "Vista/Frente8SegTeclasYLeds/FrenteCustom.hpp"
#include "OOC/lang/reflect/lib_cpp/Method.hpp"
#include "FstBoxPointer.hpp"
//#include "Errores.h"
//#include "BoxPrincipal.h"

#pragma DATA_SEG DIAGRAMA_NAVEGACION_DATA 
#pragma CODE_SEG DIAGRAMA_NAVEGACION_CODE
#pragma CONST_SEG DEFAULT

#define _VERSION_TIME 1000

class DiagramaNavegacion{
  public:
    DiagramaNavegacion(const struct BoxList *BoxesOp,const struct Array *accesos,FrenteCustom * frente);
    void procesar(uchar tecla);
    void refresh(void);
  private:
    FrenteCustom * frente;
    struct Method metodoParaTimer;
    RlxMTimer * timer;
    const struct Array *accesos;
    const struct BoxList * boxesOp;
    uchar boxListCount;
    uchar listCount;
    uchar accessCount;
    Box * boxActual;
    void goPrincipal();
    struct FstBoxPointer* opgetFstBoxP();
    struct FstBoxPointer* getActualFstBoxP();
    static void showCompilacion(void*);   
    static void jumpToOperador(void*);  
};


#pragma DATA_SEG DEFAULT 
#pragma CODE_SEG DEFAULT

#endif