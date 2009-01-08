#ifndef _BOX_PRINCIPAL_PROTECTED_H
#define _BOX_PRINCIPAL_PROTECTED_H

void BoxPri_Constructor(void* self,
                        struct SensorVisual * sensor,
                        struct MessageOut *_msj);
                        
void * BoxPri_Destructor(void* self);

#endif