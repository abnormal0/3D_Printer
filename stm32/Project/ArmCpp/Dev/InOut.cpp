//
// Created by draw on 19-5-11.
//

#include "InOut.h"
#include "Msp.h"

InOut Io;

void InOut::Tog1(void)
{
    *PBO12=!(*PBO12);
}

void InOut::Beep(bl on)
{
    *PBO12=on;
}

void InOut::Construct()
{
    GPIOB->OutPp(12);
    GPIOB->Down(12);

}
