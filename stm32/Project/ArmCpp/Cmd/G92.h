//
// Created by draw on 19-5-11.
//

#ifndef _G92_H
#define _G92_H

#include "Command.h"


class G92:public Command
{
public:
    G92();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_G92_H
