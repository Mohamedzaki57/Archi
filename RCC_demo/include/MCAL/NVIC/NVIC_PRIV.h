#ifndef NVIC_PRIV_H
#define NVIC_PRIV_H
#include <stdint.h>
#include "NVIC.h"

#define NVIC ((volatile NVIC_REG_t *)(0xE000E100UL))

#define NVIC_mod 32
#define NVIC_start 0
#define NVIC_end 15
typedef struct {

 
uint32_t NVIC_ISER[8];
uint32_t reserved0[24];
uint32_t NVIC_ICER[8];
uint32_t reserved1[24];
uint32_t NVIC_ISPR[8];
uint32_t reserved2[24];
uint32_t NVIC_ICPR[8];
uint32_t reserved3[24];
uint32_t NVIC_IABR[8];
uint32_t reserved4[56];
uint8_t NVIC_IPR[240];
uint32_t reserved5[644];
uint32_t NVIC_STIR;


}NVIC_REG_t;

#endif