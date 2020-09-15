//
// Created by draw on 19-5-11.
//

#ifndef _M84_H
#define _M84_H

#include "Command.h"


class M84:public Command
{
public:
    M84();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_M84_H
