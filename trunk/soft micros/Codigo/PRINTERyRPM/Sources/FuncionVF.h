#ifndef _FUNCIONVF_H
#define _FUNCIONVF_H

#define ENDVF 0
#define RUNVF 1
#define RMPVF 0
#define MSTVF 1
#define Ti_MES     PRom[R_Tiem1+EtapaCorr-1]
extern char EtapaCorr;
extern char VFmod;
extern char VFstatus;
extern char CantEtapas;
extern long tempActVF;

void calculoTempInstYtiempoMesetaVF (void);


#endif
