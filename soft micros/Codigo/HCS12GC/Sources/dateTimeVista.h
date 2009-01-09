#ifndef _DATE_TIME_VISTA_H
#define _DATE_TIME_VISTA_H

extern const struct BlockCnstrBoxLin cBoxDateTime;
#define DATE_TIME_BOX cBoxDateTime

extern const struct Array arrayDateTimeGetters;
#define DATE_TIME_GETTERS_ARRAY arrayAdqGetters


void dateTimeVista_addBoxes(const struct BaseTiempo * bt,char * str,uchar num_obj);

#endif