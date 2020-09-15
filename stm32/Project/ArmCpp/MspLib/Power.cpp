//
// Created by Nc2016 on 2019/1/5.
//

#include "Power.h"

void Power::Scale(Power_Scale scale)
{
    switch (scale)
    {
        case Power_Scale1:
            CR |= 0x1u << 14;
            break;
        case Power_Scale2:
            CR &= ~(0x1u << 14);
            break;
    }
}
