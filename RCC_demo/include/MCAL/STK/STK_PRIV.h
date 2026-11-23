#ifndef STK_PRIV_H
#define STK_PRIV_H
#include <stdio.h>
#include <stdint.h>

#define STK ((volatile STK_REG*) 0xE000E010UL)

typedef struct {
    uint32_t CTRL;
    uint32_t LOAD;
    uint32_t VAL;
    uint32_t CALIB;
}STK_REG;

////ctrl
#define ENABLE 0UL
#define TICKINT 1UL
#define CLKSOURCE 2UL
#define COUNTFLAG 16UL
////LOAD
#define RELOAD 0UL
///VAL
#define CURRENT 0UL
//CALIB
#define TENMS 0UL
#define SKEW 30UL
#define NOREF 31UL



#endif