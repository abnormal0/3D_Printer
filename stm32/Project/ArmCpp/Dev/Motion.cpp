//
// Created by draw on 19-5-11.
//

#include "Motion.h"
#include "Core.h"
#include "DtLib.h"
#include "Dev.h"
#include "Msp.h"
//#include "arm_math.h"

__ccm Motion Mn;


void Motion::Constuct()
{
    Vx=300;
    Vy=300;
    Vz=300;//默认最低速度
    Ve=300;

    Ax=0.99f;
    Ay=0.99f;
    Az=0.99f;//加速算法乘法参数
    Ae=0.99f;

    Lx=0;
    Ly=0;//xiangliang
    Lz=0;
    Le=0;

    X = 0;
    Y = 0;//position
    Z = 0;
    E = 0;

    Px=0;
    Py=0;
    Pz=0;
    Pe=0;

    Abs = True;
    Mmpm = 500;//mm/min jichu
    Fr=1.0f;

    GPIOC->OutPp(7);
    GPIOA->OutPp(8);
    GPIOC->OutPp(2);
    GPIOB->OutPp(9);

    GPIOB->OutPp(14);
    GPIOA->OutPp(9);
    GPIOC->OutPp(3);
    GPIOC->OutPp(0);

    XDir = PCO07;
    YDir = PAO08;
    ZDir = PCO02;
    EDir = PBO09;

    XStep = PBO14;
    YStep = PAO09;
    ZStep = PCO03;
    EStep = PCO00;

    GPIOC->OutPp(6);
    GPIOA->OutPp(10);
    GPIOC->OutPp(1);
    //*PCO01=1;
    GPIOB->OutPp(8);


    GPIOB->OutPp(5);
    GPIOB->OutPp(6);
    //GPIOB->Up(5);
    GPIOB->In(4);
    GPIOB->Pull(4, Pull_Up);
    GPIOB->OutPp(7);
    GPIOB->Up(7);
    GPIOB->In(3);
    GPIOA->In(15);

    GPIOB->In(2);
    GPIOB->Pull(2, Pull_Up);
    GPIOB->In(1);
    GPIOB->Pull(1, Pull_Up);
    GPIOB->In(0);
    GPIOB->Pull(0, Pull_Up);
    GPIOC->In(5);


    Mx.Constuct(PCO06, PBO06, PBO05, PBI04, PBO07, PBI03, PAI15, PCO07, PBO14, PBI02);
    My.Constuct(PAO10, PBO06, PBO05, PBI04, PBO07, PBI03, PAI15, PAO08, PAO09, PBI01);
    Mz.Constuct(PCO01, PBO06, PBO05, PBI04, PBO07, PBI03, PAI15, PCO02, PCO03, PBI00);
    Me.Constuct(PBO08, PBO06, PBO05, PBI04, PBO07, PBI03, PAI15, PBO09, PCO00, PCI05);


    Mx.Write(Drv8711_Reg_Ctrl, 0xC2A);
    Mx.Write(Drv8711_Reg_Torque, 0x12A);
    Mx.Write(Drv8711_Reg_Blank, 0x100);
    Mx.Write(Drv8711_Reg_Decay, 0x510);
    Mx.Write(Drv8711_Reg_Driver, 0xA59);
    Mx.Write(Drv8711_Reg_Ctrl, 0xC2B);
    Mx.Write(Drv8711_Reg_Status, 0);

    My.Write(Drv8711_Reg_Ctrl, 0xC28);
    My.Write(Drv8711_Reg_Torque, 0x12A);
    My.Write(Drv8711_Reg_Blank, 0x100);
    My.Write(Drv8711_Reg_Decay, 0x510);
    My.Write(Drv8711_Reg_Driver, 0xA59);
    My.Write(Drv8711_Reg_Ctrl, 0xC29);
    My.Write(Drv8711_Reg_Status, 0);

    Mz.Write(Drv8711_Reg_Ctrl, 0xC2A);
    Mz.Write(Drv8711_Reg_Torque, 0x11F);
    Mz.Write(Drv8711_Reg_Blank, 0x100);
    Mz.Write(Drv8711_Reg_Decay, 0x510);
    Mz.Write(Drv8711_Reg_Driver, 0xA59);
    Mz.Write(Drv8711_Reg_Ctrl, 0xC2B);
    Mz.Write(Drv8711_Reg_Status, 0);

    Me.Write(Drv8711_Reg_Ctrl, 0xC2B);
    Me.Write(Drv8711_Reg_Torque, 0x12F);
    Me.Write(Drv8711_Reg_Blank, 0x100);
    Me.Write(Drv8711_Reg_Decay, 0x510);
    Me.Write(Drv8711_Reg_Driver, 0xA59);
    Me.Write(Drv8711_Reg_Ctrl, 0xC2B);
    Me.Write(Drv8711_Reg_Status, 0);

}

void Motion::Speed(u32 f)
{

    Mmpm = Fr*f;
}

void Motion::Line(double x, double y, double z, double e)
{
    s32 dx, dy, dz, de; // Delta position in step
    s32 fx, fy, fz, fe; // Final position in step

    fx=Math.Round(x*Cg.ResuX);
    fy=Math.Round(y*Cg.ResuY);
    fz=Math.Round(z*Cg.ResuZ);
    fe=Math.Round(e*Cg.ResuE);

    if (Abs)
    {
        X=x;
        Y=y;
        Z=z;
        E=e;

        dx = fx - Px;
        dy = fy - Py;
        dz = fz - Pz;
        de = fe - Pe;

        Px = fx;    // Calibration after motion
        Py = fy;
        Pz = fz;
        Pe = fe;

    } else
    {

        X += x;
        Y += y;
        Z += z;
        E += e;

        dx = fx;
        dy = fy;
        dz = fz;
        de = fe;

        Px += fx;
        Py += fy;
        Pz += fz;
        Pe += fe;
    }


    if (Lx * dx + Ly * dy > 0)
    {
        Ac = False;
    } else
    {
        Ac = True;
    }

    Lx=dx;
    Ly=dy;


    if (dx < 0) // Direction Judgement
    {
        *XDir = 0;
        dx = -dx;
    } else
    {
        *XDir = 1;
    }
    if (dy < 0)
    {
        *YDir = 0;
        dy = -dy;
    } else
    {
        *YDir = 1;
    }
    if (dz < 0)
    {
        *ZDir = 0;
        dz = -dz;
    } else
    {
        *ZDir = 1;
    }
    if (de < 0)
    {
        *EDir = 0;
        de = -de;
    } else
    {
        *EDir = 1;
    }

    Li.Clean(); // Len = 0;
    Li.Add(dx);
    Li.Add(dy);
    Li.Add(dz);
    Li.Add(de);

    u32 hs;

    switch (Li.Index(Li.Max()))
    {
        case 0:
            hs = 30000000.0 / (Cg.ResuX * Mmpm);
            XLine(dx, dy, dz, de, hs);
            break;
        case 1:
            hs = 30000000.0 / (Cg.ResuY * Mmpm);
            YLine(dx, dy, dz, de, hs);
            break;
        case 2:
            hs = 30000000.0 / (Cg.ResuZ * Mmpm);
            ZLine(dx, dy, dz, de, hs);
            break;
        case 3:
            hs = 30000000.0 / (Cg.ResuE * Mmpm);
            ELine(dx, dy, dz, de, hs);
            break;
    }
}

void Motion::XLine(s32 x, s32 y, s32 z, s32 e, u32 hs)
{

    u32 ts = Vx;

    s32 ny, nz, ne;
    ny = (y - x) << 1;
    nz = (z - x) << 1;
    ne = (e - x) << 1;

    s32 ky, kz, ke;
    ky = y << 1;
    kz = z << 1;
    ke = e << 1;

    s32 py, pz, pe;
    py = (y << 1) - x;
    pz = (z << 1) - x;
    pe = (e << 1) - x;


    for (int k = 0; k < x; k++)
    {
        *XStep = 1;
        if (py > 0)
        {
            *YStep = 1;
            py += ny;
        } else
        {
            py += ky;
        }

        if (pz > 0)
        {
            *ZStep = 1;
            pz += nz;
        } else
        {
            pz += kz;
        }

        if (pe > 0)
        {
            *EStep = 1;
            pe += ne;
        } else
        {
            pe += ke;
        }

        if (Ac)
        {
            if (ts > hs)
            {
                ts *= Ax;
            }
        } else
        {
            ts = hs;
        }


        Os.uSleep(ts);
        *XStep = 0;
        *YStep = 0;
        *ZStep = 0;
        *EStep = 0;
        Os.uSleep(ts);
    }
}

void Motion::YLine(s32 x, s32 y, s32 z, s32 e, u32 hs)
{
    u32 ts = Vy;

    s32 nx, nz, ne;
    nx = (x - y) << 1;
    nz = (z - y) << 1;
    ne = (e - y) << 1;

    s32 kx, kz, ke;
    kx = x << 1;
    kz = z << 1;
    ke = e << 1;

    s32 px, pz, pe;
    px = (x << 1) - y;
    pz = (z << 1) - y;
    pe = (e << 1) - y;


    for (int k = 0; k < y; k++)
    {
        *YStep = 1;
        if (px > 0)
        {
            *XStep = 1;
            px += nx;
        } else
        {
            px += kx;
        }

        if (pz > 0)
        {
            *ZStep = 1;
            pz += nz;
        } else
        {
            pz += kz;
        }

        if (pe > 0)
        {
            *EStep = 1;
            pe += ne;
        } else
        {
            pe += ke;
        }

        if (Ac)
        {
            if (ts > hs)
            {
                ts *= Ay;
            }
        } else
        {
            ts = hs;
        }
        Os.uSleep(ts);
        *XStep = 0;
        *YStep = 0;
        *ZStep = 0;
        *EStep = 0;
        Os.uSleep(ts);
    }
}

void Motion::ZLine(s32 x, s32 y, s32 z, s32 e, u32 hs)
{
    u32 ts = Vz;
    s32 ny, nx, ne;
    ny = (y - z) << 1;
    nx = (x - z) << 1;
    ne = (e - z) << 1;

    s32 ky, kx, ke;
    ky = y << 1;
    kx = x << 1;
    ke = e << 1;

    s32 py, px, pe;
    py = (y << 1) - z;
    px = (x << 1) - z;
    pe = (e << 1) - z;


    for (int k = 0; k < z; k++)
    {
        *ZStep = 1;
        if (py > 0)
        {
            *YStep = 1;
            py += ny;
        } else
        {
            py += ky;
        }

        if (px > 0)
        {
            *XStep = 1;
            px += nx;
        } else
        {
            px += kx;
        }

        if (pe > 0)
        {
            *EStep = 1;
            pe += ne;
        } else
        {
            pe += ke;
        }

        if (ts > hs)
        {
            ts *= Az;
        }
        Os.uSleep(ts);
        *XStep = 0;
        *YStep = 0;
        *ZStep = 0;
        *EStep = 0;
        Os.uSleep(ts);
    }
}

void Motion::ELine(s32 x, s32 y, s32 z, s32 e, u32 hs)
{
    s32 ny, nz, nx;
    ny = (y - e) << 1;
    nz = (z - e) << 1;
    nx = (x - e) << 1;

    s32 ky, kz, kx;
    ky = y << 1;
    kz = z << 1;
    kx = x << 1;

    s32 py, pz, px;
    py = (y << 1) - e;
    pz = (z << 1) - e;
    px = (x << 1) - e;


    for (int k = 0; k < e; k++)
    {
        *EStep = 1;
        if (py > 0)
        {
            *YStep = 1;
            py += ny;
        } else
        {
            py += ky;
        }

        if (pz > 0)
        {
            *ZStep = 1;
            pz += nz;
        } else
        {
            pz += kz;
        }

        if (px > 0)
        {
            *XStep = 1;
            px += nx;
        } else
        {
            px += kx;
        }

        Os.uSleep(hs);
        *XStep = 0;
        *YStep = 0;
        *ZStep = 0;
        *EStep = 0;
        Os.uSleep(hs);
    }
}

void Motion::Home()
{

    Mz.Move(3000, 200);
    Mx.Home(20);
    X = 0;
    Px=0;
    My.Home(20);
    Y = 0;
    Py=0;
    Mz.Home(200);
    Z = 0;
    Pz=0;
    E = 0;
    Pe=0;

    Com.Ok();
}

void Motion::SetX(double p)
{
    X=p;Px=Math.Round(p*Cg.ResuX);
}

void Motion::SetY(double p)
{
    Y=p;Py=Math.Round(p*Cg.ResuY);
}

void Motion::SetZ(double p)
{
    Z=p;Pz=Math.Round(p*Cg.ResuZ);
}

void Motion::SetE(double p)
{
    E=p;Pe=Math.Round(p*Cg.ResuE);
}


