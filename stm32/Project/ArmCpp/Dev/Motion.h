//
// Created by draw on 19-5-11.
//

#ifndef _MOTION_H
#define _MOTION_H

#include "Descriptor.h"
#include "Motor.h"
#include "Drv8711.h"

class Axis
{
public:
    double P,V,A;
    s32 L;
};

class Motion
{
public:
    double X, Y, Z, E;
    s32 Px,Py,Pz,Pe;
    u32 Vx, Vy, Vz, Ve;
    double Ax, Ay, Az, Ae;

    s32 Lx, Ly, Lz, Le;

    bl Abs;
    bl Ac;

    u32 Mmpm;
    double Fr;

    vu32 *XDir;
    vu32 *XStep;

    vu32 *YDir;
    vu32 *YStep;

    vu32 *ZDir;
    vu32 *ZStep;

    vu32 *EDir;
    vu32 *EStep;

    Drv8711 Mx;
    Drv8711 My;
    Drv8711 Mz;
    Drv8711 Me;


    void SetX(double p);

    void SetY(double p);

    void SetZ(double p);

    void SetE(double p);

public:
    void Home();

    void Constuct();

    void Speed(u32 f);

    void Line(double x, double y, double z, double e);

private:
    void XLine(s32 x, s32 y, s32 z, s32 e, u32 hs);

    void YLine(s32 x, s32 y, s32 z, s32 e, u32 hs);

    void ZLine(s32 x, s32 y, s32 z, s32 e, u32 hs);

    void ELine(s32 x, s32 y, s32 z, s32 e, u32 hs);
};

extern Motion Mn;


#endif //ARMCPP_MOTION_H
