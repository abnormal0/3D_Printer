//
// Created by Nc2016 on 2019/1/5.
//

#ifndef __FLASH_H
#define __FLASH_H

#include "Descriptor.h"


class Flash
{
public:
    __IO u32 ACR;      /*!< FLASH access control register,   Address offset: 0x00 */
    __IO u32 KEYR;     /*!< FLASH key register,              Address offset: 0x04 */
    __IO u32 OPTKEYR;  /*!< FLASH option key register,       Address offset: 0x08 */
    __IO u32 SR;       /*!< FLASH status register,           Address offset: 0x0C */
    __IO u32 CR;       /*!< FLASH control register,          Address offset: 0x10 */
    __IO u32 OPTCR;    /*!< FLASH option control register ,  Address offset: 0x14 */
    __IO u32 OPTCR1;   /*!< FLASH option control register 1, Address offset: 0x18 */

    void WaitCycles(u32 cs);
};

#define FLASH                   ((Flash *) 0x40023C00U)


#endif //HELLO_FLASH_H
