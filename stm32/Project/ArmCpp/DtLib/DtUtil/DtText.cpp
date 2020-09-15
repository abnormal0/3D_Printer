//
// Created by draw on 19-5-11.
//

#include "DtText.h"


DtText &DtText::operator<<(double d)
{
    if (d < 0)
    {
        Buff[Len++] = '-';
        d = -d;
    }

    u32 n = (u32) d;
    u32 p = (u32) ((d - n) * 100);

    if (n)
    {
        u32 k = 1;
        while (n / k)
        {
            k *= 10;
        }

        while (k /= 10)
        {
            Buff[Len++] = n / k + '0';
            n %= k;
        }
    } else
    {
        Buff[Len++] = '0';
    }

    Buff[Len++] = '.';

    Buff[Len++] = p / 10 + '0';
    Buff[Len++] = (p % 10) + '0';

    return *this;
}

DtText &DtText::operator<<(const char *s)
{
    while (*s != 0)
    {
        Buff[Len++] = *s++;
    }
    return *this;
}

DtText &DtText::operator<<(u8 *s)
{
    while (*s != 0)
    {
        Buff[Len++] = *s++;
    }
    return *this;
}

DtText &DtText::operator<<(char c)
{
    Buff[Len++] = c;
    return *this;
}

DtText &DtText::operator<<(u32 n)
{
    u8 Tmp;

    for (int k = 28; k >= 0; k -= 4)
    {
        Tmp = (n >> k) & 0xF;
        if (Tmp < 10)
        {
            Buff[Len++] = Tmp + '0';
        } else
        {
            Buff[Len++] = Tmp + ('A' - 10);
        }
    }


    return *this;
}
