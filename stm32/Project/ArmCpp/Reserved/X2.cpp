//
// Created by draw on 19-5-5.
//

#include "X2.h"


X2::X2()
{
    n = 1;
    c[0] = 'B';
    pr[0] = 0;
}

void X2::Ent(u8 *p)
{
    ParaSolve(p);
}

void X2::Exe()
{
    Tf.ReadBlock((u32 *) TF_Buff, (u32)pr[0]);
    USART2->SendHex(TF_Buff, 512);
}
