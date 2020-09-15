//
// Created by draw on 19-5-15.
//

#ifndef _M105_H
#define _M105_H

#include "Command.h"


class M105:public Command
{
public:

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_M105_H
