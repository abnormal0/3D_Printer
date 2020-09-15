//
// Created by draw on 19-5-12.
//

#ifndef _DTLIST_H
#define _DTLIST_H

#include "Descriptor.h"


template<typename T>    // 类模板，T为模板形参，可以为任何类型
class DtList
{
public:
    T *Buff;
    u32 Len;

public:
    DtList(T *buff);

    void Clean();

    void Add(T e);

    T Max();

    u32 Index(T e);
};

template<typename T>
DtList<T>::DtList(T *buff):Buff(buff)
{
    Len = 0;
}

template<typename T>
void DtList<T>::Clean()
{
    Len = 0;
}

template<typename T>
T DtList<T>::Max()
{
    T Tmp[Len];
    for (int k = 0; k < Len; k++)
    {
        Tmp[k]=Buff[k]; // Replace Buff to Tmp
    }

    T Temp;

    for (int k = 1; k < Len; k++)
    {
        if (Tmp[0] < Tmp[k])
        {
            Temp = Tmp[0];
            Tmp[0] = Tmp[k];
            Tmp[k] = Temp;
        }
    }

    return Tmp[0];
}

template<typename T>
u32 DtList<T>::Index(T e)
{
    for (int k = 0; k < Len; k++)
    {
        if (Buff[k] == e)
        {
            return k;
        }
    }
    return Len;
}

template<typename T>
void DtList<T>::Add(T e)
{
    Buff[Len] = e;
    Len++;
}

extern DtList<s32> Li;


#endif //ARMCPP_DTLIST_H
