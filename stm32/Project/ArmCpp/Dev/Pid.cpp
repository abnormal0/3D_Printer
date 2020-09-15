//
// Created by draw on 19-5-12.
//

#include "Pid.h"
#include "Msp.h"
#include "Core.h"

#include "Comm.h"

#include "Ntc.h"
#include "DtLib.h"

Pid Pi;

#define Rt (16000.0/25.0)
#define Rb (10000.0)
#define Vr (3.3)


extern "C"
void TIM3_IRQHandler(void)
{
    TIM3->SR = 0;
    Pi.Calcu();


//    Com.Text << "B:" << Pi.T;
//    Com.Flush();

    Pi.Extr();
    Pi.Bed();
}

void Pid::Run()
{
    Ts = 0;
    Bs = 0;

    Te = 0;
    Be = 0;

    Kpt = 150;
    Kpb = 100;
    Kdt = 7000;
    Kdb = 3000;

    It = 5.0f;
    Ib = 5.0f;

    Wt = 0;
    Wb = 0;


    GPIOA->Anal(6);
    GPIOC->Anal(4);

    DMA2->DS0.DateNum(2 * 8);
    DMA2->DS0.Mem0Addr((u32) (Buff));
    DMA2->DS0.PerAddr((u32) &(ADC1->DR));

    DMA2->DS0.Select(Ch0);
    DMA2->DS0.Priority(Priority1);
    DMA2->DS0.MemSet(Mem16, Mem_Inc);
    DMA2->DS0.PerSet(Per16, Per_Fix);
    DMA2->DS0.Dir(Per_To_Mem);
    DMA2->DS0.Circular(True);
    DMA2->DS0.FlowCtrl(Dma_Ctrl);
    DMA2->DS0.Start();

    ADC1->Mode(True, True);
    ADC1->Iqr(False);
    ADC1->EocEach(True);
    ADC1->Dma(True);

    ADC1->Group(2);
    ADC1->Ch(0, 6);
    ADC1->Ch(1, 14);

    ADC1->Sample(6, Adc_Smp_480Clk);
    ADC1->Sample(14, Adc_Smp_480Clk);

    ADC1->ExtTri(False, False);
    ADC1->TriEven(Trigger_Timer3_CH1);

    ADC1->On();
    ADC1->Start();

    TIM3->Run(7199, 259);

    GPIOB->AfPp(15);
    GPIOB->Speed(15, Speed_Very_High);
    GPIOB->Alternate(15, AF9_Can1_2_Tim12_14);

    GPIOB->AfPp(11);
    GPIOB->Speed(11, Speed_Very_High);
    GPIOB->Alternate(11, AF1_Tim1_2);

    TIM12->Pwm2(0, 65535);
    TIM2->Pwm4(0, 65535);

    //TIM12->CCR2=40000;
}

void Pid::Calcu()
{
    T = 0;
    B = 0;

    B = Math.MedianFliter(Buff + 0, 8, 2);
    T = Math.MedianFliter(Buff + 1, 8, 2);


    T = T * 3.3 / 4095.0;
    T = (T * Rt) / (Vr - T);

    T = Rs.Value(T);

    B = B * 3.3 / 4095.0;

    B = (B * Rb) / (Vr - B);
    B = Rs.Value(B);
}

void Pid::Bed()
{
    if (Bs < 35)
    {
        TIM12->CCR2 = 65535;
        return;
    }

    float e = Bs - B;

    if (e < 2 && e > -2)
    {
        Wb++;
    } else
    {
        Wb = 0;
    }

    s32 dt;

    dt = TIM12->CCR2 + (Be - e) * Kdb - e * Kpb;

    Be = e;


    if (dt > 65535)
    {
        dt = 65535;
    }
    if (dt < 20000)
    {
        dt = 20000;
    }

    TIM12->CCR2 = dt;
}

void Pid::Extr()
{
    if (Ts < 150)
    {
        TIM2->CCR4 = 65535;
        return;
    }

    float e = Ts - T;

    if (e < 2 && e > -2)
    {
        Wt++;
    } else
    {
        Wt = 0;
    }

    if (e < -5)
    {
        TIM2->CCR4 = 65535;
        return;
    }

    if (e > 20)
    {
        TIM2->CCR4 = 50000;
        return;
    }

    s32 dt;

    dt = TIM2->CCR4 + (Te - e) * Kdt - e * Kpt;

    Te = e;


    if (dt > 65535)
    {
        dt = 65535;
    }
    if (dt < 55000)
    {
        dt = 55000;
    }

    TIM2->CCR4 = dt;

}
