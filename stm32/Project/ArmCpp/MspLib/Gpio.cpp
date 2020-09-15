//
// Created by Nc2016 on 2019/1/4.
//

#include "Gpio.h"

void Gpio::OutPp(u32 pin)
{
    MODER &= ~(3u << (pin * 2));
    MODER |= 1u << (pin * 2);

    OTYPER &= ~(1u << pin);
}

void Gpio::OutOd(u32 pin)
{
    MODER &= ~(3u << (pin * 2));
    MODER |= 1u << (pin * 2);

    OTYPER |= (1u << pin);
}

void Gpio::Down(u32 b)
{
    BSRR = (0x1u << 16) << b;
}

void Gpio::Up(u32 b)
{
    BSRR = (0x1u) << b;
}

void Gpio::AfPp(u32 pin)
{
    MODER &= ~(3u << (pin * 2));
    MODER |= 2u << (pin * 2);
    OTYPER &= ~(1u << pin);
}

void Gpio::Speed(u32 pin, SPD speed)
{
    OSPEEDR &= ~(3u << (pin * 2));
    OSPEEDR |= speed << (pin * 2);
}

void Gpio::Pull(u32 pin, PULL pull)
{
    PUPDR &= ~(3u << (pin * 2));
    PUPDR |= pull << (pin * 2);
}

void Gpio::Alternate(u32 pin, AFIO af)
{
    if (pin < 8)
    {
        AFRL &= ~(0xfu << (pin * 4));
        AFRL |= af << (pin * 4);
    } else
    {
        AFRH &= ~(0xfu << ((pin - 8) * 4));
        AFRH |= af << ((pin - 8) * 4);
    }
}

void Gpio::Anal(u32 pin)
{
    MODER |= 0b11 << (pin << 1);
}

void Gpio::In(u32 pin)
{
    MODER &= ~(3u << (pin * 2));
}



