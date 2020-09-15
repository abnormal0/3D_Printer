//
// Created by draw on 19-5-12.
//

#ifndef _PID_H
#define _PID_H

#include "Descriptor.h"

#define PID_CHS 2

#define PID_FLIT 3


class Pid
{
private:
    float Te;
    float Be;


public:
    u16 Buff[16];

    float T;
    float B;

    float Ts;
    float Bs;

    float Kpt;
    float Kdt;
    float Kpb;
    float Kdb;

    float It;
    float Ib;

    u32 Wt;
    u32 Wb;

    void Run();

    void Calcu();

    void Bed();

    void Extr();
};

extern Pid Pi;

#endif //ARMCPP_PID_H
