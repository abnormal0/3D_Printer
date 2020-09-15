//
// Created by Nc2016 on 2019/1/4.
//

#ifndef __TICK_H
#define __TICK_H

#include "Descriptor.h"

enum Tick_Div{
    Tick_Div1=0x4U,
    Tick_Div8=0U,
};

enum Tick_Irq{
    Tick_Irq_Disable=0U,
    Tick_Irq_Enable=0x2U,
};

class Tick
{
public:
    __IO u32 CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
    __IO u32 LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
    __IO u32 VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
    __I  u32 CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */

    void Delay(u32 t);

    void Period(u32 us);

    void Ctrl(Tick_Div div, Tick_Irq irq);

    void Start();

    bool Reloaded();

    void Stop();
};

#define TICK                 ((Tick *) 0xE000E010U)


#endif //HELLO_TICK_H
