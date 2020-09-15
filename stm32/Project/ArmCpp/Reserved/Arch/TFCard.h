//
// Created by draw on 19-5-4.
//

#ifndef _TFCARD_H
#define _TFCARD_H


#include "Descriptor.h"



enum TF_Cmd
{
    Go_Idle_State=0,
};

class TFCard
{
public:
    u32 RCA;
    u32 CID[4];
    u32 CSD[4];

    u32 BlockNbr;                     /*!< Specifies the Card Capacity in blocks           */
    u32 BlockSize;                    /*!< Specifies one block size in bytes               */

    void WriteBlock(u32 *data, u32 addr);

    void Erase(u32 s, u32 e);

public:
    bl SetUp();
    void ReadBlock(u32 *buf, u32 addr);

private:
    void SolveInfo();


};

extern TFCard Tf;
extern u8 TF_Buff[];


#endif //ARMCPP_TFCARD_H
