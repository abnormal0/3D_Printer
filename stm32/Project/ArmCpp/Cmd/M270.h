//
// Created by draw on 19-5-24.
//

#ifndef _M270_H
#define _M270_H

#include "Command.h"


class M270:public Command
{
public:
    M270();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_M270_H
