//
// Created by Nc2016 on 2019/1/5.
//

#ifndef __POWER_H
#define __POWER_H

#include "Descriptor.h"

enum Power_Scale {
    Power_Scale1 = 0x1u,
    Power_Scale2 = 0x0u,
};

class Power
{
public:
    __IO u32 CR;   /*!< PWR power control register,        Address offset: 0x00 */
    __IO u32 CSR;  /*!< PWR power control/status register, Address offset: 0x04 */
    void Scale(Power_Scale scale);
};

#define PWR                   ((Power *) 0x40007000U)


#endif //HELLO_POWER_H
