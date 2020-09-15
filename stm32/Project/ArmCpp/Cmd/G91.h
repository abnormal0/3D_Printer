//
// Created by draw on 19-5-11.
//

#ifndef _G91_H
#define _G91_H

#include "Command.h"


class G91:public Command
{
public:
    G91();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_G91_H
