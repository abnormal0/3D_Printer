//
// Created by draw on 19-4-18.
//

#ifndef _CMDMANA_H
#define _CMDMANA_H

#include "Descriptor.h"

class CmdMana
{

public:
    u32 op;
    u32 tp;
    u32 len;

    u32 Line;

    CmdMana();

    void Offer();
    void Take();

    u8 *Check(u8 *s);
};

#endif //ARMCPP_CMDMANA_H
