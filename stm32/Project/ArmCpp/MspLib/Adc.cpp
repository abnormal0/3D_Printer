//
// Created by draw on 19-4-19.
//

#include "Adc.h"

void Adc::Ch(u32 od, u32 ch)
{
    if (od < 6)
    {
        od *= 5;
        SQR3 &= ~(0b11111 << od);
        SQR3 |= ch << od;
        return;
    }
    if (od < 12)
    {
        od = (od - 6) * 5;
        SQR2 &= ~(0b11111 << od);
        SQR2 |= ch << od;
        return;
    }
    if (od < 16)
    {
        od = (od - 12) * 5;
        SQR1 &= ~(0b11111 << od);
        SQR1 |= ch << od;
        return;
    }
}

void Adc::Group(u32 n)
{
    SQR1 &= ~(0b1111 << 20);
    SQR1 |= ((n-1) << 20);
}

void Adc::Start(void)
{
    CR2 |= 0b1u << 30;
}

void Adc::Mode(bl scan, bl cont)
{
    if (scan)
    {
        CR1 |= 0b1 << 8;
    } else
    {
        CR1 &= ~(0b1 << 8);
    }

    if (cont)
    {
        CR2 |= 0b1 << 1;
    } else
    {
        CR2 &= ~(0b1 << 1);
    }
}

void Adc::Iqr(bl en)
{
    if (en)
    {
        CR1 |= 0b1 << 5;
    } else
    {
        CR1 &= ~(0b1 << 5);
    }
}

void Adc::EocEach(bl eoc)
{
    if (eoc)
    {
        CR2 |= 0b1 << 10;
    } else
    {
        CR2 &= ~(0b1 << 10);
    }
}

void Adc::Dma(bl d)
{
    u32 tmp = CR2;
    tmp &= ~(0b11 << 8);
    if (d)
    {
        CR2 = tmp | (0b11 << 8);
    } else
    {
        CR2 = tmp;
    }
}

void Adc::On(void)
{
    CR2 |= 1;
}

void Adc::ExtTri(bl ri, bl fa)
{
    if (ri)
    {
        CR2 |= 0b1 << 28;
    } else
    {
        CR2 &= ~(0b1 << 28);
    }
    if (fa)
    {
        CR2 |= 0b1 << 29;
    } else
    {
        CR2 &= ~(0b1 << 29);
    }
}

void Adc::TriEven(Adc_Trigger trigger)
{
    CR2 &= ~(0b1111 << 24);
    CR2 |= trigger;
}

u16 Adc::GetValue(u32 ch)
{
    SQR3 &= ~0b11111;
    SQR3 |= ch;
    CR2 |= 0b1u << 30;
    while(!(SR & 0b10));
    return DR;
}

void Adc::Sample(u32 ch, Adc_Smp smp)
{
    if(ch>9){
        SMPR1 &= ~(0b111<<((ch-10)*3));
        SMPR1 |= smp<<((ch-10)*3);
    } else{
        SMPR2 &= ~(0b111<<((ch)*3));
        SMPR2 |= smp<<((ch)*3);
    }
}
