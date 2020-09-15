//
// Created by Nc2016 on 2019/1/4.
//

#include "Descriptor.h"
#include "Msp.h"

static void GpioInit();
static void RccInit(void);
static void NvicInit(void);
static void PerEnable(void);
static void PerInit(void);

extern "C"
void Core(void)
{
    RccInit();
    NvicInit();
    PerEnable();
    GpioInit();
    PerInit();
}

static void RccInit()
{

    //Power Set to Scale1
    RCC->APB1Enable(APB1_Power);    //Power interface clock enable
    PWR->Scale(Power_Scale1);   //??

    //Set Flash Wait Cycles
    FLASH->WaitCycles(3);   //??? 3 Cycles or 11 Cycles


    //Pll Config
    RCC->HseOn();
    RCC->Pll(25, 288, 2, 6);
    RCC->PllOn();


    //System Clock Config
    RCC->Clk(AHB_Clk_Div1, APB_Clk_Div4, APB_Clk_Div2, Clk_Src_Pll);
}

void NvicInit(void)
{
    M4.NvicGroup(Group_4);
    M4.NvicPri(PendSV_IRQn,15,0);
    M4.NvicPri(SysTick_IRQn,0,0);
    M4.NvicPri(USART2_IRQn,13,0);
    M4.NvicPri(TIM7_IRQn,11,0);
    M4.NvicPri(TIM3_IRQn,12,0);
    //M4.NvicPri(ADC_IRQn,12,0);

}

static void PerEnable()
{
    RCC->AHB1Enable(AHB1_GpioA);
    RCC->AHB1Enable(AHB1_GpioB);
    RCC->AHB1Enable(AHB1_GpioC);
    RCC->AHB1Enable(AHB1_GpioD);
    RCC->AHB1Enable(AHB1_GpioE);
    RCC->APB2Enable(APB2_Adc1);
    RCC->APB2Enable(APB2_Sdio);
    RCC->AHB1Enable(AHB1_DMA1);
    RCC->AHB1Enable(AHB1_DMA2);

    RCC->APB1Enable(APB1_Tim7);
    RCC->APB1Enable(APB1_Tim12);
    RCC->APB1Enable(APB1_Tim2);
    RCC->APB1Enable(APB1_Tim3);
    RCC->APB1Enable(APB1_Tim6);
    RCC->APB1Enable(APB1_Usart2);
}

void GpioInit()
{
    GPIOA->OutOd(4);
    GPIOA->OutOd(5);
    GPIOA->Up(4);
    GPIOA->Up(5);

    GPIOC->OutPp(15);
    GPIOC->Down(15);

    GPIOA->AfPp(2);
    GPIOA->Speed(2, Speed_Very_High);
    GPIOA->Pull(2, Pull_Up);
    GPIOA->Alternate(2, AF7_Usart1_3);

    GPIOA->AfPp(3);
    GPIOA->Speed(3, Speed_Very_High);
    GPIOA->Pull(3, Pull_Up);
    GPIOA->Alternate(3, AF7_Usart1_3);

    GPIOC->AfPp(8);
    GPIOC->AfPp(9);
    GPIOC->AfPp(10);
    GPIOC->AfPp(11);
    GPIOC->AfPp(12);
    GPIOD->AfPp(2);

    GPIOC->Speed(8, Speed_Very_High);
    GPIOC->Speed(9, Speed_Very_High);
    GPIOC->Speed(10, Speed_Very_High);
    GPIOC->Speed(11, Speed_Very_High);
    GPIOC->Speed(12, Speed_Very_High);
    GPIOD->Speed(2, Speed_Very_High);

    GPIOC->Alternate(8, AF12_Fsmc_Sdio_OtgHs);
    GPIOC->Alternate(9, AF12_Fsmc_Sdio_OtgHs);
    GPIOC->Alternate(10, AF12_Fsmc_Sdio_OtgHs);
    GPIOC->Alternate(11, AF12_Fsmc_Sdio_OtgHs);
    GPIOC->Alternate(12, AF12_Fsmc_Sdio_OtgHs);
    GPIOD->Alternate(2, AF12_Fsmc_Sdio_OtgHs);

}

void PerInit()
{

}