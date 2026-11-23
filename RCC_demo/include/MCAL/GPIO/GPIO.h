#ifndef GPIO_H
#define GPIO_H
#include <stdio.h>

typedef enum{
    GPIOA,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE,
    GPIOH
}GPIO_PORT;

typedef enum{
    GPIO_PIN0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7,
    GPIO_PIN8,
    GPIO_PIN9,
    GPIO_PIN10,
    GPIO_PIN11,
    GPIO_PIN12,
    GPIO_PIN13,
    GPIO_PIN14,
    GPIO_PIN15
   
}GPIO_PIN;

typedef enum{
    GPIO_AFR0,
    GPIO_AFR1,
    GPIO_AFR2,
    GPIO_AFR3,
    GPIO_AFR4,
    GPIO_AFR5,
    GPIO_AFR6,
    GPIO_AFR7,
    GPIO_AFR8,
    GPIO_AFR9,
    GPIO_AFR10,
    GPIO_AFR11,
    GPIO_AFR12,
    GPIO_AFR13,
    GPIO_AFR14,
    GPIO_AFR15
   
}GPIO_enuAFR;


typedef enum{
    GPIO_OK,
    GPIO_INVALIDPARAM,
    GPIO_TIMEOUT,
    GPIO_NULLPTR
}GPIO_enuErrCode;

typedef enum{
    LOW_ACTIVEPIN,
    HIGH_ACTIVEPIN
}GPIO_enuPinStat;

typedef enum{
    PUSHPULL,
    OPENDRAIN
}GPIO_enuOUTTYPE;

typedef enum{
    LOW_SPEED,
    MED_SPEED,
    HIGH_SPEED,
    VHIGH_SPEED
}GPIO_enuSPEED;

typedef enum{
    NOPUPD,
    PULLUP,
    PULLDOWN,
    PUMASK
}GPIO_enuPUPD;

typedef enum{
    MODE_IN,
    MODE_OUT,
    MODE_ALTER,
    MODE_ANALOG
}GPIO_enuMODE;

typedef enum{
    AFRL,
    AFRH
}GPIO_enuALTER;

typedef struct{
 GPIO_PORT   Init_port;
 GPIO_PIN   Init_pin;
 GPIO_enuMODE   Init_mode;
 GPIO_enuSPEED   Init_speed;
 GPIO_enuOUTTYPE   Init_outType;
 uint32_t   Init_AFR;
 GPIO_enuPUPD   Init_PUPD;
}GPIO_strInit;

GPIO_enuErrCode GPIO_enuPinWrite( GPIO_PORT port , GPIO_PIN pin ,GPIO_enuPinStat stat);
GPIO_enuErrCode GPIO_enuPinRead( GPIO_PORT port ,  GPIO_PIN loc_pinNum ,volatile uint32_t *loc_read );
GPIO_enuErrCode GPIO_enuPortWrite(GPIO_PORT port, GPIO_enuPinStat stat);
GPIO_enuErrCode GPIO_enuPortRead(GPIO_PORT port, uint32_t *loc_portRead);
GPIO_enuErrCode GPIO_CFGSpeed(GPIO_PORT port, GPIO_PIN pin, GPIO_enuSPEED speed);
GPIO_enuErrCode GPIO_CFGPUPD(GPIO_PORT port, GPIO_PIN pin, GPIO_enuPUPD pupd);
GPIO_enuErrCode GPIO_CFGPinMode(GPIO_PORT port, GPIO_PIN pin, GPIO_enuMODE mode);
GPIO_enuErrCode GPIO_CFGOutType(GPIO_PORT port, GPIO_PIN pin, GPIO_enuOUTTYPE type);
GPIO_enuErrCode GPIO_enuCFGAltern(GPIO_PORT port, GPIO_PIN pin, GPIO_enuAFR alter);
GPIO_enuErrCode GPIO_InitPin(GPIO_strInit * str);




#endif