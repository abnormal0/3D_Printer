//
// Created by draw on 19-4-17.
//

#include "UsartBuffer.h"
#include "Msp.h"

u8 USART_Area[USART_AREA_SIZE];
UsartBuffer ub;


extern "C"
void USART2_IRQHandler(void)
{
    USART2->Clean(Status_Idle);
    ub.end=0xffff-(DMA1->DS5.NDTR);

    DMA1->Reset(Dma_Stream_5);
}