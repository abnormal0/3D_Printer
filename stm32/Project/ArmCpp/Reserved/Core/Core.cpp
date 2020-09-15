//
// Created by Nc2016 on 2019/1/4.
//

#include "Msp.h"
#include "UsartBuffer.h"
#include "Main.h"

extern u8 USART_Area[];

static void RccInit(void);
static void NvicInit(void);
static void PerEnable(void);
static void PerInit(void);

void GpioInit();

extern "C"
void Core(void)
{
    RccInit();
    NvicInit();
    PerEnable();
    GpioInit();
    PerInit();
}

void NvicInit(void)
{
    M4.NvicGroup(Group_4);
    M4.NvicPri(PendSV_IRQn,15,0);
    M4.NvicPri(SysTick_IRQn,0,0);
    M4.NvicPri(USART2_IRQn,13,0);
    M4.NvicPri(TIM7_IRQn,14,0);
    M4.NvicPri(ADC_IRQn,12,0);

}


static void RccInit()
{

    //Power Set to Scale1
    RCC->APB1Enable(APB1_Power);
    PWR->Scale(Power_Scale1);

    //Set Flash Wait Cycles
    FLASH->WaitCycles(3);


    //Pll Config
    RCC->HseOn();
    RCC->Pll(25, 288, 2,6);
    RCC->PllOn();


    //System Clock Config
    RCC->Clk(AHB_Clk_Div1, APB_Clk_Div4, APB_Clk_Div2, Clk_Src_Pll);
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
    RCC->APB1Enable(APB1_Tim3);
    RCC->APB1Enable(APB1_Tim6);
    RCC->APB1Enable(APB1_Usart2);
}

void PerInit()
{

    DMA1->DS5.DateNum(USART_AREA_SIZE);
    DMA1->DS5.Mem0Addr((u32)(USART_Area));
    DMA1->DS5.PerAddr((u32) &(USART2->DR));

    DMA1->DS5.Select(Ch4);
    DMA1->DS5.Priority(Priority0);
    DMA1->DS5.MemSet(Mem8, Mem_Inc);
    DMA1->DS5.PerSet(Per8, Per_Fix);
    DMA1->DS5.Dir(Per_To_Mem);
    DMA1->DS5.Circular(False);
    DMA1->DS5.FlowCtrl(Per_Ctrl);
    DMA1->DS5.Start();

    USART2->Reset();
    USART2->Baud(115200);

    USART2->CR1 |= 1 << 4;
    USART2->CR3 |= 1 << 6;

    USART2->Enable(Tx_Rx_Both);
    USART2->PrintLn("System Init...");


    SDIO->ClockDiv(120);
    SDIO->RiEdge(True);
    SDIO->ClkPass(False);
    SDIO->PowerSave(False);
    SDIO->BusWide(Sdio_Bus_4b);
    SDIO->FlowCtrl(False);
    SDIO->PowerOn();
    SDIO->ClkOn();

    SDIO->DTIMER = 0XFFFFFFFFU;
    SDIO->DLEN = 512;

    DMA2->DS0.DateNum(ADC_AREA_LEN);
    DMA2->DS0.Mem0Addr((u32)(Adc_Area));
    DMA2->DS0.PerAddr((u32) &(ADC1->DR));

    DMA2->DS0.Select(Ch0);
    DMA2->DS0.Priority(Priority1);
    DMA2->DS0.MemSet(Mem16, Mem_Inc);
    DMA2->DS0.PerSet(Per16, Per_Fix);
    DMA2->DS0.Dir(Per_To_Mem);
    DMA2->DS0.Circular(True);
    DMA2->DS0.FlowCtrl(Dma_Ctrl);
    DMA2->DS0.Start();

    ADC1->Mode(True,False);
    ADC1->Iqr(True);
    ADC1->EocEach(False);
    ADC1->Dma(True);

    ADC1->Group(2);
    ADC1->Ch(0,8);
    ADC1->Ch(1,9);

    ADC1->ExtTri(True,False);
    ADC1->TriEven(Trigger_Timer3_CH1);

    ADC1->On();
    //ADC1->Start();

    TIM3->CR1 |= TIM_CR1_ARPE;
    TIM3->CCMR1|=7<<4;   //CH2 PWM2模式
    TIM3->CCMR1|=1<<3;   //CH2预装载使能
    TIM3->ARR=99;           //设定计数器自动重装值
    TIM3->PSC=7499;                //预分频器不分频
    TIM3->CCR1=49;         //设置占空比
    TIM3->CCER|=1;     //OC2 输出使能
    TIM3->CR1|=0x01;      //使能定时器2
}

void GpioInit()
{
    GPIOA->OutOd(4);
    GPIOA->OutOd(5);
    GPIOA->Up(4);
    GPIOA->Up(5);

    GPIOB->OutPp(12);
    GPIOB->Down(12);

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

    GPIOB->Anal(0);
    GPIOB->Anal(1);
}




