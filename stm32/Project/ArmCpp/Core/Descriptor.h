//
// Created by Nc2016 on 2019/1/3.
//

#ifndef __DESCRIPTOR_H
#define __DESCRIPTOR_H


#define __weak   __attribute__((weak))
#define __ccm   __attribute__((section(".ccmram")))

#define __nop() asm("NOP")


#define     __I     volatile const
#define     __O     volatile
#define     __IO    volatile

#define Null   ((u32*)0)    //将0转换为signed32

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef int s32;
typedef short s16;
typedef char s8;

typedef volatile unsigned int vu32;

typedef enum
{
    True = 1,
    False = 0,
} bl;


#endif //HELLO_BASIC_H
