#ifndef _SETS_H
#define _SETS_H

#include "Array.h"

#pragma CONST_SEG PARAMETERS_PAGE
extern volatile const int SetC;
#pragma CONST_SEG DEFAULT

extern const struct Array arrayCodGetters;
#define COD_GETTERS_ARRAY arrayCodGetters

extern const struct BlockConstBoxPropBase CBoxSetC;

#define CONTENEDOR_CODIGO &SetC
#define SETS_FST_BOX_SET CBoxSetC


void Sets_Init(void);
void Sets_Init2(uint nListas);

void Sets_AddBoxes(void);

#endif