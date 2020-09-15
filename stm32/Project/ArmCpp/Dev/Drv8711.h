//
// Created by draw on 19-5-11.
//

#ifndef _DRV8711_H
#define _DRV8711_H

#include "Descriptor.h"

enum Drv8711_Indexer
{
    Drv8711_Indexer_1 = 0b0000,
    Drv8711_Indexer_2 = 0b0001,
    Drv8711_Indexer_4 = 0b0010,
    Drv8711_Indexer_8 = 0b0011,
    Drv8711_Indexer_16 = 0b0100,
    Drv8711_Indexer_32 = 0b0101,
    Drv8711_Indexer_64 = 0b0110,
    Drv8711_Indexer_128 = 0b0111,
    Drv8711_Indexer_256 = 0b1000,
};

enum Drv8711_Reg
{
    Drv8711_Reg_Ctrl = 0x00,
    Drv8711_Reg_Torque = 0x01,
    Drv8711_Reg_Off = 0x02,
    Drv8711_Reg_Blank = 0x03,
    Drv8711_Reg_Decay = 0x04,
    Drv8711_Reg_Stall = 0x05,
    Drv8711_Reg_Driver = 0x06,
    Drv8711_Reg_Status = 0x07,
};

enum Drv8711_Status
{
    Drv8711_Status_Ots=0b1<<0,
    Drv8711_Status_Aocp=0b1<<1,
    Drv8711_Status_Bocp=0b1<<2,
    Drv8711_Status_Apdf=0b1<<3,
    Drv8711_Status_Bpdf=0b1<<4,
    Drv8711_Status_Uvlo=0b1<<5,
    Drv8711_Status_Std=0b1<<6,
    Drv8711_Status_Stdlat=0b1<<7,
};


class Drv8711
{

private:
    vu32 *Cs;
    vu32 *Ck;
    vu32 *Di;
    vu32 *Do;
    vu32 *Sp;
    vu32 *Ft;
    vu32 *St;

    vu32 *Dir;
    vu32 *Step;
    vu32 *Limit;

public:
    void
    Constuct(vu32 *cs, vu32 *ck, vu32 *di, vu32 *du, vu32 *sp, vu32 *ft, vu32 *st, vu32 *dir, vu32 *step, vu32 *lim);

    u16 Read(Drv8711_Reg addr);

    void Write(Drv8711_Reg addr, u16 da);

    void Indexer(Drv8711_Indexer indexer);

    void Home(u32 p);

    void Enable();

    void Move(s32 s, u32 p);

    void Disable();

    void Curr(float i);
};


#endif //ARMCPP_DRV8711_H
