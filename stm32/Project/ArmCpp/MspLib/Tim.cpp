//
// Created by draw on 19-4-17.
//

#include "Tim.h"

void Tim::Sleep(u16 psc, u16 arr)
{
    PSC=psc;
    ARR=arr;

    DIER=0b1;
    CR1=0b1101;
}

void Tim::Run(u16 psc, u16 arr)
{
    PSC=psc;
    ARR=arr;

    DIER=0b1;
    CR1=0x85;
}

void Tim::Start(u32 psc)
{
    PSC=psc;
    ARR=0xffffffff;
    CR1=0b1101;
}

void Tim::Pwm1(u16 psc, u16 arr)
{
    CCMR1 |= 7 << 4;   //CH2 PWM2模式
    CCMR1 |= 1 << 3;   //CH2预装载使能
    ARR = arr;           //设定计数器自动重装值
    PSC = psc;                //预分频器不分频
    CCR1 = arr;         //设置占空比
    CCER |= 1 << 0;     //OC2 输出使能
    CR1 |= 0x01;      //使能定时器2
}

void Tim::Pwm2(u16 psc, u16 arr)
{
    CCMR1 |= 7 << 12;   //CH2 PWM2模式
    CCMR1 |= 1 << 11;   //CH2预装载使能
    ARR = arr;           //设定计数器自动重装值
    PSC = psc;                //预分频器不分频
    CCR2 = arr;         //设置占空比
    CCER |= 1 << 4;     //OC2 输出使能
    CR1 |= 0x01;      //使能定时器2
}

void Tim::Pwm3(u16 psc, u16 arr)
{
    CCMR2 |= 7 << 4;   //CH2 PWM2模式
    CCMR2 |= 1 << 3;   //CH2预装载使能
    ARR = arr;           //设定计数器自动重装值
    PSC = psc;                //预分频器不分频
    CCR3 = arr;         //设置占空比
    CCER |= 1 << 8;     //OC2 输出使能
    CR1 |= 0x01;      //使能定时器2
}

void Tim::Pwm4(u16 psc, u16 arr)
{
    CCMR2 |= 7 << 12;   //CH2 PWM2模式
    CCMR2 |= 1 << 11;   //CH2预装载使能
    ARR = arr;           //设定计数器自动重装值
    PSC = psc;                //预分频器不分频
    CCR4 = arr;         //设置占空比
    CCER |= 1 << 12;     //OC2 输出使能
    CR1 |= 0x01;      //使能定时器2
}
