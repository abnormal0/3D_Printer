//
// Created by draw on 19-5-11.
//

#ifndef _G0_H
#define _G0_H

#include "Command.h"


class G0:public Command
{
public:
    G0();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_G0_H
