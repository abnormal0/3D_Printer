//
// Created by draw on 19-4-10.
//

#include "Dma.h"

void DmaStream::Select(Dma_Channel ch)
{
    CR &= ~(0b111 << 25);
    CR |= ch;
}

void DmaStream::Priority(Dma_Priority pri)
{
    CR &= ~(0b11 << 16);
    CR |= pri;
}

void DmaStream::MemSet(Mem_Size size, Mem_Mode mode)
{
    CR &= ~((0b11 << 13) | (0b1 << 10));
    CR = CR | size | mode;
}

void DmaStream::PerSet(Per_Size size, Per_Mode mode)
{
    CR &= ~((0b11 << 11) | (0b1 << 9));
    CR = CR | size | mode;
}

void DmaStream::Dir(Dma_Direction dir)
{
    CR &= ~(0b11 << 7);
    CR |= dir;
}

void DmaStream::Circular(bl b)
{
    if (b)
    {
        CR |= 0b1 << 8;
    } else
    {
        CR &= ~(0b1 << 8);
    }
}

void DmaStream::FlowCtrl(Flow_Ctrl ct)
{
    if (ct)
    {
        CR |= 0b1 << 5;
    } else
    {
        CR &= ~(0b1 << 5);
    }
}

void DmaStream::Start()
{
    CR |= 0b1;
}

void DmaStream::Stop()
{
    CR &= ~0b1;
}

void DmaStream::Mem0Addr(u32 addr)
{
    M0AR = addr;
}

void DmaStream::PerAddr(u32 addr)
{
    PAR = addr;
}

void DmaStream::DateNum(u32 num)
{
    NDTR = num;
}

void Dma::Reset(Dma_Stream s)
{
    switch (s)
    {
        case Dma_Stream_0:
            DS0.CR &= ~0b1;
            LIFCR = 0b111111 << 0;
            DS0.CR |= 0b1;
            break;
        case Dma_Stream_1:
            DS1.CR &= ~0b1;
            LIFCR = 0b111111 << 6;
            DS1.CR |= 0b1;
            break;
        case Dma_Stream_2:
            DS2.CR &= ~0b1;
            LIFCR = 0b111111 << 16;
            DS2.CR |= 0b1;
            break;
        case Dma_Stream_3:
            DS3.CR &= ~0b1;
            LIFCR = 0b111111 << 22;
            DS3.CR |= 0b1;
            break;
        case Dma_Stream_4:
            DS4.CR &= ~0b1;
            HIFCR = 0b111111 << 0;
            DS4.CR |= 0b1;
            break;
        case Dma_Stream_5:
            DS5.CR &= ~0b1;
            HIFCR = 0b111111 << 6;
            DS5.CR |= 0b1;
            break;
        case Dma_Stream_6:
            DS6.CR &= ~0b1;
            HIFCR = 0b111111 << 16;
            DS6.CR |= 0b1;
            break;
        case Dma_Stream_7:
            DS7.CR &= ~0b1;
            HIFCR = 0b111111 << 22;
            DS7.CR |= 0b1;
            break;
    }
}
