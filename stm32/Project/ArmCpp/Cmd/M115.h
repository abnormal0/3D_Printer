//
// Created by draw on 19-5-21.
//

#ifndef _M115_H
#define _M115_H

#include "Command.h"


class M115:public Command
{
public:
    void Ent(u8 *p) override;

};


#endif //ARMCPP_M115_H
