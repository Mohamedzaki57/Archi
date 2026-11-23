#ifndef RCC_PRIV_h
#define RCC_PRIV_h
#include <stdio.h>
#include <stdint.h>

#define RCC ((volatile RCC_REG *)(0x40023800))
///// magic address   #define RCC_BASE ((uint32_t * )0x40023800)

#define TIMEOUT 100000
////////CR/////////
#define PLLRDY 25
#define PLLON 24
#define HSEON 16
#define HSERDY 17
#define HSION 0
#define HSIRDY 1
////////CFGR//////////
#define SWbit 0
#define SW_MASK (0x03 << SWbit)
#define HPRE 4
#define HPRE_MASK (0xf << HPRE)
#define PPRE1 10
#define PPRE1_MASK (0x7 <<PPRE1)
#define PPRE2 13
#define PPRE2_MASK (0x7 << PPRE2)


#define SWSbit 2
#define SWS_MASK (0x03 << SWSbit)
////////PLLCFGR////////
#define PLLSRC 22

#define PLL_Mbit 0
#define PLL_MMask (0x3f << PLL_Mbit)
#define PLL_Nbit 6
#define PLL_NMask (0x1ff << PLL_Nbit)
#define PLL_Pbit 16
#define PLL_PMask (0x03 << PLL_Pbit)
#define PLL_Qbit 24
#define PLL_QMask (0x0f << PLL_Qbit)

////////CSR/////////

#define CSR_Mask (0b11111111 <<24)
#define LSIRDY 1
#define LSION 0


#define MCO1PRE 24
#define MCO2PRE 25
#define MCO3PRE 26
#define GPIOERST 4
#define GPIODRST 3
#define GPIOCRST 2
#define GPIOBRST 1
#define GPIOARST 0


typedef struct
{

    volatile uint32_t CR;

    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t reserved0[2];
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t reserved1[2];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t reserved2[2];
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t reserved3[2];
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t reserved4[2];
    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;
    volatile uint32_t reserved5[2];
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    volatile uint32_t reserved6[2];
    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2SCFGR;
    volatile uint32_t reserved7;
    volatile uint32_t DCKCFGR;
} RCC_REG;

#endif