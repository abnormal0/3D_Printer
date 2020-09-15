//
// Created by Nc2016 on 2019/1/5.
//

#ifndef __TOOLS_H
#define __TOOLS_H

#define Bits1         0x1u
#define Bits2         0x3u
#define Bits3         0x7u
#define Bits4         0xfu
#define Bits5         0x1fu
#define Bits6         0x3fu
#define Bits7         0x7fu
#define Bits8         0xffu
#define Bits9         0x1ffu
#define Bits10        0x3ffu
#define Bits11        0x7ffu
#define Bits12        0xfffu
#define Bits13        0x1fffu
#define Bits14        0x3fffu
#define Bits15        0x7fffu
#define Bits16        0xffffu
#define Bits17        0x1ffffu
#define Bits18        0x3ffffu
#define Bits19        0x7ffffu
#define Bits20        0xfffffu
#define Bits21        0x1fffffu

#define Clean_Bit(V,b)        (V)&=~((1u)<<(b))
#define Set_Bit(V,b)          (V)|= ((1u)<<(b))

#define Clean_Bits(V,s,n)     (V)&=~((n)<<(s))
#define Set_Bits(V,s,x)       (V)|= ((x)<<(s))

#define Read_Bits(V,s,n)      (V)&((n)<<(s))
#define Write_Bits(V,s,x,n)   (V)=(((V)&~((n)<<(s)))|((x)<<(s)))


#endif //HELLO_TOOLS_H
