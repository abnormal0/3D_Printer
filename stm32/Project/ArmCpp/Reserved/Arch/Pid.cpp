//
// Created by draw on 19-4-19.
//

#include "Pid.h"
#include "Main.h"

__ccm Pid pid;

u16 Adc_Area[ADC_AREA_LEN];

void Pid::Start()
{
//    TICK->Ctrl(Tick_Div8,Tick_Irq_Enable);
//    TICK->Period((Hclk_Freq>>3)/100);
//    TICK->Start();
}


extern "C"
void SysTick_Handler(void)
{
    //Todo
}

u32 tmp=0;
extern "C"
void ADC_IRQHandler(void)
{

   // USART2->Print("Adc Handler:%d,%d",Adc_Area[0],Adc_Area[1]);
}