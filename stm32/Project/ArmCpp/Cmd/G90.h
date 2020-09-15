//
// Created by draw on 19-5-11.
//

#ifndef _G90_H
#define _G90_H

#include "Command.h"


class G90:public Command
{
public:
    G90();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_G90_H
