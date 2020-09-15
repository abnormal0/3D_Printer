//
// Created by draw on 19-5-13.
//

#include "Ntc.h"

Ntc Rs;

float Ntc::Value(float r)
{
    u32 n = 0, k = 319, m;

    if(r>Ntc_Tab[0]) return -20;
    if(r<Ntc_Tab[319]) return 300;

    while (1)
    {
        m = (n + k) >> 1;
        if (m == n)
        {
            return (Ntc_Tab[k]-r)/(Ntc_Tab[n]-Ntc_Tab[k])+k-20;
        }
        if (Ntc_Tab[m] > r)
        {
            n = m;
        } else
        {
            k = m;
        }
    }
}
