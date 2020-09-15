//
// Created by draw on 19-4-10.
//

#ifndef DMA_H
#define DMA_H

#include "Descriptor.h"

enum Dma_Channel
{
    Ch0 = 0b000 << 25,
    Ch1 = 0b001 << 25,
    Ch2 = 0b010 << 25,
    Ch3 = 0b011 << 25,
    Ch4 = 0b100 << 25,
    Ch5 = 0b101 << 25,
    Ch6 = 0b110 << 25,
    Ch7 = 0b111 << 25,
};

enum Dma_Priority
{
    Priority3 = 0b00 << 16,
    Priority2 = 0b01 << 16,
    Priority1 = 0b10 << 16,
    Priority0 = 0b11 << 16,
};

enum Mem_Size
{
    Mem8 = 0b00 << 13,
    Mem16 = 0b01 << 13,
    Mem32 = 0b10 << 13,
};

enum Mem_Mode
{
    Mem_Fix = 0b0 << 10,
    Mem_Inc = 0b1 << 10,
};

enum Per_Size
{
    Per8 = 0b00 << 11,
    Per16 = 0b01 << 11,
    Per32 = 0b10 << 11,
};

enum Per_Mode
{
    Per_Fix = 0b0 << 9,
    Per_Inc = 0b1 << 9,
};

enum Dma_Direction
{
    Per_To_Mem = 0b00 << 7,
    Mem_To_Per = 0b01 << 7,
    Mem_To_Mem = 0b10 << 7,
};

enum Flow_Ctrl
{
    Dma_Ctrl = 0,
    Per_Ctrl = 1,
};

enum Dma_Stream{
    Dma_Stream_0=0,
    Dma_Stream_1=1,
    Dma_Stream_2=2,
    Dma_Stream_3=3,
    Dma_Stream_4=4,
    Dma_Stream_5=5,
    Dma_Stream_6=6,
    Dma_Stream_7=7,
};

class DmaStream
{
public:
    __IO u32 CR;     /*!< DMA stream x configuration register      */
    __IO u32 NDTR;   /*!< DMA stream x number of data register     */
    __IO u32 PAR;    /*!< DMA stream x peripheral address register */
    __IO u32 M0AR;   /*!< DMA stream x memory 0 address register   */
    __IO u32 M1AR;   /*!< DMA stream x memory 1 address register   */
    __IO u32 FCR;    /*!< DMA stream x FIFO control register       */
    void Select(Dma_Channel ch);

    void Priority(Dma_Priority pri);

    void MemSet(Mem_Size size, Mem_Mode mode);

    void PerSet(Per_Size size, Per_Mode mode);

    void Dir(Dma_Direction dir);

    void Circular(bl b);

    void FlowCtrl(Flow_Ctrl ct);

    void Start();

    void Stop();

    void Mem0Addr(u32 addr);

    void PerAddr(u32 addr);

    void DateNum(u32 num);
};

class Dma
{
public:
    __IO u32 LISR;   /*!< DMA low interrupt status register,      Address offset: 0x00 */
    __IO u32 HISR;   /*!< DMA high interrupt status register,     Address offset: 0x04 */
    __IO u32 LIFCR;  /*!< DMA low interrupt flag clear register,  Address offset: 0x08 */
    __IO u32 HIFCR;  /*!< DMA high interrupt flag clear register, Address offset: 0x0C */
    DmaStream DS0;
    DmaStream DS1;
    DmaStream DS2;
    DmaStream DS3;
    DmaStream DS4;
    DmaStream DS5;
    DmaStream DS6;
    DmaStream DS7;

    void Reset(Dma_Stream s);
};

#define DMA1                ((Dma *) 0x40026000U)
#define DMA2                ((Dma *) 0x40026400U)
#endif //ARMCPP_DMA_H
