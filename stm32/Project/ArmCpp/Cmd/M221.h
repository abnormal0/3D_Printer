//
// Created by draw on 19-5-20.
//

#ifndef _M221_H
#define _M221_H

#include "Command.h"


class M221:public Command
{
public:
    void Ent(u8 *p) override;

};


#endif //ARMCPP_M221_H
