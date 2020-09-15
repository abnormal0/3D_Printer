//
// Created by draw on 19-4-17.
//

#ifndef _USARTBUFFER_H
#define _USARTBUFFER_H

#include "Descriptor.h"

#define USART_AREA_SIZE 128u

extern u8 USART_Area[];

class UsartBuffer
{
public:
    u8* out=USART_Area;
    u32 end=0;
};

extern UsartBuffer ub;


#endif //ARMCPP_USARTBUFFER_H
