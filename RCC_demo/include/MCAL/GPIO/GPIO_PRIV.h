#ifndef GPIO_PRIV_H
#define GPIO_PRIV_H
#include <stdint.h>


/*/0x4002 1C00 - 0x4002 1FFF GPIOH
Section 8.4.11: GPIO register map on page 164
0x4002 1000 - 0x4002 13FF GPIOE
0x4002 0C00 - 0x4002 0FFF GPIOD
0x4002 0800 - 0x4002 0BFF GPIOC
0x4002 0400 - 0x4002 07FF GPIOB
0x4002 0000 - 0x4002 03FF GPIOA
*/
#define AFR_MASK 0x03


typedef struct{
    volatile uint32_t GPIOx_MODER;
    volatile uint32_t GPIOx_OTYPER;
    volatile uint32_t GPIOx_OSPEEDR;
    volatile uint32_t GPIOx_PUPDR;
    volatile uint32_t GPIOx_IDR;
    volatile uint32_t GPIOx_ODR;
    volatile uint32_t GPIOx_BSRR;
    volatile uint32_t GPIOx_LCKR;
    volatile uint32_t GPIOx_AFRL;
    volatile uint32_t GPIOx_AFRH;
    

}GPIO_REGS;
GPIO_REGS * const GPIO[6]={(GPIO_REGS * )0x40020000UL,(GPIO_REGS * )0x40020400UL,(GPIO_REGS * )0x40020800UL,(GPIO_REGS * )0x40020C00UL,(GPIO_REGS * )0x40021000UL,(GPIO_REGS * )0x40021C00Ul};
#endif