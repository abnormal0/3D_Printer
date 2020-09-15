//
// Created by draw on 19-5-11.
//

#ifndef _M109_H
#define _M109_H

#include "Command.h"

class M109:public Command
{
public:
    M109();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_M109_H
