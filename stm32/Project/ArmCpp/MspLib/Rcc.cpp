//
// Created by Nc2016 on 2019/1/4.
//

#include "Rcc.h"
#include "Basic.h"


void Rcc::SetDefault(void)
{
    /* Set HSION bit */ //Page 161
    RCC->CR |= 0x00000001U;

    /* Reset CFGR register */   //Page 165
    RCC->CFGR = 0x00000000U;

    /* Reset HSEON, CSSON and PLLON bits */
    RCC->CR &= 0xFEF6FFFFU;

    /* Reset PLLCFGR register */
    RCC->PLLCFGR = 0x24003010U;

    /* Reset HSEBYP bit */
    RCC->CR &= 0xFFFBFFFFU;

    /* Disable all interrupts */
    RCC->CIR = 0x00000000U;

}

void Rcc::HseOn(void)
{
    CR |= 1u << 16;
    while (!(CR & (1u << 17)));
}

void Rcc::PllOn(void)
{
    CR |= 1u << 24;
    while (!(CR & (1u << 25)));
}

void Rcc::APB1Enable(APB1_Dev dev)  //形参为dev，类型为APB1_Dev枚举
{
    APB1ENR |= dev;
}

void Rcc::APB2Enable(APB2_Dev dev)
{
    APB2ENR |= dev;
}

void Rcc::AHB1Enable(AHB1_Dev dev)
{
    AHB1ENR |= dev;
}

void Rcc::Pll(u32 M, u32 N, u32 P, u32 Q, Pll_Src src)  //25, 288, 2, 6, src = Pll_Src_Hse = 1
{
    u32 cfg = (src << 22) | (M << 0) | (N << 6) | ((P - 1) << 15) | (Q << 24);  //0x0640C819
    u32 reg = PLLCFGR & 0xf0bc8000u;
    PLLCFGR = reg | cfg;

    switch (src)
    {
        case Pll_Src_Hse:
            M4.Pll_Freq = Hse_Osc_Freq / M * N / P;
            break;
        case Pll_Src_Hsi:
            M4.Pll_Freq = Hsi_Osc_Freq / M * N / P;
            break;
    }
}

void Rcc::Clk(AHB_Clk_Div H, APB_Clk_Div P1, APB_Clk_Div P2, Clk_Src src)
{
    u32 cfg = (src << 0) | (H << 4) | (P1 << 10) | (P2 << 13);
    u32 reg = CFGR & 0xffff030bu;
    CFGR = reg | cfg;

    switch (src)
    {
        case Clk_Src_Hse:
            M4.Sys_Freq = Hse_Osc_Freq;
            break;
        case Clk_Src_Hsi:
            M4.Sys_Freq = Hsi_Osc_Freq;
            break;
        case Clk_Src_Pll:
            M4.Sys_Freq = M4.Pll_Freq;
            break;
    }

    switch (H)
    {
        case AHB_Clk_Div1:
            M4.Hclk_Freq = M4.Sys_Freq >> 0;
            break;
        case AHB_Clk_Div2:
            M4.Hclk_Freq = M4.Sys_Freq >> 1;
            break;
        case AHB_Clk_Div4:
            M4.Hclk_Freq = M4.Sys_Freq >> 2;
            break;
        case AHB_Clk_Div8:
            M4.Hclk_Freq = M4.Sys_Freq >> 3;
            break;
        case AHB_Clk_Div16:
            M4.Hclk_Freq = M4.Sys_Freq >> 4;
            break;
        case AHB_Clk_Div64:
            M4.Hclk_Freq = M4.Sys_Freq >> 6;
            break;
        case AHB_Clk_Div128:
            M4.Hclk_Freq = M4.Sys_Freq >> 7;
            break;
        case AHB_Clk_Div256:
            M4.Hclk_Freq = M4.Sys_Freq >> 8;
            break;
    }

    switch (P1)
    {
        case APB_Clk_Div1:
            M4.Pclk1_Freq = M4.Hclk_Freq >> 0;
            break;
        case APB_Clk_Div2:
            M4.Pclk1_Freq = M4.Hclk_Freq >> 1;
            break;
        case APB_Clk_Div4:
            M4.Pclk1_Freq = M4.Hclk_Freq >> 2;
            break;
        case APB_Clk_Div8:
            M4.Pclk1_Freq = M4.Hclk_Freq >> 3;
            break;
        case APB_Clk_Div16:
            M4.Pclk1_Freq = M4.Hclk_Freq >> 4;
            break;
    }

    switch (P2)
    {
        case APB_Clk_Div1:
            M4.Pclk2_Freq = M4.Hclk_Freq >> 0;
            break;
        case APB_Clk_Div2:
            M4.Pclk2_Freq = M4.Hclk_Freq >> 1;
            break;
        case APB_Clk_Div4:
            M4.Pclk2_Freq = M4.Hclk_Freq >> 2;
            break;
        case APB_Clk_Div8:
            M4.Pclk2_Freq = M4.Hclk_Freq >> 3;
            break;
        case APB_Clk_Div16:
            M4.Pclk2_Freq = M4.Hclk_Freq >> 4;
            break;
    }

    M4.Apb1_Tim_Freq = M4.Pclk1_Freq << 2;
    M4.Apb2_Tim_Freq = M4.Pclk2_Freq << 2;

}




