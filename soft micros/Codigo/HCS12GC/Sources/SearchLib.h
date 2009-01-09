#ifndef _SEARCH_LIB_H
#define _SEARCH_LIB_H

typedef enum{
  OK,
  OF,
  UF
}LinState;


LinState BinSearchLin(int x,int * y, int * xdat,int* ydat, int max);

#endif