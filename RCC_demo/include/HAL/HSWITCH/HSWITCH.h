#ifndef HSWITCH_H
#define HSWITCH_H
#include"./MCAL/GPIO/GPIO.h"
#include "./HAL/HSWITCH/HSWITCH_CFG.h"
#define MXSWITCH 100

typedef enum{
    HSWITCH_OK,
    HSWITCh_FAILED,
    HSWITCH_INVALIDPARAM
}HSWITCH_enuErrCode;

typedef enum{
    UN_define,
    PREpressed,
    PRESSED,
    PRERlease,
    RELEASE
}HSWItCH_enuStats;


typedef struct{
    GPIO_PORT port;
    GPIO_PIN pin;
    GPIO_enuPUPD pupd;
    GPIO_enuPinStat activStat;


}HSWITCH_strSwitches;

typedef struct{
    HSWItCH_enuStats current;
    HSWItCH_enuStats prev;
    uint8_t statLevel;
    HSWItCH_enuStats finStat;
}HSWITCH_strSwitRuntime;



HSWITCH_enuErrCode HSWITCH_Init(HSWITCH_enuSwitches loc_switch );
HSWITCH_enuErrCode HSWITCH_enuReadStat(HSWITCH_strSwitRuntime,HSWITCH_strSwitRuntime*);
HSWITCH_enuErrCode HSWITCH_enuRunnabl();


#endif