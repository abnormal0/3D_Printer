//
// Created by draw on 19-5-11.
//

#ifndef _G28_H
#define _G28_H

#include "Command.h"


class G28:public Command
{
public:
    G28();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_G28_H
