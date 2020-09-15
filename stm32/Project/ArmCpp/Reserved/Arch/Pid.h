//
// Created by draw on 19-4-19.
//

#ifndef _PID_H
#define _PID_H

#include "Main.h"

#define ADC_AREA_LEN 2

extern u16 Adc_Area[];

class Pid
{

public:
    void Start();
};

extern Pid pid;

#endif //ARMCPP_PID_H
